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

bool detect_vmware(string base){
    return (base.size()>=2&&base[0]=='f'&&base[1]=='f');
}

bool detect_wsl(string base){
    reverse(base.begin(), base.end());
    return (base.size()>=4&&base[0]=='0'&&base[1]=='0'&&base[2]=='e'&&base[3]=='f');
}

void detect(string base){
    if(detect_vmware(base))cout<<"Detected virtualisation - VMWare\n";
    else if(detect_wsl(base))cout<<"Detected WSL\n";
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
