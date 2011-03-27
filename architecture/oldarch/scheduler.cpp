
#define THREAD_SIZE 64

class TaskQueue;
class DSPThreadPool;

// Globals
TaskQueue* gTaskQueueList[THREAD_SIZE] = {0};
DSPThreadPool* gThreadPool = 0;
int gClientCount = 0;
