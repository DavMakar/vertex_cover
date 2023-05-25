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
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

using Matrix = std::vector<std::vector<int>> ;
using Edge = std::pair<int,int>;
using Verteces = std::set<int>;
using Vector = std::vector<int>;

void show_image(const char*);

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

	private: // For graph visualization
		void add_verteces_for_render(Agraph_t*);
		void render_input_image(const char* inputImageName);
	public:
		void render_output_image(const char* outputImageName, Vector cover);
	
	public:
		Matrix adjacency_matrix;
		Verteces verteces;
		std::vector<Edge> edges;
        int	vertex_count;
};

#endif // GRAPH_HPP