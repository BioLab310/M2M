
#include "MST.h"

vector<int> candidate_num;//储存候补定点数
vector<fuzhu> closedge;
int mst_num=0;
default_random_engine e;


bool recallFlag=false;//回溯标志

//class mycomparison {
//public:
//	bool operator()(const pair<pair<int,int>,float>& lhs, const pair<pair<int,int>,float>& rhs) {
//		return lhs.second > rhs.second;
//	}
//};
//priority_queue<pair<pair<int,int>,float>,vector<pair<pair<int,int>, float>>,mycomparison> candidate_weight;
int InitMST(){
	mst1.resize(0);
	mst1.resize(Q_vexnum);
	int root,C=-1;
	uniform_int_distribution<int> u(1,Q_vexnum-1); // 左闭右闭区间
	e.seed(time(0));
	for(int i=0;i<Q_vexnum;i++){
		//0号节点初始化
		mst1[i].resize(1);
		mst1[i][0].id=i;
		mst1[i][0].childCandidate.resize(1);
		closedge[i].lowcost=-1;
		if(C==-1){
			C=0;
			root=i;
		}
		else if(candidate_num[i]<candidate_num[root]){
			root=i;
		}
	}
	closedge[root].lowcost=0;
	mst1[root][0].parentCandidate.push_back(-1);
//	find_first_edge();//根节点父节点初始化
//	for(auto i:closedge){
//		cout<<i.lowcost<<' ';
//	}
//	cout<<root<<endl;
	return root;
}
float compute_edge_candidate_weight(int i,int j){
	int count=0;
	for(auto ci:candidate[i]){
		for(auto cj:candidate[j]){
			if(search_edge(ci,cj)){
				count++;
			}
		}
	}
	float weight=count*1.0/(candidate_num[i]+candidate_num[j]);
	return weight;
}
//选择最小边中的一条最为root
void find_first_edge(){
	//set<pair<int,int>> value;
	float min=100000;
	pair<int,int>min_ij;
	for(int i=0;i<Q_vexnum;i++){
		for(auto j:Q[i]){
			float weight=compute_edge_candidate_weight(i,j);
			if(min>weight&&weight>0){
//				cout<<min<<' ';
				min=weight;
				min_ij=make_pair(i,j);
			}
		}
	}
//	cout<<min_ij.first<<' '<<min_ij.second<<endl;
	closedge[min_ij.first].lowcost=0;
	closedge[min_ij.second].lowcost=min;
	closedge[min_ij.second].adjvex=min_ij.first;
	mst1[min_ij.first][0].parentCandidate.push_back(-1);
}
//pair<int,int>
//void compute_candidate_weight(){
//	set<pair<int,int>> value;
//	int weight;
//	//相连边之间计算权重
//	for(int i=0;i<Q_vexnum;i++){
//		for(auto j:Q[i]){
//			if(!value.count(makePair(i,j))){
//				weight=compute_edge_candidate_weight(i,j);
//				value.insert(makePair(i,j))
//			}
//		}
//	}
//	//对map中按value数值排序
//}


