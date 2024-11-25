#ifndef EXP1_BWT_H
#define EXP1_BWT_H
#include "general_heading.h"
char extract_char(uint64_t* addr, int idx);
void print_BWT(int* SA, uint64_t* addr, int len);
void save_BWT_to_file(const std::string &filename, int* SA, uint64_t* BWT, uint64_t size);
#endif
