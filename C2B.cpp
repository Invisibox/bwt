#include "general_heading.h"
#include "sort.h"

// 将字符转换为二进制编码：00, 01, 10, 11
uint64_t encode(char c) {
    switch (c) {
        case 'A':
            return 0; // 00
        case 'C':
            return 1; // 01
        case 'G':
            return 2; // 10
        case 'T':
            return 3; // 11
        default:
            return -1;
    }
}

// 将字符转换为二进制编码并存储到地址中
void C2B(uint64_t* addr, std::ifstream &infile) {
    if (!infile.is_open()) {
        std::cout << "错误：文件不存在。" << std::endl;
        return;
    }

    short bits = 0;
    uint64_t cur = 0;
    long i = -1;
    std::string cur_row;

    // 读取文件的每一行
    std::getline(infile, cur_row);
    while (std::getline(infile, cur_row)) {
        for (char c : cur_row) {
            uint64_t cur_char = encode(c);
            if (cur_char == -1) {
                std::cout << "错误：字符不是 'ACGT' 之一。" << std::endl;
                return;
            }

            if (bits == 0) {
                if (i == -1) {
                    i++;
                } else {
                    addr[i++] = cur;
                }
                cur = cur_char;
                bits = 62;
            } else {
                cur = (cur << 2) | cur_char;
                bits -= 2;
            }
        }
    }

    if (bits) {
        cur = cur << bits;
        addr[i] = cur;
    }
}

// 将字符转换为二进制编码并生成BWT
uint32_t C2B_BWT(uint64_t* seq, uint64_t *BWT, int* SA, int size) {
    short bits = 0;
    uint64_t cur = 0;
    long i = -1;
    uint64_t loc_of_dollar = 0;

    for (int j = 0; j < size; j++) {
        uint64_t cur_char;
        if (SA[j] == 0) {
            cur_char = encode('A');
            loc_of_dollar = j;
        } else {
            cur_char = encode(extract_char(seq, SA[j] - 1));
        }

        if (bits == 0) {
            if (i == -1) {
                i++;
            } else {
                BWT[i++] = cur;
            }
            cur = cur_char;
            bits = 62;
        } else {
            cur = (cur << 2) | cur_char;
            bits -= 2;
        }
    }

    if (bits) {
        cur = cur << bits;
        BWT[i] = cur;
    }

    return loc_of_dollar;
}