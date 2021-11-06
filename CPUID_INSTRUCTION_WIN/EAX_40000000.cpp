#include <iostream>
#include <string>

using namespace std;


int main()
{
	bool IsUnderVM = false;

	__asm {
		xor    eax, eax
		mov    eax,0x40000000
		cpuid
		cmp ecx,0x4D566572
		jne NopInstr
		cmp edx,0x65726177
		jne NopInstr
		mov IsUnderVM, 0x1
		NopInstr:
		nop
	}
	cout << IsUnderVM;
	return 0;
}