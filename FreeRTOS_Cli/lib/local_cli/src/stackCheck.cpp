#include <Arduino.h>

extern "C" {
#include "FreeRTOS_CLI.h"
}

BaseType_t stackCheckCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)xWriteBufferLen;
    (void)pcCommandString;
    BaseType_t numChar;
    const char *argValue= FreeRTOS_CLIGetParameter(pcCommandString,1,&numChar);
    pcWriteBuffer[0] = '\0';
    dbgMemInfo();
    
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