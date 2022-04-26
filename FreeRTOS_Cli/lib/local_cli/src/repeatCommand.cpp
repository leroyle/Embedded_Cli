#include <Arduino.h>

extern "C" {
#include "FreeRTOS_CLI.h"
}

bool RepeatCommand = false;
BaseType_t repCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)xWriteBufferLen;
    (void)pcCommandString;
    BaseType_t numChar;
    const char *argValue= FreeRTOS_CLIGetParameter(pcCommandString,1,&numChar);
  
    char retString[] = "Rep called";
    sprintf(pcWriteBuffer, "%s: numbers: %s, arg length: %lu \r\n", retString, argValue, numChar);
    if(numChar == 1)
    {
        if (argValue[0] == '0')
        {
            RepeatCommand = false;
        }
        else
        {
            RepeatCommand = true;
        }
    }
    else
    {
        sprintf(pcWriteBuffer, "Usage: rep [0|1]\r\n");
    } 
    //strncpy(pcWriteBuffer, retString,xWriteBufferLen-1);
    //pcWriteBuffer[xWriteBufferLen-1]=0;
    return pdFALSE;
}
static const CLI_Command_Definition_t repCommandStruct =
    {
        "rep",
        "rep: Repeat current command [0=Off, 1==On]\n",
        repCommand,
        1
    };

void registerRepeatCommand()
{
    FreeRTOS_CLIRegisterCommand( &repCommandStruct);
}