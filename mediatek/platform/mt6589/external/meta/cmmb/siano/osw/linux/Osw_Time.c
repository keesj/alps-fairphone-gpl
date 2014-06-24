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
	\file		Osw_Time.c
                                                                       
	\brief		linux time functions
*/

#include "Osw.h"
#include <sys/time.h>

/*!  get the current time stamp
	\return	 time stamp in miliseconds
*/
UINT32 OSW_GetCurTimeStampInMSec ( void )
{
	struct timeval tv;
	gettimeofday ( &tv, NULL );
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/*!  calculate the time interval from a known time till now
	\param[in]	TimeStamp: the beginning of the time count
	\return		how many miliseconds elapsed since timeStamp.
*/
UINT32 OSW_GetMiliSecondsPassedSince ( UINT32 timeStamp )
{
	struct timeval tv;
	gettimeofday ( &tv, NULL );
	return tv.tv_sec * 1000 + tv.tv_usec / 1000 - timeStamp;
}
