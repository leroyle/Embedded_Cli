#ifndef __HEAPCHECK_COMMAND_H__
#define __HEAPCHECK_COMMAND_H__

void registerHeapCheckCommand();
const char * getTaskName();
TaskStatus_t * getTaskDetails(TaskStatus_t *taskDetails);

// We need to delcare sbrk
#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

#endif