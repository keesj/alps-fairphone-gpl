/****************************************************************

Siano Mobile Silicon, Inc. 
MDTV receiver kernel modules. 
Copyright (C) 2006-2008, Uri Shkolnik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

 This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************/
/*!  
	\file		SmsPlatDefs.h
	
	\brief		Platform dependent types and definitions
*/


#ifndef SMS_LINUX_DEFS_H
#define SMS_LINUX_DEFS_H

#ifdef __cplusplus
extern "C"{
#endif

/*********************/
/* Platform Includes */
/*********************/
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <memory.h>


/***********/
/* Defines */
/***********/

typedef unsigned char		UINT8;
typedef signed char				INT8;
typedef unsigned short		UINT16;
typedef short				INT16;
typedef unsigned int		UINT32;
typedef int				INT32;
typedef long long			INT64;
typedef unsigned long long	UINT64;

typedef unsigned long		BOOL;

#define FALSE				0
#define TRUE				1

#define IN
#define OUT

#define SMS_ASSERT(x)		assert(x)

#define ARGUSE(x)

typedef enum
{
	OSW_TASK_PRI_LOW	= 0,
	OSW_TASK_PRI_NORMAL	= 1,
	OSW_TASK_PRI_HIGH	= 2
} OSW_TASK_PRI;

// Tasks stack size
#define OSW_SMSHOSTLIBTASK_STACK					( 0x800 )
#define OSW_SMSHOSTMONITORTASK_STACK				( 0x800 )
#define OSW_SMSHOSTLIBTASK_SRVM_STACK				( 0x800 )
#define OSW_SMSHOSTLIBTASK_SCAN_STACK				( 0x800 )
#define OSW_SMSHOSTLIB_WAKEUP_TASK_STACK			( 0x800 )
#define OSW_SMSHOSTLIB_ICALL_TASK_STACK				( 0x800 )


#define OSW_SMSHOSTLIBTASK_PRI						OSW_TASK_PRI_NORMAL
#define OSW_SMSHOSTMONITORTASK_PRI					OSW_TASK_PRI_NORMAL
#define OSW_SMSHOSTLIB_ICALL_TASK_PRI				OSW_TASK_PRI_NORMAL
#define OSW_SMSHOSTLIBTASK_SCAN_PRI					OSW_TASK_PRI_NORMAL
#define OSW_SMSHOSTLIB_WAKEUP_TASK_PRI				OSW_TASK_PRI_NORMAL

//cover up for windows specific garbage in the code
#define INFINITE 0

#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT  1
#define WAIT_FAILED   2

//! error codes for the os abstraction layer
#define PTHREAD_MUTEX_ERROR 1000
#define PTHREAD_COND_VAR_ERROR 2000
#define PTHREAD_ERROR 3000
#define PTHREAD_ATTR_ERROR 4000

/**********/
/* Types */
/**********/


/**********************************/
/* Platform OSW types and defines */
/**********************************/

//! Task type
typedef void* OSW_TaskId;

//! Mutex type
typedef pthread_mutex_t MUTEX;	//!< linux mutex definition

//! File type
typedef FILE* OSW_FILEHANDLE;

//! the linux event representation
typedef struct
{
	int set;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} Event;

// Timer types
/*! prototype for the timer's callback function
	\param[in]	lpArgToCompletionRoutine: opaque data supplied at timer creation
	\param[in] 	dwTimerLowValue: timer low value
	\param[in] 	dwTimerHighValue: timer high value
*/
typedef void (*TimerCBFunc) (
			  void *lpArgToCompletionRoutine,
			  UINT32 dwTimerLowValue,
			  UINT32 dwTimerHighValue );

/**************/
/* Debug Logs */
/**************/
#define SMSHOST_ENABLE_LOGS

#ifdef SMSHOST_ENABLE_LOGS

#define SMSHOST_FILE		__FILE__
#define SMSHOST_LINE		__LINE__
#define SMSHOST_FUNCTION	__FUNCTION__

#include <utils/Log.h>

#define USER_PRINTF(mask,log_str) \
	printf("%s\n", log_str); \
	ALOGE("%s\n", log_str)

#define SMSHOST_DEFAULT_LOG_MASK (0xFFFFFFFF)

#endif

#ifdef __cplusplus
}
#endif

#endif  /* SMS_LINUX_DEFS_H */
