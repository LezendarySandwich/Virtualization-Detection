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
    is_vm|= (base.size()>=4&&base[0]=='0'&&base[1]=='0'&&base[2]=='e'&&base[3]=='f');
    return is_vm;
}    

string extract_base(gdt_info g){
    stringstream ss;
    ss<< hex << g.base; 
    string res ( ss.str() );
    return res;
}

int main()
{
    gdt_info g;
    __asm__ volatile ("sgdt %0" : "=m" (g.size) );
    //cout << "gdt base: \t" << hex << gdt_info.base << std::endl;
    detect(extract_base(g));
    return 0;
}
