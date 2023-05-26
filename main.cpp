#include "Graph.hpp"
#include <iterator>


int main(int argc, char **argv)
{
	Graph my_graph(argv[1]);

    auto vertex_cover_approx = my_graph.approx_min_cover();
    auto vertex_cover_brute = my_graph.brute_force_min_cover();

    my_graph.render_output_image("output.png",vertex_cover_brute);

    std::cout<<std::endl;
    std::cout<<"գագաթային ծածկույթի թիվը ըստ բոլոր ենթաբազմությունները դիտարկող ալգորիթմի "<< vertex_cover_brute.size() << " { "; 
    std::copy(vertex_cover_brute.begin(), vertex_cover_brute.end(),std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"}"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"գագաթային ծածկույթի թիվը ըստ մոտարկող ալգորիթմի "<< vertex_cover_approx.size() << " { "; 
    std::copy(vertex_cover_approx.begin(), vertex_cover_approx.end(),std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"}"<<std::endl;
    std::cout<<std::endl;
    return 0;
}