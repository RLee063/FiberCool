#pragma once

typedef enum {
	FS_READY,
	FS_EXCUTING,
	FS_DONE
}FSTATE;

class Fiber
{
public:
	Fiber();
	~Fiber();
};

