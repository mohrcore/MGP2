#include <iostream>

#define EXPORT __declspec(dllexport) __cdecl


void EXPORT function1()
{
	std::cout << "function1 called" << std::endl;
}

void EXPORT function2()
{
	std::cout << "function2 called, now calling function1" << std::endl;

	function1();
}

class TestClass
{
	void EXPORT tcFun() {}
};