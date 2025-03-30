# M2M

Release Date: March 29, 2025

Author

	~Changyong Yu (Northeastern University in CHINA)
	~Ming Xu (Northeastern University in CHINA)
	~Yufan Chen (Northeastern University in CHINA)

1.Introduction

	Subgraph matching is one of the most basic and important problems in graph data analysis due to its wide utilization in a variety of applications. It has always been an open challenge due to that it is theoretically an NP-hard problem. Recent efforts have made good progress in most of the application scenarios. However, it is still full of potentialities to study more efficient algorithms to address this problem. Here, we propose a new algorithm, called M2M, for subgraph matching based on minimum spanning tree and candidate graph. The M2M algorithm first optimizes the matching order of the query nodes based on minimum spanning tree to reduce the candidate space size. Then an efficient strategy based on a minimum to minimum idea is proposed for generating the minimum candidate graph of the query. Moreover, several optimization tricks are proposed such as indexing the candidate graph, calculating the size of the embeddings, enumerating the embeddings and so on. 

2.Test Data

	M2M leverages a minimum-to-minimum auxiliary structure to facilitate the stepwise querying of subgraph embeddings within the data graph. We used real-world datasets to evaluate the algorithms. 
	In work, we tested M2M with datasets used in paper "In-Memory Subgraph Matching: An In-depth Study". It contains 8 real-world datasets, including the datasets of Yeast, Human, HPRD, WordNet and so on. We download the data using the website address:  https://hkustconnect-my.sharepoint.com/:u:/g/personal/ssunah_connect_ust_hk/EQnXTic0PK9Fo1gkdDZRKOIBFIyMeBTP5rbju2ZfQdj-QA?e=SfGa8X.We have also uploaded some data in the 'test_data' directory

3.Building Notes

Our project, built using the CMake build system, adheres to the following directory structure:

```
.
├── build
├── CMakeLists.txt
├── config.h.in
├── include
├── src
└── test_data
```

This codebase is developed in C++ and is compiled and executed on Linux-based operating systems. The prerequisites for building and running this software include the prior installation of CMake and GCC (GNU Compiler Collection). The compilation process is as follows:

```b
mkdir build
cd build
cmake ..
make
```

We have uploaded a `build` directory, and we have successfully compiled the current files using the aforementioned procedure.

4.Usage Notes

```
$ ./M2M -Df <Dataset graph file> -Qf <Query graph file> [-Out <output option>] [-MeN <max enbedding num>] 

This tool is designed to identify embeddings of a query subgraph within a given database graph. The database graph file is specified via the -Df flag, **and the query graph file via the -Qf flag.** The input database graph and query graph should adhere to the input format specification detailed in Section 6. The output is a set of nodes in the database graph that correspond to the embeddings of the query subgraph.
```

Running example

```
$ ./M2M -Df dblp.graph -Qf query_dense_4_4.graph

This tool is utilized to analyze the embeddings of the query graph 'query_dense_4_4.graph' in the database graph 'dblp.graph', and by default, it outputs 500 embeddings.
```

5.Parameter Settings

The format of a parameter of M2M in the command line is a pair of strings, here we denote the pair as (-p, [q]) or (-p,<q>). String p is the name of the parameter. String q is the value of the parameter **inputted** in the command line. [q] represents that the parameter is an optional parameter. <q> represents that the parameter is a necessary parameter.

@parameter (-Df,\<Dataset graph file\>)

	The -Df parameter specifies the file path of the labeled database graph. This file must be in input format.

@parameter (-Qf,\<Query graph file\>)

	The -Qf parameter specifies the file path of the query graph file. This file must be in input format.

@parameter (-Out,\<Output option\>)

	The -Out parameter offers the option to control the output of embeddings. When the -Out parameter is set to 1, embeddings are outputted; otherwise, only the count of embeddings is outputted. The default setting for the -Out parameter is 1, which corresponds to outputting embeddings.

@parameter (-MeN,\<Max enbedding num\>)

	The -MeN parameter serves to specify the number of embeddings to be output. If the number of embeddings found exceeds the value of the -MeN parameter, the tool will output at most -MeN embeddings. The default value for the -MeN parameter is 500.

6.Input/Output Format

1)Input Format

```
t [Number of Nodes] [Number of Edges]
v [Node ID] [Node Label] [Node Degree]
    ~ Graph is undirected, degree is the sum of in-degree and out-degree.
e [Start Vertex] [End Vertex] 0
    ~ Edge is undirected.
```

2)Output Format

```
[x]*[n]
    ~ x represents the node ID from the database graph.
    ~ n represents the number of nodes in the query graph.
Embedding num is :[num]
    ~ num represents the number of embeddings.
```

7.License

	See LICENSE

8.Contacts

	Please e-mail your feedback at cyyneu@126.com.