int CreateMST(){
//	mst_num=0;
//	candidate_num.clear();
	MstOrder.clear();
	//计算节点权重
	for(auto i:candidate){
		candidate_num.push_back(i.size());
		candidate_before_update+=i.size();
//		cout<<i.size()<<' ';
////		for(auto j:i){
////			cout<<j<<' ';
////		}
//		cout<<endl;
	}
	//cerr<<endl;
	closedge.resize(0);
	closedge.resize(Q_vexnum);
	int i=InitMST();
	for(int i=0;i<Q_vexnum-1;i++){
		SelectSingle();
	}
	return 1;
}
int SelectSingle(){
//	int k=MinNode_cannum();
	//update closeage
	uniform_int_distribution<int> u(1,Q_vexnum-1); // 左闭右闭区间
	e.seed(time(0));
	candidate_num.resize(0);
	//随机数的初始化需要放在循环外面
	for(int k=0;k<Q_vexnum;k++){
		//在树上
		if(closedge[k].lowcost==0){
			for(int j=0;j<Q[k].size();j++){
				//float weight=compute_edge_candidate_weight(k,Q[k][j]);
				//不在树上，或者节点变小
				if(closedge[Q[k][j]].lowcost==-1||candidate_num[k]+candidate_num[Q[k][j]]<closedge[Q[k][j]].lowcost){
					closedge[Q[k][j]].adjvex=k;
					closedge[Q[k][j]].lowcost=candidate_num[k]+candidate_num[Q[k][j]];
				}

//				int weight=u(e);
//				if(closedge[Q[k][j]].lowcost==-1||weight<closedge[Q[k][j]].lowcost){
//					closedge[Q[k][j]].adjvex=k;
//					closedge[Q[k][j]].lowcost=weight;
//				}
			}
		}
	}

//	for(auto i:closedge){
//		cerr<<i.lowcost<<' ';
//	}
//	cerr<<endl;
	//Select minimum edge
	int min=-1,nu=0;
	for(int i=0;i<Q_vexnum;i++){
		if(min==-1&&closedge[i].lowcost>0){
			min=i;
		}
		else if(closedge[min].lowcost>closedge[i].lowcost&&closedge[i].lowcost>0){
			min=i;
		}
	}
	if(min>-1){
		int adjvex=closedge[min].adjvex;
		MstOrder.push_back(make_pair(adjvex,min));
		closedge[min].lowcost=0;
		mst1[min][0].parentCandidate.push_back(adjvex);
		mst1[adjvex][0].childCandidate[0].push_back(min);
		Visited_Set.insert(makePair(adjvex,min));
	}
	return 1;
}

int return_node_child_num(int node_id)
{
	return mst1[node_id][0].childCandidate[0].size();
}

int return_node_num_as_child(int node_id)
{
	int parent_id;
	parent_id=mst1[node_id][0].parentCandidate[0];

	for(int i=0;i<mst1[parent_id][0].childCandidate[0].size();i++)
	{
		if(node_id==mst1[parent_id][0].childCandidate[0][i])
		{
			return i;
		}
	}
}

void initial_mst1_candidate(int node_id)
{
	int child_num;
	child_num=return_node_child_num(node_id);
	struct MST candidate_tmp;
	candidate_tmp.flag_active=1;
	candidate_tmp.childCandidate.resize(child_num);

	int candidate_size;
	candidate_size=candidate[node_id].size();
	mst1[node_id].resize(candidate_size+1);

	for(int i=1;i<=candidate_size;i++)
	{
		mst1[node_id][i]=candidate_tmp;
	}

	for(int i=1;i<=candidate_size;i++)
	{
		mst1[node_id][i].id=candidate[node_id][i-1];
	}
}

void initial_mst1_candidate_all()
{
	for(int i=0;i<Q_vexnum;i++)
	{
		initial_mst1_candidate(i);
	}
}

bool update_node_candidate_by_active_flag(int node_id)
{
	vector <MST> candidate_vec_tmp;

	int active_num;
	active_num=0;
	for(int i=1;i<mst1[node_id].size();i++)
	{
		if(mst1[node_id][i].flag_active)
		{
			active_num++;
		}
	}
	candidate_vec_tmp.resize(active_num+1);

	if(active_num+1==mst1[node_id].size())
	{
		return 0;
	}

	candidate_vec_tmp[0]=mst1[node_id][0];
	int ii;
	ii=1;
	for(int i=1;i<mst1[node_id].size();i++)
	{
		if(mst1[node_id][i].flag_active)
		{
			candidate_vec_tmp[ii]=mst1[node_id][i];
			ii++;
		}
	}
	mst1[node_id]=candidate_vec_tmp;
	return 1;
}

void update_candidate_by_mst1_candidate(int node_id)
{
	vector<unsigned> candidate_vector_tmp;
	candidate_vector_tmp.resize(mst1[node_id].size()-1);

	for(int i=1;i<mst1[node_id].size();i++)
	{
		candidate_vector_tmp[i-1]=mst1[node_id][i].id;
	}
	candidate[node_id]=candidate_vector_tmp;
}

