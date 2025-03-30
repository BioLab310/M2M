
#include "Graph.h"

vector<vector<uint32_t>> Q;
vector<uint32_t> Q_degree;
vector<uint32_t> Q_v_nodelabel;
unsigned Q_vexnum;
unsigned Q_arcnum;
vector<vector<uint32_t>> Q_labelvec;
//vector<vector<int>> mst;
vector<vector<unsigned >> candidate;//候选顶点集
int candidate_before_update=0;
int candidate_after_update=0;
vector<pair<int,int>> not_mst_edge;
set<pair<int, int>> Visited_Set;


int CandidateCompute(){
//	unsigned int g,s;
	candidate.resize(0);
	candidate.resize(Q_vexnum);
	for(unsigned i=0;i<Q_vexnum;i++){
		for(unsigned j=0;j<G_vexnum;j++){
			bool iscan=true;
			for(int k=0;k<Q_labelvec[i].size();k++){
				if(Q_labelvec[i][k]>G_labelvec[j][k]) {
					iscan=false;
					break;
				}

			}
			if(iscan) candidate[i].push_back(j);
		}
	}
//	for(auto i:candidate){
//		cout<<i[0]<<"为什么"<<i[2]<<endl;
//	}
	return 1;
}
void min_max_change(int &a,int &b){
	if(a>b){
		swap(a,b);
	}
}
pair<int,int> makePair(int a,int b){
	min_max_change(a,b);
	return make_pair(a,b);
}
bool visited(int a,int b){
	min_max_change(a,b);
	if(Visited_Set.find(make_pair(a,b))!=Visited_Set.end()){
		return true;
	}
	else return false;
}
void create_not_mst_edge(){

	not_mst_edge.resize(0);
	for(int i=0;i<Q_vexnum;i++){
		for(int j=0;j<Q[i].size();j++){
			if(visited(i,Q[i][j]) ) continue;
			else {
				Visited_Set.insert(makePair(i,Q[i][j]));
				not_mst_edge.push_back(make_pair(i,Q[i][j]));
			}
		}
	}
//	for(auto i:not_mst_edge){
//		cout<<i.first<<'-'<<i.second<<' ';
//	}
}




