#include <Arduino.h>

extern "C" {
#include "FreeRTOS_CLI.h"
}

void loc_vTaskList(char * pcWriteBuffer );
static char *loc_prvWriteNameToBuffer( char *pcBuffer, const char *pcTaskName );
void dbgStackCheck();

BaseType_t stackCheckCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)xWriteBufferLen;
    (void)pcCommandString;
    BaseType_t numChar;
    const char *argValue= FreeRTOS_CLIGetParameter(pcCommandString,1,&numChar);
    pcWriteBuffer[0] = '\0';
    dbgStackCheck();
    
    return pdFALSE;
}

static const CLI_Command_Definition_t stackCheckCommandStruct =
{
    "stackCheck",
    "stackCheck: Dump Stack Statistics\r\n",
    stackCheckCommand,
    0
};

void registerStackCheckCommand()
{
    FreeRTOS_CLIRegisterCommand( &stackCheckCommandStruct);
}

void dbgStackCheck()
{
// Print Task list with stack left stat
  uint32_t tasknum = uxTaskGetNumberOfTasks();
  char* buf = (char*) rtos_malloc(tasknum*40); // 40 bytes per task

  loc_vTaskList(buf);

  PRINTF("Task    State   Prio  StackLeft Num    Base Address   Approx Size(Bytes/Words\r\n");
  PRINTF("-------------------------------------------------------------------------------\r\n");
  PRINTF(buf);
  PRINTF("\n");
  rtos_free(buf);

}

/**
 * @brief This was copied from the FreeRTOS implementation file at:
 *  .platformio/packages/framework-arduinoadafruitnrf52/cores/nRF5/freertos/Source/tasks.c
 *  It's been modified to dump the stack start address as well
 *  as trying to fetch the allocated stack size
 * @param pcWriteBuffer 
 */
