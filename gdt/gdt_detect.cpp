#include <bits/stdc++.h>
#include <cstdio>
#include <cinttypes>

using namespace std;

typedef struct gdt_info
{
    uint16_t  pad;
    uint16_t  size;
    uintptr_t base;
} gdt_info;

bool detect(string base){
    bool is_vm = (base.size()>=2&&base[0]=='f'&&base[1]=='f');
    reverse(base.begin(), base.end());
    is_vm |= (base.size()>=4&&base[0]=='0'&&base[1]=='0'&&base[2]=='e'&&base[3]=='f');
    return is_vm;
}    

string extract_base(gdt_info g){
    stringstream ss;
    ss << hex << g.base; 
    string res ( ss.str() );
    return res;
}

const char* output_string(bool a) {
    return (a ? "Yes\n": "No\n");
}

int main()
{
    gdt_info g;
    __asm__ volatile ("sgdt %0" : "=m" (g.size) );
    cout << "gdt base: \t" << hex << g.base << std::endl;
    
    bool is_under_vm = detect(extract_base(g));
    cout << "Virtualization Detected: " << output_string(is_under_vm);

    return 0;
}