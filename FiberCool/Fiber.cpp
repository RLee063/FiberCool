#pragma once
#include "Fiber.h"
#include <Windows.h>


Fiber::Fiber() {
	//***set return value
	_fiberState = FS_EXCUTING;
}

Fiber::Fiber(void * prog, void * pvParam, void * releaseFunc){
	//***set return value
	_espAllocP = new char[100000];
	_context.Esp = (DWORD)_espAllocP;
	_context.Esp += 25000;
	_context.Eip = (DWORD)prog;
	this->_pvParam = pvParam;
	int * pvStack = (int*)_context.Esp;
	pvStack -= 1;
	*pvStack = (int)pvParam;
	*(pvStack - 1) = (int)releaseFunc;
	_context.Esp = (DWORD)(pvStack - 1);
	_fiberState = FS_READY;
}

Fiber::~Fiber() { 
	//may have someting wrong here
} 

int Fiber::getFiberState() {
	return _fiberState;
}

void Fiber::setContext(CONTEXT * pContext) {
	_context = *pContext;
	return;
}

void * Fiber::getPvFiberContext() {
	return &_context;
}

void Fiber::setFiberState(int state) {
	_fiberState = (FSTATE)state;
}

void * Fiber::getPvParam() {
	return _pvParam;
}