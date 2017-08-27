/*============================================================================
 *
 *      error.h
 *
 *      
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
 * Contributors:  Arnaud Ferir
 * Date:          
 * Purpose:       Common error code definitions
 * Description:
 * 
 *==========================================================================*/
#ifndef INFRA_ERROR_H
#define INFRA_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/* TYPE DEFINITIONS */

/* A type for error codes which may be useful to explain the purpose of
 * a variable or return code. It shows that it contains an error code
 * of the type defined below */

typedef int result_t;

#define MAKE_ERROR(_id_, _error_) ((_id_ << 16) + _error_)


/**
 *  
 * @defgroup Error_Codes Error Codes
 * 
 * This chapter contains descriptions of all error codes used by INNOVA CARD 
 * USIP® Professional Hardware Abstraction Layer. It conforms to the ANSI/POSIX 
 * error code format. 
 * 
 * The error codes returned by the HAL functions are always the negated values 
 * of the numbers given in this description. 
 * 
 * @{
 * 
 */

 
/* CONSTANT DEFINITIONS */

/* If adding to this list, you must also update strerror() with its text
 * If there is a common error of the same purpose on Unix, try and use its
 * name and number. If not, use one above 200 to prevent future conflicts
 *
 * Do not use negative numbers, so that functions can return positive on
 * success and -ERR_SOMETHING on error, and it all works consistently.
*/


/** \showinitializer No error */
#define ERR_NO              0    
/** \showinitializer Not permitted */
#define ERR_PERM            1    
/** \showinitializer No such entity */
#define ERR_NOENT           2     
/** \showinitializer No such process */
#define ERR_SRCH            3    
/** \showinitializer Operation interrupted */ 
#define ERR_INTR            4    
/** \showinitializer I/O error */
#define ERR_IO              5    
/** \showinitializer Bad handle */
#define ERR_BADF            9     
/** \showinitializer Try again later */
#define ERR_AGAIN           11    
/** \showinitializer */
#define ERR_WOULDBLOCK      ERR_AGAIN
/** \showinitializer Out of memory */
#define ERR_NOMEM           12
/** \showinitializer Resource busy */    
#define ERR_BUSY            16    
/** \showinitializer Cross-device link */ 
#define ERR_XDEV            18    
/** \showinitializer No such device */   
#define ERR_NODEV           19    
/** \showinitializer Not a directory */
#define ERR_NOTDIR          20    
/** \showinitializer Is a directory */    
#define ERR_ISDIR           21    
/** \showinitializer Invalid argument */
#define ERR_INVAL           22    
/** \showinitializer Too many open files in system */
#define ERR_NFILE           23    
/** \showinitializer Too many open files */
#define ERR_MFILE           24    
/** \showinitializer File too large */    
#define ERR_FBIG            27    
/** \showinitializer No space left on device */
#define ERR_NOSPC           28    
/** \showinitializer Illegal seek */
#define ERR_SPIPE           29    
/** \showinitializer Read-only file system */    
#define ERR_ROFS            30    
/** \showinitializer Argument to math function outside valid */
#define ERR_DOM             33    

                               /** domain */
/** \showinitializer Math result cannot be represented */
#define ERR_RANGE           34    
/** \showinitializer Resource deadlock would occur */
#define ERR_DEADLK          35    
/** \showinitializer Resource deadlock would occur */
#define ERR_DEADLOCK        ERR_DEADLK 
/** \showinitializer Function not implemented */
#define ERR_NOSYS           38    
/** \showinitializer File name too long */  
#define ERR_NAMETOOLONG     60    

/** \showinitializer Not supported error */  
#define ERR_NOTSUP          95    

/** \showinitializer End of file reached */
#define ERR_EOF             200

/** \showinitializer Operation not supported */
#define ERR_NOSUPP          201   
/** \showinitializer Device does not support this operation */
#define ERR_DEVNOSUPP       202   
    
/** Additional errors used by networking */

/** \showinitializer Device not configured */
#define ERR_NXIO            300   
/** \showinitializer Permission denied */
#define ERR_ACCES           301   
/** \showinitializer File exists */
#define ERR_EXIST           302   

/** \showinitializer Inappropriate ioctl for device */
#define ERR_NOTTY           303   
/** \showinitializer Broken pipe */
#define ERR_PIPE            304   

/** non-blocking and interrupt i/o */
/** \showinitializer Operation now in progress */
#define ERR_INPROGRESS      310   

/** \showinitializer Operation already in progress */
#define ERR_ALREADY         311   

/** \showinitializer ipc/network software -- argument errors */
/** \showinitializer Socket operation on non-socket */
#define ERR_NOTSOCK         320   
/** \showinitializer Destination address required */
#define ERR_DESTADDRREQ     321   
/** \showinitializer Message too long */
#define ERR_MSGSIZE         322   
/** \showinitializer Protocol wrong type for socket */
#define ERR_PROTOTYPE       323   
/** \showinitializer Protocol not available */
#define ERR_NOPROTOOPT      324   
/** \showinitializer Protocol not supported */
#define ERR_PROTONOSUPPORT  325   
/** \showinitializer Socket type not supported */
#define ERR_SOCKTNOSUPPORT  326   

/** \showinitializer Operation not supported */
#define ERR_OPNOTSUPP       327  
/** \showinitializer Protocol family not supported */
#define ERR_PFNOSUPPORT     328   
/** \showinitializer Address family not supported by */
#define ERR_EAFNOSUPPORT     329   
                               /** \showinitializer protocol family */
/** \showinitializer Address already in use */
#define ERR_ADDRINUSE       330   
/** \showinitializer Can't assign requested address */
#define ERR_ADDRNOTAVAIL    331   

/** \showinitializer ipc/network software -- operational errors */
/** \showinitializer Network is down */
#define ERR_NETDOWN         350   
/** \showinitializer Network is unreachable */
#define ERR_NETUNREACH      351   
/** \showinitializer Network dropped connection on reset */
#define ERR_NETRESET        352   
/** \showinitializer Software caused connection abort */
#define ERR_CONNABORTED     353   
/** \showinitializer Connection reset by peer */
#define ERR_CONNRESET       354   
/** \showinitializer No buffer space available */
#define ERR_NOBUFS          355   
/** \showinitializer Socket is already connected */
#define ERR_ISCONN          356   
/** \showinitializer Socket is not connected */
#define ERR_NOTCONN         357   
/** \showinitializer Can't send after socket shutdown */
#define ERR_SHUTDOWN        358   
/** \showinitializer Too many references: can't splice */
#define ERR_TOOMANYREFS     359   

/** \showinitializer Operation timed out */
#define ERR_TIMEDOUT        360  
 
/** \showinitializer Connection refused */
#define ERR_CONNREFUSED     361   

/** \showinitializer Host is down */
#define ERR_HOSTDOWN        364   
/** \showinitializer No route to host */
#define ERR_HOSTUNREACH     365   

/**  @} */

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* INFRA_ERROR_H */


