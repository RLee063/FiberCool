#include "FiberCool.cpp"

void YieldThd() {
	_dispatchFiber();
}

void CreateThd(void* func, void * arg) {
	createFiber(func, arg);
}

void StartThds() {
	convertThreadToFiber();
	_dispatchFiber();
}