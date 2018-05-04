#include "Fiber.h"
#include <Windows.h>
class Fiber
{
public:
	//***结构化异常处理***
	//...
	//*******************
	Fiber();
	Fiber(int * prog, void * argv);
	~Fiber();
	int getFiberState();
	void setContext(void * pContext);
	//void * getPvFiberContext();
private:
	CONTEXT _context;
	FSTATE _fiberState;
	void * _pvParam;					
};

Fiber::Fiber() {
	_fiberState = FS_READY;
}

Fiber::Fiber(int * prog, void * pvParam){
	_context.Esp = (DWORD)new char[1000];
	_context.Eip = (DWORD)prog;
	this->_pvParam = pvParam;
	_fiberState = FS_READY;
}

Fiber::~Fiber() { } 

int Fiber::getFiberState() {
	return _fiberState;
}

void Fiber::setContext(void * pContext) {
	_context = *(PCONTEXT)pContext;
	return;
}

//void * Fiber::getPvFiberContext() {
//	return &_context;
//}