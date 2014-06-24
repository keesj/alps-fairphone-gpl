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
	\file		Osw_Memory.c

	\brief		memory api linux abstraction implementation

 				This file contains the application implementation to linux critical section
*/

#include "Osw.h"
#include <stdlib.h>
#include <string.h>


/*! allocate memory
	\param[in]	size: amount of memory to allocate
	\return		pointer to the memory or NULL if error.
*/
void *OSW_MemAlloc ( UINT32 size )
{
	return malloc ( size );
}

/*! free allocated memory
	\param[in]	pMemToFree: pointer to a previously allocated memory area
*/
void OSW_MemFree ( void *pMemToFree )
{
	free ( pMemToFree );
}

