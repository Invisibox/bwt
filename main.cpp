#include "general_heading.h"
#include "sort.h"
#include "C2B.h"
#include "BWT.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>

void read_fasta(std::ifstream &myfile, std::string &seq);

int main() {
    std::string file = "../NC_008253.fna";
    std::ifstream myfile(file);
    std::string cur_row;
    uint64_t size = 0;

    // 计算序列的大小
    std::getline(myfile, cur_row);
    while (std::getline(myfile, cur_row)) {
        size += cur_row.size();
    }
    myfile.close();

    // 重新打开文件进行处理
    myfile.open(file);
    uint64_t num_of_u64 = (size * 2) / 64;
    int* SA = (int*)malloc(sizeof(int) * (size + 1));
    for (uint64_t i = 0; i <= size; ++i) {
        SA[i] = i;
    }

    uint64_t* sequence = (uint64_t*)malloc(sizeof(uint64_t) * (num_of_u64 + 1));
    C2B(sequence, myfile);

    // 记录时间并对后缀数组进行排序
    clock_t start = clock();
    my_quicksort(SA, 0, size, sequence);
    clock_t finish = clock();

    // 生成BWT并找到$的位置
    uint64_t* BWT = (uint64_t*)malloc(sizeof(uint64_t) * (num_of_u64 + 1));
    uint64_t loc = C2B_BWT(sequence, BWT, SA, size);

    // 输出结果
    std::cout << "dollar符号的位置: " << loc << std::endl;
    std::cout << "排序时间: " << (double)(finish - start) / CLOCKS_PER_SEC << "秒" << std::endl;
    std::cout << "序列大小: " << size << std::endl;

    // 打印后缀数组的前10个元素
    for (int i = 0; i < 10; ++i) {
        std::cout << SA[i] << std::endl;
    }

    print_BWT(SA, sequence, 10);

    // 释放分配的内存
    free(SA);
    free(sequence);
    free(BWT);

    return 0;
}