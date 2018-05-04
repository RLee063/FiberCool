#include <iostream>
#include <Windows.h>
#include "Fiber.cpp"
using namespace std;

//Its a fiber manager
class FiberCool {
public:
	void * convertThreadToFiber();
	void * createFiber(int * pProg, void * pvParam);
	void * switchToFiber(void * pFiber);
private:
	Fiber* _currentFiber;

};


void * FiberCool::createFiber(int * pProg, void * pvParam) {
	Fiber * pFiber = new Fiber(pProg, pvParam);
	return pFiber;
}

void * FiberCool::convertThreadToFiber() {
	Fiber* pFiber = new Fiber();
	_currentFiber = pFiber;
	return pFiber;
}

void * FiberCool::switchToFiber(void * pFiber) {
	
}