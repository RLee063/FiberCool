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

void _suspendFiber();
void _resumeFiber(void * pFiber);
void _fiberRealease();
void _dispatchFiber();

void * createFiber(void * pProg, void * pvParam) {
	Fiber * pFiber = new Fiber(pProg, pvParam, _fiberRealease);
	//��Ϊ��ֹ�����˳��������ȹ�����Fiber, �����˳�Ӧ�ò���������
	//_fiberList.push_back(pFiber);
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
	tContext = *((PCONTEXT)pFiber->getPvFiberContext());
	if (pFiber->getFiberState() == FS_READY) {
		tArgv = pFiber->getPvParam();
		_asm {
			mov esp, tContext.Esp
			push tArgv
			mov eax, tContext.Eax
			mov ecx, tContext.Ecx
			mov edx, tContext.Edx
			mov ebx, tContext.Ebx
			mov esi, tContext.Esi
			mov edi, tContext.Edi
			mov ebp, tContext.Ebp
			call tContext.Eip
		}
	}
	else {

	}
	//if (pFiber == _currentFiber) {
	//	return pFiber;
	//}

	//_suspendFiber();
	//_resumeFiber(pFiber);
}

__declspec(naked) void _suspendFiber() {
	_asm {
		//check

		ret 0x4;
	}
	//get current environment***********
	//set Fiber's context
}

void _resumeFiber(void * pFiber) {
	_currentFiber = (Fiber*)pFiber;
	((Fiber*)pFiber)->setFiberState(FS_EXCUTING);
	PCONTEXT pContext = (PCONTEXT)((Fiber*)pFiber)->getPvFiberContext();
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
		//���ӵ��ж��Ƿ��ǵ�ǰFiber���㷨
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