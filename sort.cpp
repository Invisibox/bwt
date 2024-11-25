#include "general_heading.h"

// 提取值函数，从地址数组中提取指定索引的值
uint64_t extract_val(uint64_t* addr, int idx) {
    int i = idx >> 5; // 计算块索引
    int j = idx % 32; // 计算块内偏移
    if (j == 0) return addr[i];
    uint64_t code1 = addr[i] << (j * 2);
    uint64_t code2 = addr[i + 1] >> (64 - j * 2);
    return code1 | code2;
}

// 比较函数，比较两个索引处的值
int compare(uint64_t* addr, int i, int j) {
    uint64_t val1 = extract_val(addr, i);
    uint64_t val2 = extract_val(addr, j);
    if (val1 == val2) return compare(addr, i + 1, j + 1); // 递归比较下一个值
    return val1 < val2;
}

// 快排
void my_quicksort(int SA[], int left, int right, uint64_t* addr) {
    if (left < right) {
        int pivot = SA[right]; // 选择最右边的元素作为枢轴
        int i = left - 1;
        for (int j = left; j <= right - 1; j++) {
            if (compare(addr, SA[j], pivot)) {
                i++;
                std::swap(SA[i], SA[j]); // 交换元素
            }
        }
        std::swap(SA[i + 1], SA[right]); // 将枢轴放置在正确位置
        int partition = i + 1;
        my_quicksort(SA, left, partition - 1, addr); // 递归排序左子数组
        my_quicksort(SA, partition + 1, right, addr); // 递归排序右子数组
    }
}