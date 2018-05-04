#include <iostream>
#include <Windows.h>
#include <vector>
#include "Fiber.cpp"
#include "Fiber.h"
using namespace std;

//Its a fiber manager
class FiberCool {
public:
	void * convertThreadToFiber();
	void * createFiber(int * pProg, void * pvParam);
	void * switchToFiber(void * pFiber);
	//void startFiber();
private:
	int _fiberCount;
	static Fiber* _mainFiber;
	static Fiber* _currentFiber;
	void _suspendFiber();
	void _resumeFiber(void * pFiber);
	static void _fiberRealease();
	vector<Fiber*> fiberVector;
};

void * FiberCool::createFiber(int * pProg, void * pvParam) {
	Fiber * pFiber = new Fiber(pProg, pvParam, _fiberRealease);
	return pFiber;
}

void * FiberCool::convertThreadToFiber() {
	Fiber* pFiber = new Fiber();
	_currentFiber = pFiber;
	return pFiber;
}

void * FiberCool::switchToFiber(void * pFiber) {
	_suspendFiber();
	_resumeFiber(pFiber);
	_currentFiber = (Fiber*)pFiber;
	((Fiber*)pFiber)->setFiberState(FS_EXCUTING);
}

void FiberCool::_suspendFiber() {
	PCONTEXT pContext;
	//get current environment***********
	//set Fiber's context
}

void FiberCool::_resumeFiber(void * pFiber) {
	PCONTEXT pContext= ((Fiber*)pFiber)->getPvFiberContext;
	//set current environment***********
}

void FiberCool::_fiberRealease() {
	_currentFiber->setFiberState(FS_DONE);

}