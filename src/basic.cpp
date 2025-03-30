#include "basic.h"

vector<vector<uint32_t>> G;
vector<uint32_t> G_degree ;
vector<uint32_t> G_v_nodelabel;
//vector<uint32_t>labelid;
vector<vector<uint32_t>>G_labelvec;
//map<uint32_t,unsigned> label_map;
unsigned G_vexnum;
unsigned G_arcnum;
int AD_SIZE=90;
int output_choise = 1;
int embedding_num=0;
int best_embedding_num = 500;

bitset<	QQQQ> filter1;
bitset<	QQQQ> filter2;
bitset<	QQQQ> filter3;
int bloom_edge[2];
vector<vector<MST>> mst1;
vector<pair<int,int>> MstOrder;
vector<int> M_index_uu;
vector<int> M;
