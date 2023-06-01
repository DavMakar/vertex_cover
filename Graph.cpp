#include "Graph.hpp"
#include <cstdlib> 

void Graph::add_verteces_for_render(Agraph_t* g)
{
    for (const auto& [u, v] : edges) {
        Agnode_t* v1 = agnode(g, const_cast<char*>(std::to_string(u).c_str()), true);
        Agnode_t* v2 = agnode(g, const_cast<char*>(std::to_string(v).c_str()), true);
        agedge(g, v1,v2,nullptr,true);
    }
}

void Graph::render_input_image(const char* input_image_name)
{
    std::string filename = input_image_name;
    std::string name = filename.substr(0, filename.length() - 3);
    std::string image_extension = "png";
    filename = name + image_extension;

    Agraph_t* g = agopen("gr", Agundirected, nullptr);

    add_verteces_for_render(g);

    GVC_t* gvc = gvContext();
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, image_extension.c_str(), filename.c_str());

    agclose(g);
    gvFreeLayout(gvc, g);
    gvFreeContext(gvc);
}

void Graph::render_output_image(const char *outputImageName, Vector cover)
{
    Agraph_t* g = agopen("gr", Agundirected, nullptr);

    add_verteces_for_render(g);

    for (const auto& v : cover) {
        Agnode_t* n = agfindnode(g, const_cast<char*>(std::to_string(v).c_str()));
        if (n) {
            agsafeset(n, const_cast<char*>("color"), const_cast<char*>("red"), const_cast<char*>(""));
            agsafeset(n, const_cast<char*>("style"), const_cast<char*>("filled"), const_cast<char*>(""));
            agsafeset(n, const_cast<char*>("fillcolor"), const_cast<char*>("firebrick2"), const_cast<char*>(""));
        }
    }

    GVC_t* gvc = gvContext();
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", outputImageName);

    agclose(g);
    gvFreeLayout(gvc, g);
    gvFreeContext(gvc);
}


Graph::Graph(const char* filename)
{
	std::ifstream file{filename};
    int u, v;
    
    while (file >> u >> v)
    {
        if(std::end(edges) == std::find_if(edges.begin(),edges.end(),[u,v](Edge e){
            return (e.first == u && e.second == v) || (e.first == v && e.second == u); 
        })){
            edges.push_back({u,v});
            verteces.insert(u);
            verteces.insert(v);
        }
    }
    file.close();

    render_input_image(filename);
	vertex_count = verteces.size();
    vertexVector = Vector(verteces.begin(), verteces.end());
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
    int n = vertexVector.size();
    Vector cover;
    Vector bestCover = vertexVector;
    int minCoverSize = n;
    for (int mask = 0; mask < (1 << n); mask++) { //2^n
        for (int i = 0; i < n; i++) { // n
            if (mask & (1 << i)) {
                cover.push_back(vertexVector[i]);
            }
        }
        if (cover.size() < minCoverSize && is_vertex_cover(cover)) {
            minCoverSize = cover.size();
            bestCover.clear();
            std::copy(cover.begin(),cover.end(),std::back_inserter(bestCover));
        }
        cover.clear();
    }
    return bestCover;
}

Vector Graph::approx_min_cover()
{
    Vector C;
    auto E_ = edges;
    while (!E_.empty())
    {
        Edge e = E_.front();
        C.push_back(e.first);
        C.push_back(e.second);
        auto new_end = std::remove_if(E_.begin() , E_.end(), [e](Edge f){
            return ((e.first == f.first || e.first == f.second) || 
                    (e.second == f.second || e.second == f.first));
        });
        E_.erase(new_end , E_.end());
    }
    return C;
}

struct EdgeComparator {
    bool operator()(const Edge& e1, const Edge& e2) const {
        if (e1.first != e2.first) {
            return e1.first < e2.first;
        }
        return e1.second < e2.second;
    }
};

Vector Graph::approx_min_cover_v2()
{
    Vector C;
    std::unordered_set<int> V; 
    std::set<Edge, EdgeComparator> E_;  

    for (const auto& edge : edges) {
        E_.emplace(edge); 
    }

    while (!E_.empty()) {
        auto e = *E_.begin();  
        E_.erase(E_.begin());  

        if (V.find(e.first) == V.end() && V.find(e.second) == V.end()) {
            C.push_back(e.first);
            C.push_back(e.second);
            V.insert(e.first);
            V.insert(e.second);
        }
    }
    return C;
}

void show(const char* outputFilename){
    std::string command = "xdg-open ";
    command += outputFilename;
    system(command.c_str());
}