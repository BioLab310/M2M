

#ifndef SEARCHEDGE_H_
#define SEARCHEDGE_H_
#include "basic.h"
#include "bloomfilter.h"
#include "Graph.h"
int search_edge(int num1,int num2);
int adj_min(int num1,int num2);
int adj_max(int num1,int num2);
int two_search(unsigned num,unsigned key);
int seq_search(int num,int key);
int banary_search(int target,vector<unsigned>elem);
extern int right_num;
extern int positive_num;
extern long filter_num;
extern double two_time;
extern double seq_time;
extern double bloom_time;
#endif /* SEARCHEDGE_H_ */
