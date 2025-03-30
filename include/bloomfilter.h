

#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

#include "basic.h"
//int*类型数据进入bloom过滤器
// BKDR Hash Function
unsigned int BKDRHash(int* str);


// AP Hash Function
unsigned int APHash(int* str);


// DJB Hash Function
unsigned int DJBHash(int* str);


// JS Hash Function
unsigned int JSHash(int* str);


// RS Hash Function
unsigned int RSHash(int *str);


void BloomSet1(int* str);
void BloomSet2(int* str);
void BloomSet3(int* str);
//int* Bloom_int(int num1,int num2);
char* Bloom_char(int num1,int num2);
int Filter(int* str,int a);

#endif /* BLOOMFILTER_H_ */
