#include"Thread.h"
#include<cstdio>
using namespace std;

void thd2(void * arg)
{
	for (int i = 4; i < 12; i++)
	{
		printf("thd2: arg=%d , i = %d\n", (int)arg, i);
		YieldThd();
	}
}

void thd1(void * arg)
{
	if (CreateThd(thd2, (void *)2) == NULL)
	{
		printf("cannot create\n");
	}
	for (int i = 0; i < 12; i++)
	{
		printf("thd1: arg=%d , i = %d\n", (int)arg, i);
		YieldThd();
	}
}


int main()
{
	if (CreateThd(thd1, (void *)1) == NULL)
	{
		printf("cannot create\n");
	}

	StartThds();
	return 0;
}
