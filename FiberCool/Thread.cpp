#pragma once
#include "FiberCool.hpp"

void YieldThd() {
	_dispatchFiber();
}

bool CreateThd(void* func, void * arg) {
	return createFiber(func, arg);
}

void StartThds() {
	convertThreadToFiber();
	YieldThd();
}