int node_num_when_insert_on_mst(int node_id)
{
	for(int i=0;i<Q_vexnum-1;i++)
	{
		if(node_id==MstOrder[i].second)
		{
			return i;
		}
	}
	return 0;
}

int update_candidate_by_a_single_edge(int edge_id)
{
	unsigned u=MstOrder[edge_id].first;
	unsigned v=MstOrder[edge_id].second;

	//计算节点v是节点u的第几个孩子
	int v_num_as_child;
	v_num_as_child=return_node_num_as_child(v);

	//初始化父亲和孩子候选的vector
	vector<int> parent_tmp;
	vector<vector<int>> child_tmp;
	child_tmp.resize(candidate[u].size());
	for(int j=0;j<candidate[u].size();j++)
	{
		child_tmp[j].clear();
	}

	//更新u的孩子候选和v的父亲候选
	for(int i=0;i<candidate[v].size();i++)
	{
		parent_tmp.clear();
		for(int j=0;j<candidate[u].size();j++)
		{
			if(search_edge(candidate[v][i],candidate[u][j]))
			{
				parent_tmp.push_back(candidate[u][j]);
				child_tmp[j].push_back(candidate[v][i]);
			}
		}
		mst1[v][i+1].parentCandidate=parent_tmp;
	}

	for(int j=0;j<candidate[u].size();j++)
	{
		mst1[u][j+1].childCandidate[v_num_as_child]=child_tmp[j];

	}

	//标记v的候选的状态
	for(int i=0;i<candidate[v].size();i++)
	{
		if(mst1[v][i+1].parentCandidate.size()==0)
		{
			mst1[v][i+1].flag_active=0;
		}
	}

	//标记u的候选的状态
	int r;
	int r_flag;
	r_flag=0;
	for(int j=0;j<candidate[u].size();j++)
	{
		if(mst1[u][j+1].childCandidate[v_num_as_child].size()==0)
		{
			mst1[u][j+1].flag_active=0;
			r_flag=1;
		}
	}

	//更新u和v的mst1 candidate候选vector
	bool u_flag;
	bool v_flag;
	u_flag=update_node_candidate_by_active_flag(u);
	v_flag=update_node_candidate_by_active_flag(v);
	//更新u和v的candidate候选vector
	if(u_flag)
	{
		update_candidate_by_mst1_candidate(u);
	}
	if(v_flag)
	{
		update_candidate_by_mst1_candidate(v);
	}

	//确定返回值
	if(edge_id==0)
	{
		return -1;
	}
	else
	{
		if(r_flag==1)
		{
//			cout<<"变"<<" ";
//			edge_id=node_num_when_insert_on_mst(u);
			return node_num_when_insert_on_mst(u);
		}
		else
		{
			return -1;
		}
	}
}
bool update_not_mst_candidate_by_edge(vector<bool> have_edge,int node_id){
	vector<MST> candidate_vec_tmp;
	int active_num=0;
	for(int i=0;i<have_edge.size();i++){
		active_num+=have_edge[i];
	}
	if(active_num==have_edge.size()){
		return 0;
	}
//	cout<<active_num<<' '<<have_edge.size()<<endl;
	candidate_vec_tmp.resize(active_num+1);
	int ii=0;
	candidate_vec_tmp[ii]=mst1[node_id][0];
	ii++;
	for(int i=1;i<=have_edge.size();i++){
		if(have_edge[i-1]){
			candidate_vec_tmp[ii]=mst1[node_id][i];
			ii++;
		}
	}
	mst1[node_id]=candidate_vec_tmp;
	return 1;
}
void update_candidate_of_not_mst_edge(int edge_id){
	int u=not_mst_edge[edge_id].first;
	int v=not_mst_edge[edge_id].second;

	vector<int> parent_tmp;
	vector<vector<int>> child_tmp;
	vector<unsigned> candidate_u_tmp;
	vector<unsigned>candidate_v_tmp;
	vector<bool> have_parent;
	vector<bool> have_child;
	have_parent.resize(candidate[v].size());
	have_child.resize(candidate[u].size());
	for(int i=0;i<candidate[v].size();i++){
		have_parent[i]=true;
	}
	child_tmp.resize(candidate[u].size());
	for(int j=0;j<candidate[u].size();j++)
	{
		have_child[j]=true;
		child_tmp[j].clear();
	}
	for(int i=0;i<candidate[v].size();i++)
	{
		parent_tmp.clear();
		for(int j=0;j<candidate[u].size();j++)
		{
			if(search_edge(candidate[v][i],candidate[u][j]))
			{
				parent_tmp.push_back(candidate[u][j]);
				child_tmp[j].push_back(candidate[v][i]);
			}
		}
		if(parent_tmp.size()!=0) {
			candidate_v_tmp.push_back(candidate[v][i]);
			mst1[v][i+1].parentCandidate=parent_tmp;
		}
		else{
			have_parent[i]=false;
		}
	}
	for(int j=0;j<candidate[u].size();j++){
		if(child_tmp[j].size()!=0){
			candidate_u_tmp.push_back(candidate[u][j]);
		}
		else{
			have_child[j]=false;
		}
	}
	candidate[u]=candidate_u_tmp;
	candidate[v]=candidate_v_tmp;
	update_not_mst_candidate_by_edge(have_parent,v);
	update_not_mst_candidate_by_edge(have_child,u);
}

