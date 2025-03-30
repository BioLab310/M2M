

#ifndef GRAPH_H_
#define GRAPH_H_
#include "basic.h"
#include "bloomfilter.h"
#include "searchedge.h"

extern vector<vector<uint32_t>> Q;
extern vector<uint32_t> Q_degree;
extern vector<uint32_t> Q_v_nodelabel;
extern unsigned Q_vexnum;
extern unsigned Q_arcnum;
extern vector<vector<uint32_t>> Q_labelvec;
//extern vector<vector<int>> mst;
extern vector < vector<unsigned >> candidate;//候选顶点集
extern int candidate_before_update;
extern int candidate_after_update;
extern set<pair<int, int>> Visited_Set;
extern vector<pair<int,int>> not_mst_edge;;

int InsertMST(vector<unsigned>cond1,vector<unsigned>cond2,int count);
int CreateMST();
int InitMST();
int CandidateCompute();
bool visited(int a,int b);
pair<int,int> makePair(int a,int b);
void create_not_mst_edge();
//void update_candidate_of_not_mst_edge(int edge_id);
#endif /* GRAPH_H_ */
