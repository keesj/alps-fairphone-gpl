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
	\file		Osw_Event.c

	\brief		Linux event implementation

 				This file contains the application implementation to linux critical section
*/

#include "Osw.h"
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

/*! create new event
	\param[in]	event: pointer to the event structure instance
	\return		always 0
*/
UINT32 OSW_EventCreate ( Event * pEvent)
{
	if (pEvent)
	{
		// init mutex for event
		pthread_mutex_init(&pEvent->mutex, NULL);
		// init condition variable
		pthread_cond_init(&pEvent->cond, NULL);
		pEvent->set = 0;
		return 0;
	}
	
	return 1;
}

/*! destroy the event
	\param[in]	event: pointer to the event structure instance
	\return		always 0
*/
UINT32 OSW_EventDelete ( Event * pEvent)
{
	if (pEvent)
	{
		// destroy mutex
		pthread_mutex_destroy(&pEvent->mutex);
		// destroy condition variable
		pthread_cond_destroy(&pEvent->cond);
		return 0;
	}

	return 1;
}

/*! set the event
	\param[in]	event: pointer to the event structure instance
	\return		error status
*/
UINT32 OSW_EventSet ( Event * pEvent)
{
	int rc = 0;

	// critical section
	rc = pthread_mutex_lock ( &pEvent->mutex );
	if ( rc != 0 )
	{
		// exit critical section
		rc = pthread_mutex_unlock (  &pEvent->mutex );
		return rc | PTHREAD_MUTEX_ERROR;
	}
	// set "event set" flag
	pEvent->set = 1;
	// signal waiting threads
	rc = pthread_cond_signal ( &pEvent->cond );
	if ( rc != 0 )
	{
		pthread_mutex_unlock(&pEvent->mutex);
		return rc | PTHREAD_COND_VAR_ERROR;
	}
	// exit critical section
	rc = pthread_mutex_unlock (  &pEvent->mutex );
	if ( rc != 0 )
	{
		return rc | PTHREAD_MUTEX_ERROR;
	}

	return rc;
}

/*! reset the event
	\param[in]	event: pointer to the event structure instance
	\return		error status
*/
UINT32 OSW_EventClear ( Event * pEvent)
{
	int rc = 0;

	// critical section
	rc = pthread_mutex_lock ( &pEvent->mutex );
	if ( rc != 0 )
	{
		// exit critical section
		rc = pthread_mutex_unlock (  &pEvent->mutex );
		return rc | PTHREAD_MUTEX_ERROR;
	}

	// clear "even set" flag
	pEvent->set = 0;

	// exit critical section
	rc = pthread_mutex_unlock (  &pEvent->mutex );
	if ( rc != 0 )
	{
		return rc | PTHREAD_MUTEX_ERROR;
	}

	return 0;
}

/*! wait on the event
	\param[in]	event: pointer to the event structure instance
	\param[in]	Timeout: timeout to return from this call even if the event is not acquired
	\return		error status
*/
UINT32 OSW_EventWait ( Event * pEvent, UINT32 Timeout )
{
	int rc = 0;
	UINT32 OswRc = OSW_OK;

	// critical section
	pthread_mutex_lock ( &pEvent->mutex );

	// check "event set" flag
	if ( pEvent->set )
	{
		// if already set reset and return immidiately
		pEvent->set = 0;
		pthread_mutex_unlock ( &pEvent->mutex );
		return 0;
	}
	// if wait forever
	if(OSW_WAIT_FOREVER == Timeout)
	{
		// wait forever
		pthread_cond_wait ( &pEvent->cond, &pEvent->mutex );
		pEvent->set = 0;
	}
	else
	{
		// prepare timer for timeout
		struct timeval now;
		struct timespec timeout;
		gettimeofday(&now, NULL);
		// calculate wakeup time
		timeout.tv_sec = now.tv_sec + (Timeout/1000);
		timeout.tv_nsec = (now.tv_usec*1000) + ((Timeout % 1000) * 1000000);
		if (timeout.tv_nsec >= 1000000000)
		{
			timeout.tv_nsec -= 1000000000;
			timeout.tv_sec++;			
		}

		// Wait for condition variable with timeout
		rc = pthread_cond_timedwait ( &pEvent->cond, &pEvent->mutex, &timeout);
		if(!rc)
		{
			pEvent->set = 0;		
		}
		else
		{
			OswRc = rc;
			if ( rc == ETIMEDOUT )
			{
				OswRc = OSW_TIMEOUT;
			}
		}
	}

	// exit critical section
	pthread_mutex_unlock (  &pEvent->mutex );
	return OswRc;
}

