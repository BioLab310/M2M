#include"putin.h"


int readGraph(char* path,vector<vector<uint32_t>>& G,vector<uint32_t>& degree,vector<uint32_t>& v_nodelabel,unsigned &vexnum,unsigned &arcnum)
{	//参数：文件路径 邻接表 结点的度 结点的值
	ifstream fin;
	fin.open(path, ios::in );
	//uint32_t nodeNum, edgeNum;
	int lineNum=0;

	candidate.clear();
	G.resize(0);
	string line;
	ifstream file(path);
	 if (!file.is_open())
	 {
       cout << "无法打开文件\n";
       return 0;
	  }

	 while(getline(file,line))
	 {
		 lineNum++;
		 istringstream iss(line);
		 char letter;
		 int num1,num2,num3;

		 if(lineNum == 1)
		 {	//第一行
			 iss >> letter >> num1 >> num2;
			 //cout << "结点个数：" << num1 << "边的个数" << num2 << endl;
			 G.resize(num1);	//设置邻接表的高度
			 vexnum=num1;
			 arcnum=num2;
		 }
		 else
		 {
			 iss >> letter >> num1 >> num2 >> num3;
			 if(letter == 'v')	//结点信息
			 {	//结点数据
				 degree.push_back(num3);
				 v_nodelabel.push_back(num2);
				 //cout << letter << num2 << num3 << endl;
			 }
			 else if(letter == 'e')	//构建邻接表
			 {
				G[num1].push_back(num2);
				G[num2].push_back(num1);
				if(num1>num2){
					bloom_edge[0]=num1;
					bloom_edge[1]=num2;
					BloomSet1(bloom_edge);
				}
				else{
					bloom_edge[0]=num2;
					bloom_edge[1]=num1;
					BloomSet1(bloom_edge);
				}

				 //cout << letter << num2 << num3 << endl;
			 }

		 }
	 }
//	 for(unsigned i=0;i<G.size();i++){
//		 sort(G[i].begin(),G[i].end());//默认升序
//	 }
	 file.close();
	 //cout<<"finish readGraph" <<endl;
	 return 1;
}

void display(int flag){
	if(flag==0){
		//打印结点度
		cout << "结点的度：" << endl;
		for(auto i : G_degree)
		{
			cout << i << " ";
		}
		cout << endl;
		//打印结点值
		cout << "结点的值：" << endl;
		for(auto i : G_v_nodelabel)
			{
				cout << i << " ";
			}
		cout << endl;
		//打印前三行
		cout << "邻接表前三行：" << endl;
		for(int i=0;i<G.size();i++)
		{
			for(auto j : G[i])
			{
				cout << j << " ";
			}
			cout<<'\t'<<"邻接label向量:"<<' ';
			for(auto j:G_labelvec[i]){
				cout<<j<<" ";
			}
			cout << endl;
		}
		cout<<endl;
	}
	else if(flag==1){
		//打印结点度
		cout << "结点的度：" << endl;
		for(auto i : Q_degree)
		{
			cout << i << " ";
		}
		cout << endl;
		//打印结点值
		cout << "结点的值：" << endl;
		for(auto i : Q_v_nodelabel)
			{
				cout << i << " ";
			}
		cout << endl;
		//打印前三行
		cout << "邻接表前三行：" << endl;
		for(int i=0;i<Q_vexnum;i++)
		{
			for(int j=0;j<Q[i].size();j++){
				cout<<Q[i][j]<<" ";
			}
//			cout<<"邻接label向量:"<<' ';
//			for(auto j:Q_labelvec[i]){
//				cout<<j<<" ";
//			}
//			cout<<"candidate向量："<<' ';
//			for(auto j:candidate[i]){
//				cout<<j<<' ';
//			}
			cout << endl;
		}
		cout<<endl;
	}
}
//int LabelCompute(/*vector<vector<unsigned>> G,unsigned vexnum,*/vector<uint32_t> v_nodelabel,vector<vector<uint32_t>>& labelvec){

int LabelCompute(int flag){
	unsigned max=0;
	for(auto i:G_v_nodelabel){
		if(max<=i) max=i;
	}
	//cout<<"the largest label is:"<<max+1<<endl;
	//labelnum = vector<vector<unsigned>>(vexnum, vector<unsigned>(max+1,0));
	if(flag==0){
		G_labelvec.clear();
		G_labelvec.resize(G_vexnum);
		for(int i=0;i<G_vexnum;i++){
			G_labelvec[i].resize(max+1,0);
			for(auto j:G[i]){
				G_labelvec[i][G_v_nodelabel[j]]++;
			}
		}
	}
	else{
		Q_labelvec.clear();
		Q_labelvec.resize(Q_vexnum);
		for(int i=0;i<Q_vexnum;i++){
			Q_labelvec[i].resize(max+1,0);
			for(auto j:Q[i]){
				Q_labelvec[i][Q_v_nodelabel[j]]++;
			}
		}
	}

	return 0;
}
