
#include "searchedge.h"
int right_num=0;
int positive_num=0;
long filter_num=0;
double two_time=0;
double seq_time=0;
double bloom_time=0;
int search_edge(int num1,int num2){
	struct timeval start;
	struct timeval end;
	filter_num++;
	int conse;
	if(num1>num2){
		bloom_edge[0]=num1;
		bloom_edge[1]=num2;
		conse=Filter(bloom_edge,1);
		if(!conse) return 0;
	}
	else{
		bloom_edge[0]=num2;
		bloom_edge[1]=num1;
		conse=Filter(bloom_edge,1);
		if(!conse) return 0;
	}
	positive_num++;

	int min_vex=adj_min(num1,num2);
	int max_vex=adj_max(num1,num2);
	if(max_vex>G[min_vex].back()||max_vex<G[min_vex][0]){
		return 0;
	}
	if(G_degree[min_vex]>=AD_SIZE){
//		gettimeofday(&start,NULL);
		conse=two_search(min_vex,max_vex);
//		gettimeofday(&end,NULL);
//		two_time+=(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec));
		if(conse==-1) return 0;
		else {
			right_num++;
			return 1;
		}

	}
	else{
//		gettimeofday(&start,NULL);
		conse=seq_search(min_vex,max_vex);
//		gettimeofday(&end,NULL);
//		seq_time+=(1000*(end.tv_sec-start.tv_sec)+0.001*(end.tv_usec-start.tv_usec));
		if(conse==-1) return 0;
		else {
			right_num++;
			return 1;
		}

	}
}

int adj_min(int num1,int num2){
	if(G_degree[num1]<=G_degree[num2]) return num1;
	else return num2;
}
int adj_max(int num1,int num2){
	if(G_degree[num1]>G_degree[num2]) return num1;
	else return num2;
}

int two_search(unsigned num,unsigned key){
	int low=0;
	int high=G[num].size()-1;
	int mid;
	while(low<high){
		mid=(low+high)/2;
		if(key>G[num][mid]) {
			if(key<G[num][mid+1]) return -1;
			low=mid+1;
		}
		else if(key<G[num][mid]) {
			if(key>G[num][mid-1]) return -1;
			high=mid-1;
		}
		else if(key==G[num][mid]) return mid;
		else if(key>G[num][low]) return -1;
	}
	return -1;
}

int seq_search(int num,int key){
	for(unsigned i=0;i<G[num].size();i++){
		if(G[num][i]==key) return i;
		else if(G[num][i]>key) return -1;
	}
	return -1;
}
int banary_search(int target,vector<unsigned>elem){
	int low=0;
	int high=elem.size()-1;
	while(low<=high){
		int mid=(low+high)/2;
		if(elem[mid]<target){
			low=mid+1;
		}
		else if(elem[mid]>target){
			high=mid-1;
		}
		else if(elem[mid]==target){
			return mid;
		}
	}
	return -1;
}
