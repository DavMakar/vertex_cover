#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <set>

using Matrix = std::vector<std::vector<int>> ;
using Edge = std::pair<int,int>;
using Verteces = std::set<int>;
using Vector = std::vector<int>;

class Graph
{
    public:
		Graph(const char* filename);   
	public:
		void fill_matrix(int u , int v);
		void print_graph();
		Verteces approx_min_cover();
		Vector brute_force_min_cover();
	private:
		bool is_vertex_cover(const Vector&);
	public:
		Matrix adjacency_matrix;
		Verteces verteces;
		std::vector<Edge> edges;
        int	vertex_count;
};

#endif // GRAPH_HPP