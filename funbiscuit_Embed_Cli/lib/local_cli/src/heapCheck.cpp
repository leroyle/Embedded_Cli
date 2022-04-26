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

  // values from app linker .map file
  // Name   Origin             Length             Attributes
  // FLASH  0x0000000000026000 0x00000000000c7000 xr
  // RAM    0x0000000020006000 0x000000000003a000 xrw
  // StackStart == ram origin + Length
  // 0x20040000    = 0x20006000 + 0x3a000

  uint32_t stackStart = 0x20040000; // value from app linker map file
  uint32_t ramEnd = stackStart + 1;
  uint32_t sbrkVal = (uint32_t) reinterpret_cast<char *>(sbrk(0));
  uint32_t ramLeft = ramEnd - sbrkVal;
  printf(PSTR("\r\n(%s): Heap Space Check() =======> \r\n"), xTaskDetails.pcTaskName);
  printf(PSTR("\tCurrent sbrk() value: 0x%x\r\n\tAvailable Memory:     0x%x\r\n"), (unsigned int)sbrkVal, (unsigned int)ramLeft);
  printf(PSTR("Heap Space Check() =======> \r\n\r\n"));
  return ramLeft;
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