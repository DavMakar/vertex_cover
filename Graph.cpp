#include "Graph.hpp"

void Graph::fill_matrix(int u , int v){
        adjacency_matrix[u][v] += 1;
        adjacency_matrix[v][u] += 1;
}

void Graph::print_graph(){
    for(auto i : adjacency_matrix){
        for(auto j : i){
            std::cout << j << " ";
        }
        std::cout<<std::endl;
    }
}

Graph::Graph(const char* filename)
{
	std::ifstream file{filename};

    int u, v;


    while (file >> u >> v)
    {
        edges.push_back({u,v});
        verteces.insert(u);
        verteces.insert(v);
    }
    file.close();

	vertex_count = verteces.size();

	adjacency_matrix = Matrix(vertex_count , std::vector<int>(vertex_count));	
   
    for(const auto& [u,v] : edges){
        fill_matrix(u, v);
    }
}

bool Graph::is_vertex_cover(const Vector& subset) {
    std::unordered_set<int> vertexSet(subset.begin() , subset.end());
    for (const auto& [u, v] : edges) { 
        if (vertexSet.find(u) == vertexSet.end() && vertexSet.find(v) == vertexSet.end()) {
            return false;
        }
    }
    return true;
}

Vector Graph::brute_force_min_cover() {
    int n = verteces.size();
    Vector cover;
    Vector bestCover;
    int minCoverSize = n;
    for (int mask = 0; mask < (1 << n); mask++) { //2^n
        cover.clear();
        for (int i = 0; i < n; i++) { // n
            if (mask & (1 << i)) {
                cover.push_back(*(std::next(verteces.begin(), i)));
            }
        }
        if (cover.size() < minCoverSize && is_vertex_cover(cover)) {
            minCoverSize = cover.size();
            bestCover.clear();
            std::copy(cover.begin(),cover.end(),std::back_inserter(bestCover));
        }
    }
    return bestCover;
}


Verteces Graph::approx_min_cover() {
    Verteces C;
    auto E_ = edges;
    while (!E_.empty())
    {
        Edge e = E_.front();
        auto new_end = std::remove_if(E_.begin() , E_.end(), [e](Edge f){
            return ((e.first == f.first || e.first == f.second) || 
                    (e.second == f.second || e.second == f.first));
        });
        E_.erase(new_end , E_.end());
        C.insert(e.first);
        C.insert(e.second);
    }
    return C;
    // C = 0
    // e = (1,2)
    // E_ = (1,2) ,(4,1), (2,4) , (1,3)
 
    // C = {1,2}
    // e = 
    // E_ = (1,3) 
}
