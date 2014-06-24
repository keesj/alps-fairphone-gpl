/*******************************************************************************
 *
 * Filename:
 * ---------
 *   tst_main.h
 *
 * Project:
 * --------
 *   YUSU
 *
 * Description:
 * ------------
 *    header file of main function
 *
 * Author:
 * -------
 *   Lu.Zhang (MTK80251) 09/11/2009
 *
 *------------------------------------------------------------------------------
 * $Revision:$
 * $Modtime:$
 * $Log:$
 *
 * 05 11 2010 lu.zhang
 * [ALPS00005327]CCAP 
 * .
 *
 * 01 20 2010 lu.zhang
 * [ALPS00004332]Create META 
 * .
 *
 *
 *
 *
 *
 *******************************************************************************/
#ifndef __FT_MAIN_H__
#define __FT_MAIN_H__

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/timeb.h>


#include "WM2Linux.h"
#include "meta.h"

#define  MAX_TST_TX_BUFFER_LENGTH            (4096*8)


#ifdef __cplusplus
extern "C" {
#endif

//the standard stream interface of ft module's
int   FTT_Init( int dwContext);
void FT_DispatchMessage(void *pLocalBuf, void *pPeerBuf, int local_len, int peer_len);
int    FTT_Deinit( int hDeviceContext );
void FTMuxPrimitiveData(META_RX_DATA *pMuxBuf);

#ifdef __cplusplus
}
#endif




#endif

