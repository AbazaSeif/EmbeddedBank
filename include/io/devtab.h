/*============================================================================
 *
 *      devtab.h
 *
 *      Device I/O Table
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2006 Innova Card.
 * All Rights Reserved.
 *
 * This software is the confidential and proprietary information of
 * Innova Card ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with Innova Card.
 *
 * Innova Card makes no representations or warranties about the suitability of 
 * the software, either express or implied, including but not limited to 
 * the implied warranties of merchantability, fitness for a particular purpose, 
 * or non-infrigement. Innova Card shall not be liable for any damages suffered 
 * by licensee as the result of using, modifying or distributing this software 
 * or its derivatives.
 * 
 *==========================================================================*/
/*============================================================================
 * 
 * Author(s):     Arnaud Corria 
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:   Describe low level I/O interfaces 
 * 
 *==========================================================================*/ 
#ifndef _IO_DEVTAB_H_
#define _IO_DEVTAB_H_

#include <io/devio.h>

#define __string(_x) #_x
#define __xstring(_x) __string(_x)

#define DEVTABLE_BEGIN( _label, _name )                                 \
__asm__(".section \".dev.table." __xstring(_name) ".begin\",\"aw\"\n"       \
    ".globl " __xstring(_label) "\n"                         \
    ".type    " __xstring(_label) ",object\n"                \
    ".p2align " __xstring(3) "\n"                           \
__xstring(_label) ":\n"                                      \
    ".previous\n"                                                            \
       )

#define DEVTABLE_END( _label, _name )                                   \
__asm__(".section \".dev.table." __xstring(_name) ".finish\",\"aw\"\n"      \
    ".globl " __xstring(_label) "\n"                         \
    ".type    " __xstring(_label) ",object\n"                \
    ".p2align " __xstring(3) "\n"                           \
__xstring(_label) ":\n"                                      \
    ".previous\n"                                                            \
       )

// This macro must be applied to any types whose objects are to be placed in
// tables

#define DEVTABLE_TYPE 


#define DEVTABLE_ENTRY( _name ) \
  __attribute__ ((aligned (4) , section(".dev.table." __xstring(_name) ".data")))


#define DEVTABLE_QUALIFIED_ENTRY( _name, _qual ) \
        __attribute__ ((section(".dev.table." __xstring(_name) ".data." \
                              __xstring(_qual)))



/* Set of functions which handle top level I/O functions */
typedef struct {
    int (*write)(io_handle_t handle, const void *buf, unsigned int *len);
    int (*read)(io_handle_t handle, void *buf, unsigned int *len);
    int (*bwrite)(const void *buf, 
                       unsigned int *len,
                       unsigned int pos);
    int (*bread)(void *buf, 
                      unsigned int *len,
                      unsigned int pos);
    int  (*select)(unsigned int which,
                        unsigned int info);
    int (*get_config)(unsigned int key, 
                            void *buf, 
                            unsigned int *len);
    int (*set_config)(unsigned int key, 
                            const void *buf, 
                            unsigned int *len);
    int (*ioctl)(io_handle_t handle, unsigned int cmd, void *data);

} devio_table_t;


/*----------------------------------------------------------------------------
 *   Function declarations
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


int devio_cwrite(io_handle_t handle, const void *buf, unsigned int *len);
int devio_cread(io_handle_t handle, void *buf, unsigned int *len);
int devio_bwrite(io_handle_t handle, const void *buf, unsigned int *len,
                                     unsigned int pos);
int devio_bread(io_handle_t handle, void *buf, unsigned int *len,
                                    unsigned int pos);

int devio_select(io_handle_t handle,
                                     unsigned int which,
                                     unsigned int info);

int devio_get_config(io_handle_t handle,
                                         unsigned int key,
                                         void* buf,
                                         unsigned int* len);

int devio_set_config(io_handle_t handle,
                                         unsigned int key,
                                         void* buf,
                                         unsigned int* len);

#ifdef __cplusplus
}
#endif

// Initialization macros

#define CHAR_DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config,_ioctl)    \
devio_table_t const _l = {                                          \
    _write,                                                         \
    _read,                                                          \
    devio_bwrite,                                                   \
    devio_bread,                                                    \
    _select,                                                        \
    _get_config,                                                    \
    _set_config,                                                    \
    _ioctl                                                          \
}

#define BLOCK_DEVIO_TABLE(_l,_bwrite,_bread,_select,_get_config,_set_config)    \
devio_table_t const _l = {                                        \
    devio_cwrite,                                           \
    devio_cread,                                            \
    _bwrite,                                                    \
    _bread,                                                     \
    _select,                                                    \
    _get_config,                                                \
    _set_config,                                                \
}

#define DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config) \
        CHAR_DEVIO_TABLE(_l,_write,_read,_select,_get_config,_set_config)

typedef struct devtab_entry {
    const char        *name;
    const char        *dep_name;
    devio_table_t *handlers;
    int             (*init)(struct devtab_entry *tab);
    int        (*lookup)(struct devtab_entry **tab, 
                               struct devtab_entry *sub_tab,
                               const char *name);
    void              *priv;
    unsigned long     status;
    int              rfu;
}  DEVTABLE_TYPE devtab_entry_t;


#define DEVTAB_STATUS_AVAIL   0x0001
#define DEVTAB_STATUS_CHAR    0x1000
#define DEVTAB_STATUS_BLOCK   0x2000

extern devtab_entry_t __DEVTAB__[], __DEVTAB_END__;

#define CHAR_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
devtab_entry_t _l DEVTABLE_ENTRY(devtab) = {                   \
   _name,                                                               \
   _dep_name,                                                           \
   _handlers,                                                           \
   _init,                                                               \
   _lookup,                                                             \
   _priv,                                                               \
   DEVTAB_STATUS_CHAR,                                               \
   0    \
};

#define BLOCK_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
devtab_entry_t _l DEVTABLE_ENTRY(devtab) = {                   \
   _name,                                                               \
   _dep_name,                                                           \
   _handlers,                                                           \
   _init,                                                               \
   _lookup,                                                             \
   _priv,                                                               \
   DEVTAB_STATUS_BLOCK,                                              \
   0    \
};

#define DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv) \
        CHAR_DEVTAB_ENTRY(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)


#define DEVTAB_ENTRY_NO_INIT(_l,_name,_dep_name,_handlers,_init,_lookup,_priv)  \
devtab_entry_t _l = {                                                       \
   _name,                                                                       \
   _dep_name,                                                                   \
   _handlers,                                                                   \
   _init,                                                                       \
   _lookup,                                                                     \
   _priv,                                                                       \
   DEVTAB_STATUS_CHAR                                                       \
};

#endif /* _IO_DEVTAB_H_ */
