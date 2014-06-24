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
/*					                                                     */
/*                                                                       */
/* COMPONENT                                                             */
/*                                                                       */
/*																		 */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*************************************************************************/
#ifndef _SMS_DATA_SVC_H__
#define _SMS_DATA_SVC_H__

#include "SmsPlatDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
*			 Macros
*************************************************************************/


/*************************************************************************
*			 Enums
*************************************************************************/


/*************************************************************************
*			 Structs/Typedefs
*************************************************************************/
typedef struct SmsDataSvcFatUpdateInfo_S
{
	UINT32 FatMinorVersion;         // Minor version of the FAT taken from the FAT XML.
	UINT32 FatMajorVersion;			// Major version of the FAT taken from the FAT XML.
	UINT32 FatUpdateNum;			// Update number (0-31) of the FAT. 
	UINT32 NumFiles;				// Number of files in this update
	const char** pFilePathsArr;		// Array of strings containing the paths of the files
									// included in this update
	UINT32 Reserved[4];				// Reserved for future use
} SmsDataSvcFatUpdateInfo_ST;		 
									 
/*************************************************************************
Update begin callback
This callback pointer is a part of the initiate parameters given to SmsDataSvcInitiate.
If it is not NULL - it will be called by the add-on when a new FAT was detected.
The callback is called after the FAT was processed, and before any data files 
are written to disk. 

\param[in]	ClientPtr		A pointer supplied by the caller when he registers 
\c							the callback. It is delivered to the caller as is.
\param[in]	SvcHdl          The service handle
\param[in]	SfIndex			The service sub-frame index 
\param[in]	pFatUpdateInfo	Info about the FAT update. See #SmsDataSvcFatUpdateInfo_ST
\return		void
*************************************************************************/
typedef void (*SmsDataSvcUpdateBeginCb)( void* ClientPtr, UINT32 SvcHdl, 
										UINT32 SfIndex, SmsDataSvcFatUpdateInfo_ST* pFatUpdateInfo );

/*************************************************************************
Update finish callback
This callback pointer is a part of the initiate parameters given to SmsDataSvcInitiate.
If it is not NULL - it will be called by the add-on when a FAT processing was complete.
I.e. when the module has written all the files included in the update to file system.

\param[in]	ClientPtr		A pointer supplied by the caller when he registers 
\c							the callback. It is delivered to the caller as is.
\param[in]	SvcHdl          The service handle
\param[in]	SfIndex			The service sub-frame index 
\param[in]	pFatUpdateInfo	Info about the FAT update. See #SmsDataSvcFatUpdateInfo_ST

\return		void
*************************************************************************/
typedef void (*SmsDataSvcUpdateFinishCb)( void* ClientPtr, UINT32 SvcHdl, 
										UINT32 SfIndex, SmsDataSvcFatUpdateInfo_ST* pFatUpdateInfo);

/*************************************************************************
Service initiation parameters
Passed to #SmsDataSvcInitiate to initiate processing of a data service
*************************************************************************/
typedef struct SmsDataInitiateParams_S
{
	const char* pBaseDirPath;					// Base dir for writing the data service files
												// all paths of the delivered files will begin with 
												// this base dir.

	SmsDataSvcUpdateBeginCb pfnUpdateBeginCb;	// Update begin callback pointer - see #SmsDataSvcUpdateBeginCb
	SmsDataSvcUpdateFinishCb pfnUpdateFinishCb;	// Update finish callback pointer - see #SmsDataSvcUpdateFinishCb

	void* ClientPtr;							// A client pointer that will be passed to the begin
												// and finish callbacks
	UINT32 ReservedZero[6];
} SmsDataInitiateParams_ST;
	
/*************************************************************************
*			 Functions
*************************************************************************/

/*************************************************************************
Initiate processing of a data service
This function prepares for processing a service.
The user has to call it once for each service that needs processing.
The function allocates resources for the service - those resources are freed
when calling #SmsDataSvcCleanup.
The service is identified by a service handle and sub-frame index.

\param[in]	SvcHdl          The service handle - received from a successful
\c							Start service response 
\c							(see #SMSHOSTLIB_MSG_CMMB_START_SERVICE_RES)
\param[in]	SfIndex			The service sub-frame index. received from a successful
\c							Start service response.
\param[in]	pParams			Initial parameters - see #SmsDataInitiateParams_ST above

\return		Error code by  #SMSHOSTLIB_ERR_CODES_E enumerator.
*************************************************************************/
SMSHOSTLIB_API SMSHOSTLIB_ERR_CODES_E SmsDataSvcInitiate(UINT32 SvcHdl,
							UINT32 SfIndex, 
							SmsDataInitiateParams_ST* pParams);


/*************************************************************************
Terminate processing of a data service and free resources
This function should be called when the user wants to stop processing a 
data service.
The service is identified by a service handle and sub-frame index.
This function should be called only for services that the user has already
initiated by calling #SmsDataSvcInitiate.

\param[in]	SvcHdl          The service handle 
\param[in]	SfIndex			The service sub-frame index

\return		Error code by  #SMSHOSTLIB_ERR_CODES_E enumerator.
*************************************************************************/
SMSHOSTLIB_API SMSHOSTLIB_ERR_CODES_E SmsDataSvcCleanup(UINT32 SvcHdl, UINT32 SfIndex);


/*************************************************************************
Set a new base directory to an existing service.

The base directory of a service is set in #SmsDataSvcInitiate.
The user can change this directory during the processing of a service.
For example - after getting an "update Finish" callback - to set a 
different base directory for the next update.
The user is allowed to call this function only inside the "update begin" or
"update finish" callbacks - see #SmsDataInitiateParams_ST.
Any call to this function in a different place will result in undefined 
behavior.

\param[in]	SvcHdl          The service handle 
\param[in]	SfIndex			The service sub-frame index
\param[in]	pNewBaseDir		A string with a path to an existing directory.
\c							The module copies the string to an internal buffer.

\return		Error code by  #SMSHOSTLIB_ERR_CODES_E enumerator.
*************************************************************************/
SMSHOSTLIB_API SMSHOSTLIB_ERR_CODES_E SmsDataSvcSetBaseDir(UINT32 SvcHdl, UINT32 SfIndex, 
											   const char* pNewBaseDir);

/*************************************************************************
Process a frame that belongs to a data service.

After the user has initiated a data service, he must deliver each 
frame to the module. The module processes the frame and extracts
the service files.
The user is allowed to deliver all frames to this function - even
for services which were not initiated. In such a case the frames are
ignored and a #SMSHOSTLIB_ERR_SERVICE_DOES_NOT_EXIST value is returned.

\param[in]	SvcHdl          The service handle 
\param[in]	SfIndex			The service sub-frame index
\param[in]	pMpxFrame		A pointer to a buffer that contains the frame
\param[in]	MpxFrameSize	The frame size

\return		Error code by  #SMSHOSTLIB_ERR_CODES_E enumerator.
*************************************************************************/
SMSHOSTLIB_API SMSHOSTLIB_ERR_CODES_E SmsDataSvcProcessServiceFrame(UINT32 SvcHdl, 
							UINT32 SfIndex, 
							UINT8* pMpxFrame,
							UINT32 MpxFrameSize);


#ifdef __cplusplus
}
#endif

#endif	//_SMS_DATA_SVC_H__