# FiberCool

## 描述

bitman“病毒”任务后的任务，要求实现一个用户级纤程库。
ps:由于觉得题目有点像纤程，于是实现了一套纤程接口（暂时未完全实现不过满足了main.cpp）

## 导出接口

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

## 备注

完成度目前不是很高，还需要实现的功能有
1. 结构化异常处理
2. 纤程的其他几个接口
3. FiberCool作为hpp感觉不太合适，尝试封装为一个类
4. 全局变量有点多