void loc_vTaskList(char * pcWriteBuffer )
	{
	#define tskRUNNING_CHAR		( 'X' )
	#define tskBLOCKED_CHAR		( 'B' )
	#define tskREADY_CHAR		( 'R' )
	#define tskDELETED_CHAR		( 'D' )
	#define tskSUSPENDED_CHAR	( 'S' )
	
	TaskStatus_t *pxTaskStatusArray;
	volatile UBaseType_t uxArraySize, x;
	char cStatus;
	volatile UBaseType_t uxCurrentNumberOfTasks 	= ( UBaseType_t ) 0U;

		/*
		 * PLEASE NOTE:
		 *
		 * This function is provided for convenience only, and is used by many
		 * of the demo applications.  Do not consider it to be part of the
		 * scheduler.
		 *
		 * vTaskList() calls uxTaskGetSystemState(), then formats part of the
		 * uxTaskGetSystemState() output into a human readable table that
		 * displays task names, states and stack usage.
		 *
		 * vTaskList() has a dependency on the sprintf() C library function that
		 * might bloat the code size, use a lot of stack, and provide different
		 * results on different platforms.  An alternative, tiny, third party,
		 * and limited functionality implementation of sprintf() is provided in
		 * many of the FreeRTOS/Demo sub-directories in a file called
		 * printf-stdarg.c (note printf-stdarg.c does not provide a full
		 * snprintf() implementation!).
		 *
		 * It is recommended that production systems call uxTaskGetSystemState()
		 * directly to get access to raw stats data, rather than indirectly
		 * through a call to vTaskList().
		 */


		/* Make sure the write buffer does not contain a string. */
		*pcWriteBuffer = 0x00;

		/* Take a snapshot of the number of tasks in case it changes while this
		function is executing. */
		uxCurrentNumberOfTasks = uxTaskGetNumberOfTasks();
		
		uxArraySize = uxCurrentNumberOfTasks;

		/* Allocate an array index for each task.  NOTE!  if
		configSUPPORT_DYNAMIC_ALLOCATION is set to 0 then pvPortMalloc() will
		equate to NULL. */
		pxTaskStatusArray = (TaskStatus_t *) pvPortMalloc( uxCurrentNumberOfTasks * sizeof( TaskStatus_t ) );

		if( pxTaskStatusArray != NULL )
		{
			/* Generate the (binary) data. */
			uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, NULL );

			/* Create a human readable table from the binary data. */
			for( x = 0; x < uxArraySize; x++ )
			{

				switch( pxTaskStatusArray[ x ].eCurrentState )
				{
					case eRunning:		cStatus = tskRUNNING_CHAR;
										break;

					case eReady:		cStatus = tskREADY_CHAR;
										break;

					case eBlocked:		cStatus = tskBLOCKED_CHAR;
										break;

					case eSuspended:	cStatus = tskSUSPENDED_CHAR;
										break;

					case eDeleted:		cStatus = tskDELETED_CHAR;
										break;

					default:			/* Should not get here, but it is included
										to prevent static checking errors. */
										cStatus = 0x00;
										break;
				}

				/* Write the task name to the string, padding with spaces so it
				can be printed in tabular form more easily. */
				pcWriteBuffer = loc_prvWriteNameToBuffer( pcWriteBuffer, pxTaskStatusArray[ x ].pcTaskName );
				/* Write the rest of the string. */
				
				// trying to get to the size of the allocated stack buffer
				// the size seems to be stored at an address just before the returned
				// stack address pointer. Sometimes pointer -1, sometimes pointer -2, not sure
				// why the difference at this point.
				// Some of the tasks are created via xTaskCreateStatic()
				// which uses a different stack creation alogrithm than does the non static version 
				volatile int32_t myValue = 0;
				// PRINTF("Name: %s\r\n", pxTaskStatusArray[x].pcTaskName);
				myValue = *(pxTaskStatusArray[x].pxStackBase-2);
				// PRINTF("Value 2: %d\r\n", myValue);
				
				if (myValue < (int32_t) 20 || myValue == -1 )
				{
					myValue = *(pxTaskStatusArray[x].pxStackBase-1);
				 	// PRINTF("Value 1: %d\r\n", myValue);
					 if (myValue < (int32_t) 20)
					{
						myValue = *(pxTaskStatusArray[x].pxStackBase-0);
						// PRINTF("Value 0: %d\r\n", myValue);
						if (myValue < (int32_t) 20)
						{
							myValue = 0;
							// PRINTF("Value Default: %d\r\n", myValue);
						}
					}
				}
				if (myValue != 0)
				{
					myValue = myValue/4;
				}
				// sprintf( pcWriteBuffer, "\t%c\t%u\t%u\t%u\r\n", cStatus, ( unsigned int ) pxTaskStatusArray[ x ].uxCurrentPriority, ( unsigned int ) pxTaskStatusArray[ x ].usStackHighWaterMark, ( unsigned int ) pxTaskStatusArray[ x ].xTaskNumber);
				sprintf( pcWriteBuffer, "\t%c\t%u\t%u\t%u\t%p\t%d/%d\r\n", cStatus, ( unsigned int ) pxTaskStatusArray[ x ].uxCurrentPriority, ( unsigned int ) pxTaskStatusArray[ x ].usStackHighWaterMark, ( unsigned int ) pxTaskStatusArray[ x ].xTaskNumber, pxTaskStatusArray[x].pxStackBase, *(pxTaskStatusArray[x].pxStackBase-2), myValue );
				pcWriteBuffer += strlen( pcWriteBuffer );
			
			}

			/* Free the array again.  NOTE!  If configSUPPORT_DYNAMIC_ALLOCATION
			is 0 then vPortFree() will be #defined to nothing. */
			vPortFree( pxTaskStatusArray );
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}

/**
 * @brief copied from FreeRTOS implementation
 * 
 * @param pcBuffer 
 * @param pcTaskName 
 * @return char* 
 */
static char *loc_prvWriteNameToBuffer( char *pcBuffer, const char *pcTaskName )
	{
	size_t x;

		/* Start by copying the entire string. */
		strcpy( pcBuffer, pcTaskName );

		/* Pad the end of the string with spaces to ensure columns line up when
		printed out. */
		for( x = strlen( pcBuffer ); x < ( size_t ) ( configMAX_TASK_NAME_LEN - 1 ); x++ )
		{
			pcBuffer[ x ] = ' ';
		}

		/* Terminate. */
		pcBuffer[ x ] = 0x00;

		/* Return the new end of string. */
		return &( pcBuffer[ x ] );
	}
