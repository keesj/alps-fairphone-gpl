/*************************************************************************/
/*                                                                       */
/* Copyright (C) 2005-2009 Siano Mobile Silicon Ltd. All rights reserved */
/*                                                                       */
/* PROPRIETARY RIGHTS of Siano Mobile Silicon are involved in the        */
/* subject matter of this material.  All manufacturing, reproduction,    */
/* use, and sales rights pertaining to this subject matter are governed  */
/* by the license agreement.  The recipient of this software implicitly  */
/* accepts the terms of the license.                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

#include "SmsHostLibTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _SMS_HOST_UTILS_H_
#define _SMS_HOST_UTILS_H_

SMSHOSTLIB_API UINT32 SmsCRC32Compute(UINT32 InitialVector, const UINT8* pData, INT32 Len);
UINT32 SmsCRC8Compute(UINT8 initialVector, const UINT8* pData, UINT32 len);


#ifdef __cplusplus
}
#endif

#endif //_SMS_HOST_UTILS_H_