int counter=0;//跳转的次数
int counter_step=0;//跳转的步长
void UpdateMstCandidateRecall(){
//	cout<<"开始：";
	int i=0;
	while(i<MstOrder.size()){
//		cout<<"更改边候选"<<MstOrder[i].first<<' '<<MstOrder[i].second<<endl;
		int node_recall=update_candidate_by_a_single_edge(i);
		if(node_recall==-1) i++;
		else {
			assert(node_recall<i);
			counter++;
			counter_step+=i-node_recall;
			i=node_recall;
		}
	}
}

void UpdateMstCandidate(){
	for(int i=0;i<MstOrder.size();i++){
//		cout<<"更改边候选"<<MstOrder[i].first<<' '<<MstOrder[i].second<<endl;
		update_candidate_by_a_single_edge(i);
	}
}

void update_candidate_by_not_mst(){
	for(int i=0;i<not_mst_edge.size();i++){
		update_candidate_of_not_mst_edge(i);
	}
}

void MSTdisplay_query(){

	cerr<<"生成树："<<mst1.size()<<endl;

	for(int i;i<Q_vexnum;i++){
		cout<<mst1[i][0].id<<'\t';//序号
		cout<<mst1[i][0].parentCandidate[0]<<'\t';//树父节点
		for(auto j:mst1[i][0].childCandidate[0]){
			cout<<j<<'\t';//树子结点
		}
		cout<<endl;
	}
	cerr<<"生成树顺序："<<endl;
	cout<<MstOrder.size()<<endl;
	for(auto i:MstOrder){
		cout<<i.first<<'-'<<i.second<<"  ";
	}

	cerr<<endl;
	for(int i=0;i<candidate.size();i++){
		candidate_after_update+=candidate[i].size();
		candidate_num.push_back(candidate[i].size());
		// cout<<i.size()<<' ';
		for(int j=0;j<candidate[i].size();j++){
			cout<<candidate[i][j]<<' ';
		}
		cout<<endl;
		for(int j=0;j<candidate[i].size();j++){
			cout<<mst1[i][j+1].id<<' ';
		}
		cout<<endl;
	}

	cout<<mst1.size()<<endl;
	for(int i=0;i<mst1.size();i++){
		for(int j=0;j<mst1[i].size();j++){
			cout<<"父亲"<<'\t';
			for(int k=0;k<mst1[i][j].parentCandidate.size();k++){
				cout<<mst1[i][j].parentCandidate[k]<<' ';
			}
			cerr<<'\n';
			cout<<'\t'<<mst1[i][j].id;
			cerr<<'\n'<<"孩子"<<'\t';
			for(int k=0;k<mst1[i][j].childCandidate.size();k++){
				for(int l=0;l<mst1[i][j].childCandidate[k].size();l++){
					cout<<mst1[i][j].childCandidate[k][l]<<' ';
				}
				cerr<<'\t';
			}
			cerr<<'\n';
		}
		cerr<<"==========================="<<endl;
	}
}
void MSTdisplay(){
	for(int i=0;i<candidate.size();i++){
		candidate_after_update+=candidate[i].size();
	}
}
int InsertChildCandidate(vector<MST>& vec,int id,vector<int> child){
	int low=1;
	int high=vec.size()-1;
	int mid;
	while(low<=high){
		mid=(low+high)/2;
		if(vec[mid].id<id){
			low=mid+1;
		}
		else if(vec[mid].id>id){
			high=mid-1;
		}
		else{
			low=mid;
			break;
		}
	}
	//找到插入位置，插入该节点
	if(low<vec.size()&&vec[low].id==id){
		if(child.empty()){
			//删除该节点
			vec.erase(vec.begin()+low);
			return 0;
		}
		vec[low].childCandidate.push_back(child);
	}
	else{
		if(child.empty()) return 0;
		MST target;
		target.id=id;
		target.childCandidate.push_back(child);
		vec.push_back(target);
	}
	return 1;
}
int InsertSort(vector<int>& vec,int target){
	int insertPosition=BinarySearch(vec,target);
	if(insertPosition==-1) return 0;
	else{
		vec.insert(vec.begin()+insertPosition,target);
	}
	return 1;
}
int BinarySearch(vector<int> vec,int target){
	int low=0;
	int high=vec.size()-1;
	int mid;
	while(low<=high){
		mid=(low+high)/2;
		if(vec[mid]==target) {
			return -1;
		}
		else if(vec[mid]<target){
			low=mid+1;
		}
		else{
			high=mid-1;
		}
	}
	return low+1;
}
void insert_sorted(vector<int>& v, int elem)
{
    const auto insert_pos(lower_bound(begin(v), end(v), elem));
    v.insert(insert_pos, elem);
}
/*int InsertEdgeCandidate(int recall){
	int u=MstOrder[recall].first;
	int v=MstOrder[recall].second;
//	MST mstCan;
	int recallIndex=-1;

	//初始化父亲节点
	vector<int> parent_tmp;
	vector<<vector<int>> child_tmp;
	child_tmp.resize(candidate[v].size());
	for(int i=0;i< candidate[v].size();i++){
		parent_tmp.clear();
		for(int j=0;j<candidate[u].size();j++){
			//如果存在j-k相连 k
			if(search_edge(candidate[v][i],candidate[u][j])){
				parent_tmp.push_back(candidate[u][j]);
				child_tmp[j].push_back(candidate[v][i]);//u节点的孩子
//						mst1[min][son+1].p_candidate.push_back(pa);
			}
		}
		if(!parent_tmp.empty()) {
			mst1[v]parent_tmp;
			//更改返回标志和返回节点
			recallFlag=true;
		}

	}
	for(int i=0;i<candidate[u].size();i++){
		mst1[u][i+1].childCandidate[v]
	}
	//更改子结点
	vector<MST> temp;
	for(int i=0;i<sonCandidate.size();i++){
		if(!sonCandidate[i].parentCandidate.empty()){
			temp.push_back(sonCandidate[i]);
		}
		else{
//			cout<<"删除前："<<sonCandidate.size()<<endl;
//			sonCandidate.erase(sonCandidate.begin()+i);
//			cout<<"删除后："<<sonCandidate.size()<<endl;
//			i--;
		}
	}
	mst1[min].resize(temp.size()+1);
	for(int i=0;i<temp.size();i++){
		mst1[min][i+1]=temp[i];
		cout<<temp[i].id;
	}
	//查找迭代位置
	if(recallFlag)
	{
		int parent=mst1[adjvex][0].parentCandidate[0];
		for(int i=recall;i>=0;i--){
			if(MstOrder[i].second==parent){
				recallIndex=i;
				break;
			}
		}
	}
	//更改候选列表;
	vector<unsigned> candidateTemp(mst1[min].size()-1);
    for(int i=0;i<mst1[min].size()-1;i++){
		candidateTemp[i]=mst1[min][i+1].id;
	}
	candidate[min]=candidateTemp;
	candidateTemp.clear();
	candidateTemp.resize(mst1[adjvex].size()-1);
	for(int i=0;i<mst1[adjvex].size()-1;i++){
		candidateTemp[i]=mst1[adjvex][i+1].id;
	}
	candidate[adjvex]=candidateTemp;
	return recallIndex;
}*/

