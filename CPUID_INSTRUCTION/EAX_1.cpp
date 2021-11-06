#include <iostream>
using namespace std;

namespace assembly {
    int get_ecx_cpuid() {
        int ECX;
        asm volatile(
            "xor %eax, %eax;"
            "inc %eax;"
            "cpuid;"
        );
        asm volatile(
            "movl %%ecx, %0;" : "=r" ( ECX )
        );
        return ECX;
    }
}

bool check_kthbit(int number, int bit) {
    return (1ll << bit) & number;
}

const char* output_string(bool a) {
    return (a ? "Yes\n": "No\n");
}

signed main() {

    bool is_under_vm = false;

    int ECX_VAL = assembly::get_ecx_cpuid();
    is_under_vm = check_kthbit(ECX_VAL, 0x1f);
    
	cout << "Virtualization Detected: " << output_string(is_under_vm);
    return 0;

}