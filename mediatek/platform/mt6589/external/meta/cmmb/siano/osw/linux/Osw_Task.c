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
	\file		Osw_Task.c
                                                                       
	\brief		linux thread implementation
*/

#include <time.h>
#include <stdlib.h>
#include "Osw.h"
#include "SmsPlatDefs.h"

typedef void *(*PthreadTaskFunc)(void*);

/*!  create a task
	\param[in]	TaskName: name of the Task
	\param[in]	TaskPriority: priority of the task
	\param[in]	TaskStackSize: stack size of the Task
	\param[in]	TaskFunction: the function that this task will run
	\param[in]	TaskFunctionParams: parameters to be passed to the task function
	\return		handle to the task.
*/
OSW_TaskId OSW_TaskCreate ( const char *TaskName,
					   UINT32 TaskPriority,
					   UINT32 TaskStackSize,
					   TaskFunc TaskFunction,
					   void *TaskFunctionParams )
{
	pthread_t *TaskHandle;
	pthread_attr_t attr;

	// allocate memory for task structure
	TaskHandle = (pthread_t*)malloc(sizeof(pthread_t));

	pthread_attr_init(&attr);
	pthread_attr_setstacksize (&attr, TaskStackSize);
	
	// create linux thread
	pthread_create ( TaskHandle, &attr,
					 (PthreadTaskFunc)TaskFunction,
					 TaskFunctionParams );
	if ( *TaskHandle == 0 )
	{
		// if failed - free task structure
		free(TaskHandle);
		return NULL;
	}

	return (void*)TaskHandle;
}

/*!  cancel a task
	\param[in]	pTask: handle to the task.
*/
void OSW_TaskCleanup ( OSW_TaskId pTask )
{
	// android don't support pthread_cancel
	//// cancel thread
	//pthread_cancel ( *(pthread_t*)pTask );

	// free task structure
	free((pthread_t*)pTask);
}

/*!  sleep
	\param[in]	TaskSleepPeriod: time to sleep.
*/
void OSW_TaskSleep ( UINT32 TaskSleepPeriod )
{
	struct timespec ts, tr;
	
	// calculate wakeup time
	ts.tv_sec = TaskSleepPeriod / 1000;
	ts.tv_nsec = ( TaskSleepPeriod % 1000 ) * 1000000;
	// sleep
	nanosleep ( &ts, &tr );
}

/*!  unimplemented */
OSW_TaskId OSW_TaskGetCurrent ( void )
{
	return NULL;
}

