#include "Fiber.h"
#include <Windows.h>
class Fiber
{
public:
	//***结构化异常处理***
	//...
	//*******************
	Fiber();
	Fiber(void * prog, void * argv, void * releaseFunc);
	~Fiber();
	int getFiberState();
	void setContext(void * pContext);
	void * getPvFiberContext();
	void setFiberState(int state);
private:
	CONTEXT _context;
	FSTATE _fiberState;
	void * _pvParam;					
};

Fiber::Fiber() {
	//***set return value
	_fiberState = FS_EXCUTING;
}

Fiber::Fiber(void * prog, void * pvParam, void * releaseFunc){
	//***set return value
	_context.Esp = (DWORD)new char[1000];
	_context.Eip = (DWORD)prog;
	this->_pvParam = pvParam;
	int * pvStack = (int*)_context.Esp;
	*pvStack = (int)pvParam;
	*(pvStack + 1) = (int)releaseFunc;
	_context.Esp = (DWORD)(pvStack + 2);
	_fiberState = FS_READY;
}

Fiber::~Fiber() { 
	//may have someting wrong here
	delete [] (char*)this->_context.Esp;
} 

int Fiber::getFiberState() {
	return _fiberState;
}

void Fiber::setContext(void * pContext) {
	_context = *(PCONTEXT)pContext;
	return;
}

void * Fiber::getPvFiberContext() {
	return &_context;
}

void Fiber::setFiberState(int state) {
	_fiberState = (FSTATE)state;
}