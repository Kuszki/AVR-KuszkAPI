#include "kamemory.hpp"

void* operator new (size_t Size)
{
	return malloc(Size);
}

void* operator new[] (size_t Size)
{
	return malloc(Size);
}

void operator delete (void* Pointer)
{
	free(Pointer);
}

void operator delete[] (void* Pointer)
{
	free(Pointer);
}

size_t getFreeRAM(void)
{
  extern int	__heap_start;
  extern int*	__brkval;

  char 		tmp;

  return (size_t) &tmp - (__brkval ? (size_t) __brkval : (size_t) &__heap_start);
}
