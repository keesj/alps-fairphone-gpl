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
	\file		Osw_Mutex.c

	\brief		linux mutex implementation
*/

#include "Osw.h"
#include "SmsPlatDefs.h"


/*!  create a mutex
	\param[in] 	mutex: pointer to a mutex structure
	\return		status of the operation.
*/
UINT32 OSW_MutexCreate (MUTEX * mutex )
{
	pthread_mutexattr_t attr;
	SMS_ASSERT ( mutex );

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype((pthread_mutexattr_t *)&attr, (int)PTHREAD_MUTEX_RECURSIVE_NP);

	// init mutex
	int rc = pthread_mutex_init ( mutex, &attr );
	if ( rc != 0 )
	{
		return PTHREAD_MUTEX_ERROR | rc;
	}

	return rc;
}

/*!  release a mutex
	\param[in] 	mutex: pointer to a mutex
	\return		status of the operation.
*/
UINT32 OSW_MutexDelete ( MUTEX * mutex )
{

	SMS_ASSERT ( mutex );
	// destroy mutex
	int rc = pthread_mutex_destroy ( mutex );
	if ( rc != 0 )
	{
		return PTHREAD_MUTEX_ERROR | rc;
	}

	return rc;
}

/*!  unlock a mutex
	\param[in] 	mutex: pointer to a mutex
	\return		status of the operation.
*/
UINT32 OSW_MutexPut ( MUTEX * mutex )
{
	SMS_ASSERT ( mutex );

	// unlock mutex
	int rc = pthread_mutex_unlock ( mutex );
	if ( rc != 0 )
	{
		return PTHREAD_MUTEX_ERROR | rc;
	}
	return rc;
}

/*!  lock a mutex
	\param[in] 	mutex: pointer to a mutex
	\return		status of the operation.
*/
UINT32 OSW_MutexGet ( MUTEX * mutex )
{
	SMS_ASSERT ( mutex );

	// get mutex
	int rc = pthread_mutex_lock ( mutex );
	if ( rc != 0 )
	{
		return PTHREAD_MUTEX_ERROR | rc;
	}
	return rc;
}
