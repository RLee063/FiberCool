/*
Final version must include SEH
*/
#pragma once
#include <Windows.h>
typedef enum {
	FS_READY,
	FS_EXCUTING,
	FS_DONE
}FSTATE;

typedef struct _FCONTEXT {
	
}FCONTEXT, *PFCONTEXT;

class Fiber
{
public:
	//***结构化异常处理***
	//...
	//*******************
	CONTEXT _context;

	Fiber();
	Fiber(void * prog, void * argv, void * releaseFunc);
	~Fiber();
	int getFiberState();
	void setContext(CONTEXT * pContext);
	void * getPvFiberContext();
	void setFiberState(int state);
	void * getPvParam();
private:
	FSTATE _fiberState;
	void * _pvParam;
	void * _espAllocP;
};

