
#include "bloomfilter.h"

//int* Bloom_int(int num1,int num2){
//	if(num1>num2){
//		bloom_edge[0]=num1;
//		bloom_edge[1]=num2;
//	}
//	else{
//		bloom_edge[0]=num2;
//		bloom_edge[1]=num1;
//	}
//
//	return bloom_edge;
//}



unsigned int BKDRHash(int* str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    for(int i=0;i<2;i++)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(int* str)
{
    unsigned int hash = 0;
    int i;

    for (i = 0; i<2; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(int* str)
{
    unsigned int hash = 5381;

    for(int i=0;i<2;i++)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(int* str)
{
    unsigned int hash = 1315423911;

    for(int i=0;i<2;i++)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash(int *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    for(int i=0;i<2;i++)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

void BloomSet1(int* str)
{
    size_t i1 = BKDRHash(str) & QQQQ_set;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) & QQQQ_set;
    size_t i3 = DJBHash(str) & QQQQ_set;
    size_t i4 = JSHash(str)&QQQQ_set;
    size_t i5 =  RSHash(str) & QQQQ_set;

    //在这个位设置为1
    filter1.set(i1);
    filter1.set(i2);
    filter1.set(i3);
    filter1.set(i4);
    filter1.set(i5);
}

void BloomSet2(int* str)
{
    size_t i1 = BKDRHash(str) & QQQQ_set;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) & QQQQ_set;
    size_t i3 = DJBHash(str)& QQQQ_set;
    size_t i4 = JSHash(str)&QQQQ_set;
    size_t i5 =  RSHash(str)& QQQQ_set;

    //在这个位设置为1
    filter2.set(i1);
    filter2.set(i2);
    filter2.set(i3);
    filter2.set(i4);
    filter2.set(i5);
}

void BloomSet3(int* str)
{
    size_t i1 = BKDRHash(str) & QQQQ_set;//也可以写成Hash1 hf1; size_t i1 = hf1(key) % N;
    size_t i2 = APHash(str) &QQQQ_set;
    size_t i3 = DJBHash(str) & QQQQ_set;
    size_t i4 = JSHash(str)& QQQQ_set;
    size_t i5 =  RSHash(str)& QQQQ_set;
    //在这个位设置为1
    filter3.set(i1);
    filter3.set(i2);
    filter3.set(i3);
    filter3.set(i4);
    filter3.set(i5);
}

int Filter(int* str,int a)
{
	//str 查询字串，a 选择过滤器
	if(a==1){
		size_t i1 = BKDRHash(str) & QQQQ_set;
		if (filter1.test(i1) == false) return false;
		size_t i2 = APHash(str) &QQQQ_set;
		if (filter1.test(i2)==false) return false;
		size_t i3 = DJBHash(str) & QQQQ_set;
		if(filter1.test(i3)==false) return false;
		size_t i4 = JSHash(str)& QQQQ_set;
		if(filter1.test(i4)==false) return false;
		size_t i5 =  RSHash(str)& QQQQ_set;
		if(filter1.test(i5)==false) return false;
		return true;
	}
	if(a==2){
			size_t i1 = BKDRHash(str) & QQQQ_set;
			if (filter2.test(i1) == false) return false;
			size_t i2 = APHash(str) &QQQQ_set;
			if (filter2.test(i2)==false) return false;
			size_t i3 = DJBHash(str) & QQQQ_set;
			if(filter2.test(i3)==false) return false;
			size_t i4 = JSHash(str)& QQQQ_set;
			if(filter2.test(i4)==false) return false;
			size_t i5 =  RSHash(str)& QQQQ_set;
			if(filter2.test(i5)==false) return false;
			return true;
		}
	if(a==3){
			size_t i1 = BKDRHash(str) & QQQQ_set;
			if (filter3.test(i1) == false) return false;
			size_t i2 = APHash(str) &QQQQ_set;
			if (filter3.test(i2)==false) return false;
			size_t i3 = DJBHash(str) & QQQQ_set;
			if(filter3.test(i3)==false) return false;
			size_t i4 = JSHash(str)& QQQQ_set;
			if(filter3.test(i4)==false) return false;
			size_t i5 =  RSHash(str)& QQQQ_set;
			if(filter3.test(i5)==false) return false;
			return true;
		}
}

