#include <Arduino.h>
#include "heapCheck.h"

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
