#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace assembly {
    int get_ecx_cpuid() {
        int ECX;
        asm volatile (
            "xor %eax, %eax;"
            "movl $0x40000000, %eax;"
            "cpuid;"
        );
        asm volatile(
            "movl %%ecx, %0;" : "=r" ( ECX )
        );
        return ECX;
    }
}

namespace vm_string_lst {
    const vector<int> brand_list{
        0x4D566572, 
        0x65726177,
        0x564b4d56,
    };
}

const char* output_string(bool a) {
    return (a ? "Yes\n": "No\n");
}

int main()
{
	bool is_under_vm = false;

    int ECX_VAL = assembly::get_ecx_cpuid();
    for(int brand: vm_string_lst::brand_list) is_under_vm |= brand == ECX_VAL;

	cout << "Virtualization Detected: " << output_string(is_under_vm);
	return 0;
}