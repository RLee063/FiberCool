# FiberCool

## ����

bitman������������������Ҫ��ʵ��һ���û����˳̿⡣
ps:���ھ�����Ŀ�е����˳̣�����ʵ����һ���˳̽ӿڣ���ʱδ��ȫʵ�ֲ���������main.cpp��

## �����ӿ�

```c++
//FiberCool.hpp
void * convertThreadToFiber();
void * createFiber(void * pProg, void * pvParam);
void * switchToFiber(Fiber * pFiber);
```

```c++
//Thread.h
void YieldThd();
bool CreateThd(void* func, void * arg);
void StartThds();
```

## ��ע

��ɶ�Ŀǰ���Ǻܸߣ�����Ҫʵ�ֵĹ�����
1. �ṹ���쳣����
2. �˳̵����������ӿ�
3. FiberCool��Ϊhpp�о���̫���ʣ����Է�װΪһ����
4. ȫ�ֱ����е��