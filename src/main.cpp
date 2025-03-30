#include "basic.h"
#include "putin.h"
#include "bloomfilter.h"
#include "test.h"

int main(int argc, char * argv[]){
    string path ="";
	char *data_graph_filename;
	char *query_graph_filename;
	char Method=' ';
	string h="";
	int random_seed;
	bool query_test=false;
//	F_N_weight=1;
	for (int i = 0; i < argc; ++i) {
		string arg = argv[i];
//				cout<<argv[i]<<endl;
		if (arg == "-Df") {         // graph file
			data_graph_filename = argv[++i];
			cout<<argv[i]<<endl;
		}
		else if (arg == "-Qf") {         // query file
			query_graph_filename = argv[++i];
			//cout<<argv[i]<<endl;
		}
		else if (arg == "-Out"){
			char c = *argv[++i];
			output_choise= c-'0';
			cout<<output_choise<<endl;
		}
		else if (arg == "-MeN"){
			best_embedding_num= atoi(argv[++i]);
		}
		else if(arg=="-test"){
			query_graph_filename = argv[++i];
			query_test=true;
			cout<<argv[i]<<endl;
		}
	}

	//测试readGraph()
	struct timeval start;
	struct timeval end;
	gettimeofday(&start,NULL);
	filter1.reset();
	if(query_test){
		test_file(data_graph_filename,query_graph_filename);
	}
	else{
		int t_G=readGraph(data_graph_filename,G,G_degree,G_v_nodelabel,G_vexnum,G_arcnum);
		if(t_G) LabelCompute(0);
		int t_Q=readGraph(query_graph_filename,Q,Q_degree,Q_v_nodelabel,Q_vexnum,Q_arcnum);
		if(t_Q) LabelCompute(1);
		test();
	}
//	display(1);
	gettimeofday(&end,NULL);
	cout<<"time = "<<(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec))<<"ms"<<endl;
	return 0;
}
