
#include "mstEmbedding.h"

//int visit_mst(int node){
//	cout<<mst1[node][0].id<<' ';
//	if(mst1[node][0].childCandidate[0].size()==0) {
////		cout<<2<<endl;
//		return 0;
//	}
//	for(int i=0;i<mst1[node][0].childCandidate[0].size();i++){
//		visit_mst(mst1[node][0].childCandidate[0][i]);
//	}
//	return 1;
//}

stack<int> st;

int visit_mst(int node){
	st.push(node);
	while(!st.empty()){
		int snode=st.top();
		st.pop();
//		cerr<<mst1[snode][0].id<<' ';
		for(int i=mst1[snode][0].childCandidate[0].size()-1;i>=0;i--){
			int child=mst1[snode][0].childCandidate[0][i];
//			if(child>=0&&child<Q_vexnum) st.push(child);
			st.push(child);
		}
	}
	return 1;
}
void init_M(){
	M_index_uu.resize(Q_vexnum);
	M.resize(Q_vexnum);
	embedding_num=0;
}
void create_M_index_uu(){
	M_index_uu[MstOrder[0].first]=0;
	for(int i=0;i<MstOrder.size();i++){
		M_index_uu[MstOrder[i].second]=i+1;
	}
}
bool M_not_repetitive(int v,int i){
	for(int j=0;j<i;j++){
		if(M[j]==v) return false;
	}
	return true;
}
int node_id_of_candidate(int v,vector<unsigned> can){
	int index=banary_search(v,can);
	if(index!=-1){
		return index+1;
	}
	return -1;
}
void output(){
	for(auto i:M){
		cout<<i<<' ';
	}
	cout<<endl;
}
void BFS(int i_n){
	if(i_n==Q_vexnum-1){
		embedding_num++;
		if(output_choise==1){
			output();//输出M
		}
		return ;
	}
	if(embedding_num>=best_embedding_num){
		return ;
	}
	//查找插入的uui候选的位置
	int uu=MstOrder[i_n-1].first;
	int u=MstOrder[i_n-1].second;
	int vtmp=M[M_index_uu[uu]];
	int v_num_as_child;
	//查找u插入在uui的第几个孩子
	v_num_as_child=return_node_num_as_child(u);
	int v=node_id_of_candidate(vtmp,candidate[uu]);

	for(int i=0;i<mst1[uu][v].childCandidate[v_num_as_child].size();i++){
		int child=mst1[uu][v].childCandidate[v_num_as_child][i];
		//判断该候选是否存在
		int i_in_u_candidate=node_id_of_candidate(child,candidate[u]);
		if(i_in_u_candidate==-1) continue;
		//判断是否重复
		if(!M_not_repetitive(child,i_n)){
			continue;
		}
		
		if(i_n==Q_vexnum-1){
		}
		else{
			BFS(i_n+1);
		}
		M[i_n]=child;
		if(embedding_num>=best_embedding_num) break;
	}
}
void create_embedding_of_mst(){
	init_M();
	create_M_index_uu();
	int i_n=0;
	int node=MstOrder[0].first;

	for(int i=0;i<candidate[node].size();i++){
		M[i_n]=candidate[node][i];
		BFS(i_n+1);
	}
}




