#include <Arduino.h>

extern "C" {
#include "FreeRTOS_CLI.h"
}
#include "heapCheck.h"

uint32_t checkHeapSpace();

BaseType_t heapCheckCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)xWriteBufferLen;
    (void)pcCommandString;
    BaseType_t numChar;
    const char *argValue= FreeRTOS_CLIGetParameter(pcCommandString,1,&numChar);
    pcWriteBuffer[0] = '\0';
    checkHeapSpace();
    
    return pdFALSE;
}

static const CLI_Command_Definition_t heapCheckCommandStruct =
{
    "heapCheck",
    "heapCheck: Dump Heap Statistics\r\n",
    heapCheckCommand,
    0
};

void registerHeapCheckCommand()
{
    FreeRTOS_CLIRegisterCommand( &heapCheckCommandStruct);
}

/**
 * Print heap details
 * 
 */

uint32_t checkHeapSpace()
{

  TaskStatus_t xTaskDetails;
  getTaskDetails(&xTaskDetails);

  // The called functions use info from the linker .map file
  // extern unsigned char __HeapBase[];
  // extern unsigned char __HeapLimit[];
  
  uint32_t sbrkVal = (uint32_t ) reinterpret_cast<char*>(sbrk(0));
  printf(PSTR("\r\n(%s): Heap Space Check()\r\n=========================> \r\n"), xTaskDetails.pcTaskName);
  printf(PSTR("Current sbrk() value: 0x%x\r\n"), (unsigned int)sbrkVal);
  int total = dbgHeapTotal(); 
  int used = dbgHeapUsed();
  int free =  dbgHeapFree();

  printf("Total:  %d (0x%x) \r\nUsed:   %d (0x%x) \r\nFree:   %d (0x%x)\r\n", total, total, used, used, free, free);
  printf(PSTR("=========================> \r\n\r\n"));
 
  return dbgHeapFree();
}

/**
 * get current task details structure
 */
TaskStatus_t *getTaskDetails(TaskStatus_t *taskDetails)
{
  vTaskGetInfo(NULL,
               taskDetails,
               pdTRUE,
               eInvalid);

  return taskDetails;
}

/** 
 * return task name
 */
const char *getTaskName()
{
  TaskStatus_t xTaskDetails;
  getTaskDetails(&xTaskDetails);

  return xTaskDetails.pcTaskName;
}
