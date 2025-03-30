#ifndef _BASIC_H_
#define _BASIC_H_

#define QQQQ 0x10000000
#define QQQQ_set 0xfffffff
//#define AD_SIZE 30
#include<math.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include"stdint.h"
#include<sstream>
#include <bitset>
#include <random>
#include <sys/time.h>
#include<algorithm>
#include<utility>
#include <map>
#include <queue>
#include<set>
#include <algorithm>
#include <assert.h>
#include <unordered_set>
#include <random>
#include <ctime>
#include <stack>
using namespace std;

//G information

extern vector<vector<uint32_t>> G;
extern vector<uint32_t> G_degree ;
extern vector<uint32_t> G_v_nodelabel;
extern vector<vector<uint32_t>> G_labelvec;
extern int bloom_edge[2];
extern unsigned G_vexnum;
extern unsigned G_arcnum;
extern bitset<	QQQQ> filter1;
extern bitset<	QQQQ> filter2;
extern bitset<	QQQQ> filter3;
extern int AD_SIZE;
extern int output_choise;
typedef struct MST{
	unsigned id;
	bool flag_active;
	vector<int> parentCandidate;
	vector<vector<int>> childCandidate;
}MST;
extern vector<vector<MST>> mst1;
extern vector<pair<int,int>> MstOrder;//边生成顺序
extern vector<int> M_index_uu;//顶点插入顺序
extern vector<int> M;//enbadding
extern int embedding_num;
extern int best_embedding_num ;
#endif
