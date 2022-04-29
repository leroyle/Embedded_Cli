#include <Arduino.h>

extern "C" {
#include "FreeRTOS_CLI.h"
}
#include "CLI_Impl.h"
#include "versionCommand.h"

/**
 * Print app version details
 * 
 */

void getAppVersion()

{
	printf("%s\r\n", cliAppVersion);
}

BaseType_t versionCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)xWriteBufferLen;
    (void)pcCommandString;
    BaseType_t numChar;
    const char *argValue= FreeRTOS_CLIGetParameter(pcCommandString,1,&numChar);
    pcWriteBuffer[0] = '\0';
    getAppVersion();
    
    return pdFALSE;
}

static const CLI_Command_Definition_t versionCommandStruct =
{
    "appVersion",
    "appVersion: Dump application version\r\n",
    versionCommand,
    0
};

void registerVersionCommand()
{
    FreeRTOS_CLIRegisterCommand( &versionCommandStruct);
}


/**
 * get current task details structure
 */
// TaskStatus_t *getTaskDetails(TaskStatus_t *taskDetails)
// {
//   vTaskGetInfo(NULL,
//                taskDetails,
//                pdTRUE,
//                eInvalid);

//   return taskDetails;
// }

// /** 
//  * return task name
//  */
// const char *getTaskName()
// {
//   TaskStatus_t xTaskDetails;
//   getTaskDetails(&xTaskDetails);

//   return xTaskDetails.pcTaskName;
// }

