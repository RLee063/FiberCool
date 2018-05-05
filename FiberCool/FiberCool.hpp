#pragma once
#pragma once
#include <iostream>
//#include <Windows.h>
#include <list>
#include "Fiber.h"
using namespace std;

void * convertThreadToFiber();
void * createFiber(void * pProg, void * pvParam);
void * switchToFiber(Fiber * pFiber);
//void * deleteFiber(void * pFiber);

CONTEXT tContext;
void * tArgv;

int _fiberCount;
Fiber* _mainFiber;
Fiber* _currentFiber;
list<Fiber*> _fiberList;

void _fiberRealease();
void _dispatchFiber();

void * createFiber(void * pProg, void * pvParam) {
	Fiber * pFiber = new Fiber(pProg, pvParam, _fiberRealease);
	//因为防止程序退出，所以先挂起主Fiber, 而且纤程应该不是这样的
	_fiberList.push_back(pFiber);
	return pFiber;
}

void * convertThreadToFiber() {
	Fiber* pFiber = new Fiber();
	_currentFiber = pFiber;
	_mainFiber = pFiber;
	return pFiber;
}

__declspec(naked) void * switchToFiber(Fiber * pFiber) {
	_asm {
		mov eax, [esp + 4]
		mov pFiber, eax
	}
	if (_currentFiber == pFiber) {
		_asm {
			mov eax, pFiber
			ret 0x4
		}
	}
	_asm {
		mov tContext.Eax, eax
		mov tContext.Ecx, ecx
		mov tContext.Edx, edx
		mov tContext.Ebx, ebx
		mov tContext.Esi, esi
		mov tContext.Edi, edi
		mov tContext.Ebp, ebp
		mov eax, [esp]
		mov tContext.Eip, eax
		add esp, 4
		mov tContext.Esp, esp
	}
	_currentFiber->setContext(&tContext);

	_currentFiber = (Fiber*)pFiber;
	((Fiber*)pFiber)->setFiberState(FS_EXCUTING);
	tContext = *((PCONTEXT)pFiber->getPvFiberContext());

	_asm {
		mov esp, tContext.Esp
		mov eax, tContext.Eax
		mov ecx, tContext.Ecx
		mov edx, tContext.Edx
		mov ebx, tContext.Ebx
		mov esi, tContext.Esi
		mov edi, tContext.Edi
		mov ebp, tContext.Ebp
		jmp tContext.Eip
	}

	//if (pFiber->getFiberState() == FS_READY) {
	//	tArgv = pFiber->getPvParam();
	//	_asm {
	//		mov esp, tContext.Esp
	//		push tArgv
	//		mov eax, tContext.Eax
	//		mov ecx, tContext.Ecx
	//		mov edx, tContext.Edx
	//		mov ebx, tContext.Ebx
	//		mov esi, tContext.Esi
	//		mov edi, tContext.Edi
	//		mov ebp, tContext.Ebp
	//		jmp tContext.Eip
	//	}
	//}
	//else {
	//	_asm {
	//		mov esp, tContext.Esp
	//		mov eax, tContext.Eax
	//		mov ecx, tContext.Ecx
	//		mov edx, tContext.Edx
	//		mov ebx, tContext.Ebx
	//		mov esi, tContext.Esi
	//		mov edi, tContext.Edi
	//		mov ebp, tContext.Ebp
	//		jmp tContext.Eip
	//	}
	//}
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