#include <bits/stdc++.h>

using namespace std;

namespace datastructures {

    struct desc_ptr {
        unsigned short size;
        unsigned long address;
    } __attribute__((packed)) ;

    using global_descriptor_table = struct desc_ptr;

    class access_base {
        protected:
        uint64_t base;
        bool bit;
        public:
        access_base(struct desc_ptr const &g, bool bit) : base(g.address), bit(bit) {}
        explicit operator string () {
            stringstream ss;
            ss << hex << base; 
            string res ( ss.str() );
            if(bit) res[static_cast<int>(res.size()) - 4] = '9';
            return res;
        } 
    };

}

namespace assembly {

    void gdt_asm(datastructures::global_descriptor_table &g) {
        __asm__ __volatile__ ("sgdt %[gdt]" : [gdt]"=m" (g) );
    }

    int32_t ecx() {
        int ECX;
        asm volatile(
            "xor %eax, %eax;"
            "inc %eax;"
            "cpuid;"
        );
        asm volatile(
            "movl %%ecx, %0;" : "=r" ( ECX )
        );
        return ECX & (1 << 31);
    }

}

namespace detect {

    vector<string> end_pattern{
        "9000"
    };

    bool detect(datastructures::access_base base){
        string base_address = static_cast<string> (base);
        
        for(string &pat: end_pattern) {
            if(pat.size() <= base_address.size()) {
                int st = static_cast<int> (base_address.size()) - static_cast<int> (pat.size());
                if(base_address.substr(st, pat.size()) == pat) {
                    return true;
                }
            }
        }

        return false;
    }    

}


const char* output_string(bool a) {
    return (a ? "Yes\n": "No\n");
}

int main()
{
    datastructures::global_descriptor_table g;

    assembly::gdt_asm(g);

    datastructures::access_base base_conv =  datastructures::access_base(g, assembly::ecx());
    
    cout << "Global Descriptor Table Base Address: " << static_cast<string> (base_conv) << endl;

    bool is_under_vm = detect::detect(base_conv);
    cout << "Virtualization Detected: " << output_string(is_under_vm);

    return 0;
}
