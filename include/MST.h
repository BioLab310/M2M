
//
#ifndef MST_H_
#define MST_H_
#include "basic.h"
#include "Graph.h"
#include "bloomfilter.h"
#include "searchedge.h"
int CreateMST();
int InitMST();
void MSTdisplay();
int SelectSingle();
int BinarySearch(vector<int> vec,int target);
int InsertSort(vector<int>& vec,int target);
int ClearSide(int root,int key);
int InsertChildCandidate(vector<MST> &vec,int id,vector<int> child);
int  InsertEdgeCandidate(int recall);
void UpdateMstCandidate();
void initial_mst1_candidate_all();
int return_node_num_as_child(int node_id);
void find_first_edge();
void UpdateMstCandidateRecall();
void update_candidate_by_not_mst();
typedef struct {
	int adjvex;//权值
	float lowcost;//座标点
}fuzhu;


#endif /* MST_H_ */

