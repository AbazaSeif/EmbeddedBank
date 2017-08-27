/*============================================================================
 *
 *      debug.h
 *
 *      
 *
 *==========================================================================*/
/*============================================================================
 * 
 * Copyright (c) 2002-2003 Innova Card.
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
 * Author(s):    Arnaud Corria 
 * Contributors:  
 * Date:          
 * Purpose:       
 * Description:
 * 
 *==========================================================================*/
#ifndef _INFRA_DEBUG_H_
#define _INFRA_DEBUG_H_	

#include <infra/diag.h>

# ifdef CONFIG_MATURITY_LEVEL_DEBUG
#   define _static_
#   define DEBUG_INIT()                    diag_init()
#   define DEBUG_TRACE(s, ...)             diag_printf(s)
#   define DEBUG_TRACE1(s, a1)             diag_printf(s, a1)
#   define DEBUG_TRACE2(s, a1, a2)         diag_printf(s, a1, a2)
#   define DEBUG_TRACE3(s, a1, a2, a3)     diag_printf(s, a1, a2, a3)
#   define DEBUG_TRACE4(s, a1, a2, a3, a4) diag_printf(s, a1, a2, a3, a4)
#   define DEBUG_REINIT()                  diag_reinit()
#   define DEBUG_GET_CHAR(c)               diag_getchar(&c)
#   define DEBUG_TERMINATE()  
#   define db_printf diag_printf
# endif

#ifdef CONFIG_MATURITY_LEVEL_RELEASE
#   define _static_ static
#   define DEBUG_INIT()                    
#   define DEBUG_TRACE(s)                  
#   define DEBUG_TRACE1(s, a1)             
#   define DEBUG_TRACE2(s, a1, a2)         
#   define DEBUG_TRACE3(s, a1, a2, a3)     
#   define DEBUG_TRACE4(s, a1, a2, a3, a4)  
#   define DEBUG_REINIT()                	(0)    
#   define DEBUG_GET_CHAR(c)                (0)
#   define DEBUG_TERMINATE()
#   define db_printf(fmt, ... )
# endif

#endif  /*  _INFRA_DEBUG_H_ */
	

