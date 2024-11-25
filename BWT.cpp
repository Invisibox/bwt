#include "BWT.h"
#include "general_heading.h"

// 提取字符函数，从地址数组中提取指定索引的字符
char extract_char(uint64_t* addr, int idx) {
    int i = idx / 32; // 计算在数组中的位置
    int j = idx % 32; // 计算在64位整数中的位置
    uint64_t code = addr[i];
    code = (code << (j * 2)) >> 62; // 获取所需的位：左移 j*2 位，然后右移 62 位
    switch (code) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'G';
        case 3: return 'T';
        default: return 'N';
    }
}

// 打印BWT函数，输出后缀数组对应的BWT字符串
void print_BWT(int* SA, uint64_t* addr, int len) {
    for (int i = 0; i < len; i++) {
        if (SA[i] == 0)
            std::cout << '$'; // 输出结束符
        else
            std::cout << extract_char(addr, SA[i] - 1); // 输出对应字符
    }
    std::cout << std::endl;
}
