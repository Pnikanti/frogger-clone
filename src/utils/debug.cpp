#include <malloc.h>
#include "statistics.h"

void* operator new(size_t size)
{
	Statistics::Get().AllocatedMemory += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	Statistics::Get().FreedMemory += size;
	free(memory);
}