
#include "test.h"
extern int counter;
extern int counter_step;
void test(){
//	struct timeval start;
//	struct timeval end;
	CandidateCompute();
//	display(0);
//	display(1);
	Visited_Set.clear();
//	gettimeofday(&start,NULL);
	cout<<'1'<<endl;
	CreateMST();
	initial_mst1_candidate_all();
	cout<<'2'<<endl;
	
	UpdateMstCandidateRecall();
	cout<<'3'<<endl;

	create_not_mst_edge();
	cout<<'4'<<endl;

	update_candidate_by_not_mst();
	cout<<'5'<<endl;

	create_embedding_of_mst();
	visit_mst(MstOrder[0].first);
	// MSTdisplay();
	cout<<"embedding num is:\t"<<embedding_num<<endl;
//	cout<<query_filename<<endl;
//	cout<<"更新前候选个数"<<candidate_before_update<<'\t'<<"更新后候选个数"<<candidate_after_update<<endl;
	//	display(0);
	//	display(1);
//	gettimeofday(&end,NULL);
//	cout<<"filter_num="<<filter_num<<" positive_num="<<positive_num<<" rigth_num="<<right_num<<endl;
//	cout<<"AD_SIZE="<<AD_SIZE<<endl<<" filter_time="<<bloom_time<<" ms"<<
//	"tw0_time = "<<two_time<<"ms"
//	" seq_time="<<(seq_time)<<"ms"<<endl;
//	cout<<"all time="<<(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec))<<"ms"<<endl;

}
void test_file(char* data_graph_filename,char* query_graph_filename){
	struct timeval start;
	struct timeval end;
	filter1.reset();
	int t_G=readGraph(data_graph_filename,G,G_degree,G_v_nodelabel,G_vexnum,G_arcnum);
	if(t_G) LabelCompute(0);
	string line;
	ifstream stream(query_graph_filename);
	if(!stream.eof()){
		getline(stream,line);
		int graph_num=1;
		gettimeofday(&start,NULL);
		while(stream.good()){
			char* query_filename=&line[0];
			mst1.resize(0);
			MstOrder.resize(0);
			Q.resize(0);
			Q_degree.resize(0);
			Q_v_nodelabel.resize(0);
			Q_labelvec.resize(0);
			candidate.resize(0);
			int t_Q=readGraph(query_filename,Q,Q_degree,Q_v_nodelabel,Q_vexnum,Q_arcnum);
			if(t_Q) LabelCompute(1);
			test();


			if(graph_num%200==0){
				gettimeofday(&end,NULL);
//				ofs<<query_filename<<endl;
//				ofs<<"更新前候选个数"<<candidate_before_update/200<<'\t'<<"更新后候选个数"<<candidate_after_update/200<<endl;
//				ofs<<"query_time="<<(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec))<<"ms"<<endl;
				cout<<query_filename<<'\t'<<not_mst_edge.size()<<'\t';
				cout<<candidate_before_update/200<<'\t'<<candidate_after_update/200
						<<'\t'<<(candidate_before_update-candidate_after_update)/200<<'\t'<<(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec))/200;
				cout<<'\t'<<counter*1.0/200<<'\t'<<counter_step*1.0/200<<endl;
				gettimeofday(&start,NULL);
				candidate_before_update=0;
				candidate_after_update=0;
				counter=0;
				counter_step=0;
			}
			getline(stream,line);
			graph_num++;
		}
	}

}
//string path ="";
//    argc=4;
//    argv[0]="-data";
//    argv[1]="dataset//dblp//data_graph//dblp.graph";
//    argv[2]="-query";
//    char* data[]={
////			"dataset//human//data_graph//human.graph",
////			"dataset//yeast//data_graph//yeast.graph",
////			"dataset//hprd//data_graph//hprd.graph",
//    		"dataset//dblp//data_graph//dblp.graph",
//			//"dataset//eu2005//date_graph//eu2005.graph",
//			//"dataset//patents//data_graph//patents.graph",
//			//"dataset//wordnet//data_graph//wordnet.graph",
////			"dataset//youtube//data_graph//youtube.graph",
//    };
//    char* human[]={
//			"dataset//human//query_graph//query_dense_12_1.graph",
//    		"dataset//human//query_graph//query_dense_4_4.graph",
//			"dataset//human//query_graph//query_dense_8_1.graph",
//			"dataset//human//query_graph//query_dense_16_16.graph",
//			"dataset//human//query_graph//query_dense_20_10.graph",
//			"dataset//human//query_graph//query_sparse_8_1.graph",
//			"dataset//human//query_graph//query_sparse_16_1.graph",
//			"dataset//human//query_graph//query_sparse_12_1.graph",
//			"dataset//human//query_graph//query_sparse_20_1.graph"
//    };
//    char* yeast[]={
//			"dataset//yeast//query_graph//query_dense_24_7.graph",
//			"dataset//yeast//query_graph//query_dense_4_4.graph",
//			"dataset//yeast//query_graph//query_dense_8_1.graph",
//			"dataset//yeast//query_graph//query_dense_16_16.graph",
//			"dataset//yeast//query_graph//query_dense_32_10.graph",
//			"dataset//yeast//query_graph//query_sparse_8_1.graph",
//			"dataset//yeast//query_graph//query_sparse_16_1.graph",
//			"dataset//yeast//query_graph//query_sparse_24_1.graph",
//			"dataset//yeast//query_graph//query_sparse_32_1.graph"
//	};
//    char* hprd[]={
//			"dataset//hprd//query_graph//query_dense_24_7.graph",
//			"dataset//hprd//query_graph//query_dense_4_4.graph",
//			"dataset//hprd//query_graph//query_dense_8_1.graph",
//			"dataset//hprd//query_graph//query_dense_16_16.graph",
//			"dataset//hprd//query_graph//query_dense_32_10.graph",
//			"dataset//hprd//query_graph//query_sparse_8_1.graph",
//			"dataset//hprd//query_graph//query_sparse_16_1.graph",
//			"dataset//hprd//query_graph//query_sparse_24_1.graph",
//			"dataset//hprd//query_graph//query_sparse_32_1.graph"
//    	};
//    char* query[]={
//    			"dataset//dblp//query_graph//query_sparse_32_1.graph",
//    			"dataset//dblp//query_graph//query_sparse_16_1.graph",
//    			"dataset//dblp//query_graph//query_sparse_24_1.graph",
//    			"dataset//dblp//query_graph//query_dense_4_4.graph",
//    			"dataset//dblp//query_graph//query_dense_8_1.graph",
//    			"dataset//dblp//query_graph//query_dense_32_10.graph",
//    			"dataset//dblp//query_graph//query_dense_24_7.graph",
//    			"dataset//dblp//query_graph//query_dense_16_16.graph",
//    			"dataset//dblp//query_graph//query_sparse_8_1.graph",
//        	};
//
//	char *data_graph_filename;
//	char *query_graph_filename;
//	char Method=' ';
//	string h="";
//	int random_seed;
////	F_N_weight=1;
//	for(int k=0;k<1;k++){
//		argv[1]=data[k];
//		for(int j=0;j<9;j++){
//			argv[3]=query[j];
//			for (int i = 0; i < argc; ++i) {
//				string arg = argv[i];
////				cout<<argv[i]<<endl;
//				if (arg == "-data") {         // graph file
//					data_graph_filename = argv[++i];
//					cout<<argv[i]<<endl;
//				}
//				if (arg == "-query") {         // query file
//					query_graph_filename = argv[++i];
//					cout<<argv[i]<<endl;
//				}
//		//		else if (arg == "-method") {
//		//			Method = argv[++i][0];
//		//		}else if (arg == "-seed") {
//		//			random_seed = atoi(argv[++i]);
//		//		}else if (arg == "-h") {
//		//			h = "help";
//		//		}else if(arg == "-budget"){
//		//			Budget =atoi(argv[++i]);
//		//			M=Budget;
//		//		}else if(arg == "-fw"){
//		//			F_N_weight=atof(argv[++i]);
//		//		}else if(arg == "-T"){
//		//			Threshold =atoi(argv[++i]);
//		//		}else if(arg == "-M"){
//		//			M=atoi(argv[++i]);
//		////		}
//			}
//
//			//测试readGraph()
//			struct timeval start;
//			struct timeval end;
//			gettimeofday(&start,NULL);
//			filter1.reset();
//			int t_G=readGraph(data_graph_filename,G,G_degree,G_v_nodelabel,G_vexnum,G_arcnum);
//			if(t_G) LabelCompute(0);
//			int t_Q=readGraph(query_graph_filename,Q,Q_degree,Q_v_nodelabel,Q_vexnum,Q_arcnum);
//			if(t_Q) LabelCompute(1);
//			test();
//		//	display(1);
//			gettimeofday(&end,NULL);
//			cout<<"time = "<<(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec))<<"ms"<<endl;
//		}
//	}
