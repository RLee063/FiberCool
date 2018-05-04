#include <iostream>
//#include <Windows.h>
#include <list>
#include "Fiber.cpp"
#include "Fiber.h"
using namespace std;

void dispatchFiber();
void * convertThreadToFiber();
void * createFiber(int * pProg, void * pvParam);
void * switchToFiber(void * pFiber);

int _fiberCount;
Fiber* _mainFiber;
Fiber* _currentFiber;
void _suspendFiber();
void _resumeFiber(void * pFiber);
void _fiberRealease();
list<Fiber*> _fiberList;

void dispatchFiber() {
	for (list<Fiber*>::iterator it = _fiberList.begin(); it != _fiberList.end(); it++) {
		if ((*it)->getFiberState() == FS_DONE) {
			delete *it;
			_fiberList.erase(it++);
		}
	}
	if (!_fiberList.empty()) {
		switchToFiber(_fiberList.front());
	}
	else {
		switchToFiber(_mainFiber);
	}
	return;
}

void * createFiber(int * pProg, void * pvParam) {
	Fiber * pFiber = new Fiber(pProg, pvParam, _fiberRealease);
	_fiberList.push_back(pFiber);
	return pFiber;
}

void * convertThreadToFiber() {
	Fiber* pFiber = new Fiber();
	_currentFiber = pFiber;
	_mainFiber = pFiber;
	return pFiber;
}

void *switchToFiber(void * pFiber) {
	if (pFiber == _currentFiber) {
		return pFiber;
	}
	_suspendFiber();
	_resumeFiber(pFiber);

}

void _suspendFiber() {
	PCONTEXT pContext;
	//get current environment***********
	//set Fiber's context
}

void _resumeFiber(void * pFiber) {
	_currentFiber = (Fiber*)pFiber;
	((Fiber*)pFiber)->setFiberState(FS_EXCUTING);
	PCONTEXT pContext= ((Fiber*)pFiber)->getPvFiberContext;
	//set current environment***********
}

void _fiberRealease() {
	_currentFiber->setFiberState(FS_DONE);
	dispatchFiber();
}