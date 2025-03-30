
#ifndef _PUTIN_H_
#define _PUTIN_H_
#include"basic.h"
#include "bloomfilter.h"
#include "Graph.h"
int readGraph(char* path,vector<vector<uint32_t>>& G,vector<uint32_t>& degree,vector<uint32_t>& v_nodelabel,unsigned &vexnum,unsigned &arcnum);
void display(int t);
int LabelCompute(int flag);


#endif
