#include <iostream>
//#include <Windows.h>
#include <list>
#include "Fiber.cpp"
#include "Fiber.h"
using namespace std;

void * convertThreadToFiber();
void * createFiber(void * pProg, void * pvParam);
void * switchToFiber(void * pFiber);
//void * deleteFiber(void * pFiber);

int _fiberCount;
Fiber* _mainFiber;
Fiber* _currentFiber;
list<Fiber*> _fiberList;

void _suspendFiber();
void _resumeFiber(void * pFiber);
void _fiberRealease();
void _dispatchFiber();

void * createFiber(void * pProg, void * pvParam){
	Fiber * pFiber = new Fiber(pProg, pvParam, _fiberRealease);
	//因为防止程序退出，所以先挂起主Fiber, 而且纤程应该不是这样的
	//_fiberList.push_back(pFiber);
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
	//jmp here
}

void _fiberRealease() {
	_currentFiber->setFiberState(FS_DONE);
	_dispatchFiber();
}

void _dispatchFiber() {
	for (list<Fiber*>::iterator it = _fiberList.begin(); it != _fiberList.end(); it++) {
		if ((*it)->getFiberState() == FS_DONE) {
			delete *it;
			_fiberList.erase(it++);
		}
	}
	if (!_fiberList.empty()) {
		//低劣的判断是否是当前Fiber的算法
		if (_fiberList.front() == _currentFiber) {
			_fiberList.pop_front();
			_fiberList.push_back(_currentFiber);
		}
		switchToFiber(_fiberList.front());
	}
	else {
		switchToFiber(_mainFiber);
	}
	return;
}