#pragma once

typedef enum {
	FS_READY,
	FS_EXCUTING
}FSTATE;

class Fiber
{
public:
	Fiber();
	~Fiber();
};

