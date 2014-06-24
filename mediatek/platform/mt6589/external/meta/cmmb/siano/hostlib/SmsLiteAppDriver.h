/*************************************************************************/
/*                                                                       */
/* Copyright (C) 2005,2006 Siano Mobile Silicon Ltd. All rights reserved */
/*                                                                       */
/* PROPRIETARY RIGHTS of Siano Mobile Silicon are involved in the        */
/* subject matter of this material.  All manufacturing, reproduction,    */
/* use, and sales rights pertaining to this subject matter are governed  */
/* by the license agreement.  The recipient of this software implicitly  */
/* accepts the terms of the license.                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/*************************************************************************/
/*                                                                       */
/* FILE NAME                                                             */
/*                                                                       */
/*      AppDriver.c                                                      */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/*      Application driver unified interface   	                         */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*************************************************************************/

#ifndef _APP_DRIVER_INT_H
#define _APP_DRIVER_INT_H

#include "SmsHostLibTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	ADR_CTRL_HANDLE		0

///////////////////////////////////////////////////////////////////////////////
/*! 
	Plug n Play events notification callback
	This function is registered by the host lib in #ADR_Init
	It is called when a PNP event occurs - when a new device 
	appears or when a device disconnects

\param[in]	DeviceHandle	ADR Device handle of the device that connected or disconnected
\param[in]	DeviceName	Name of the device
\param[in]	IsDeviceConnected	Indicated whether this event is a connect event or a disconnect event
								if IsDeviceConnected is TRUE, then it is an event for a new device
\param[in]	CurrentMode		The current mode of the device - #SMSHOSTLIB_ERR_CODES_E when notifying
							about a new device. In case of disconnect (IsDeviceConnected==FALSE) the
							mode will be set to #SMSHOSTLIB_DEVMD_NONE
*/

	///////////////////////////////////////////////////////////////////////////////
/*! 
	Handle callback
	This callback is registered by the host lib or data lib in #ADR_OpenHandle
	It is called for delivering asynchronous information of that handle

\param[in]	handle_num	The handle number
\param[in]	p_buffer	A buffer containing the new data from that handle
\param[in]	buff_size	The size of p_buffer in bytes

*/
typedef void ( *SmsLiteAdr_pfnFuncCb )( UINT32 handle_num, UINT8* p_buffer, UINT32 buff_size );


///////////////////////////////////////////////////////////////////////////////
/*! 
	Stream Driver Initialization. 

	\param[in]	e_comm_type	Communication type
	\param[in]	p_params	Driver dependent extra parameters
	\param[in]	pfPnPCbFunc	Callback for client plug and play event

	\return		#SMSHOSTLIB_ERR_CODES_E	Return code.
*/
SMSHOSTLIB_ERR_CODES_E SmsLiteAdrInit( SMSHOSTLIB_DEVICE_MODES_E DeviceMode, 
									  SmsLiteAdr_pfnFuncCb pfnControlCb, 
									  SmsLiteAdr_pfnFuncCb pfnDataCb );

///////////////////////////////////////////////////////////////////////////////
/*! 
	Stream Driver Termination. 

	\return		#SMSHOSTLIB_ERR_CODES_E	Return code.
*/
SMSHOSTLIB_ERR_CODES_E SmsLiteAdrTerminate( void );

///////////////////////////////////////////////////////////////////////////////
/*! 
	Write message (little-endian ordering).
	
	\param[in]	DeviceHandle	Handle return from call to #ADR_OpenHandle.
	\param[in]	p_msg			Pointer to a message to write

	\return		#SMSHOSTLIB_ERR_CODES_E	Return code.
*/
SMSHOSTLIB_ERR_CODES_E SmsLiteAdrWriteMsg( SmsMsgData_ST* p_msg );

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif // _APP_DRIVER_INT_H