//blog.csdn.net/wangyi463295828/article/details/135111385
//int SelectSingle(){
//
////	int k=MinNode_cannum();
//	for(int k=0;k<Q_vexnum;k++){
//		if(closedge[k].lowcost==0){
//			for(int j=0;j<Q[k].size();j++){
//				if(closedge[Q[k][j]].lowcost==-1||candidate_num[k]+candidate_num[Q[k][j]]<closedge[Q[k][j]].lowcost){
//					closedge[Q[k][j]].adjvex=k;
//					closedge[Q[k][j]].lowcost=candidate_num[Q[k][j]]+candidate_num[k];
//				}
//			}
//		}
//	}
////	for(auto i:closedge){
////		cerr<<i.lowcost<<' ';
////	}
////	cerr<<endl;
//	int min=-1,nu=0;
//	for(int i=0;i<Q_vexnum;i++){
//		if(min==-1&&closedge[i].lowcost>0){
//			min=i;
//		}
//		else if(closedge[min].lowcost>closedge[i].lowcost&&closedge[i].lowcost>0){
//			min=i;
//		}
//	}
//	if(min>-1){
//		closedge[min].lowcost=0;
//		int adjvex=closedge[min].adjvex;
//		mst1[min][0].id=min;
//		mst1[min][0].p_candidate.push_back(adjvex);
//		mst1[adjvex][0].c_candidate[0].push_back(min);
//		int j,k;
//		for(j=0;j< candidate[closedge[min].adjvex].size();j++){
//			bool ismst=false;
//			for(k=0;k<candidate[min].size();k++){
//				if(search_edge(candidate[closedge[min].adjvex][j],candidate[min][k])){
//					mstside[mst_num].push_back(make_pair(j,k));
//					ismst=true;
//				}
//				else{
//					candidate[min].erase(candidate[min].begin()+k);
//				}
//			}
//			if(ismst==false) {
//				candidate[closedge[min].adjvex].erase(candidate[closedge[min].adjvex].begin()+j);
//				int root=mst_map[make_pair(mst[closedge[min].adjvex][1],closedge[min].adjvex)];
//				ClearSide(root,closedge[min].adjvex);
//			}
//		}
//		mst_num++;
//	}
//
//	return 1;
//}
//int ClearSide(int root,int key){
//	if(root==-1) return 1;
//	else{
//		int low=0,high=mstside[root].size()-1;
//		int mid;
//		while(low<=high){
//			mid=(low+high)/2;
//			if(mstside[root][mid].second==key){
//				mstside[root].erase(mstside[root].begin()+mid);
//				return 0;
//			}
//			else if(mstside[root][mid].second<key){
//				low=mid+1;
//			}
//			else if(mstside[root][mid].second>key){
//				high=mid+1;
//			}
//		}
//
//	}
//}

//int InitMST(){
////	mst.clear();
////	mstside.clear();
////	mst_map.clear();
//	mst.resize(Q_vexnum);
//	mstside.resize(Q_vexnum-1);
//	int root,C=-1;
//	for(int i=0;i<Q_vexnum;i++){
//		mst[i].push_back(i);
//		if(C==-1){
//			root=i;
//			C=0;
//		}
//		else if(candidate_num[i]<candidate_num[root]){
//			root=i;
//		}
//		closedge[i].lowcost=-1;
//	}
//	closedge[root].lowcost=0;
//	mst[root].push_back(-1);
//	for(auto i:closedge){
//		cout<<i.lowcost<<' ';
//	}
//	cout<<endl;
//	return root;
//}






