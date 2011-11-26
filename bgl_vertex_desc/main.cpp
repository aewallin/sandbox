
#include <iostream>
#include <sstream>
#include <string>

#include <boost/graph/adjacency_list.hpp>

#define OUT_EDGE boost::vecS
#define VERTEX_LIST boost::listS

typedef boost::adjacency_list_traits<OUT_EDGE, 
                                     VERTEX_LIST, 
                                     boost::bidirectionalS, 
                                     boost::listS >::edge_descriptor Edge;
                                     
// edge properties
struct EdgeProperty {
    EdgeProperty() {
        space_eater.resize(100);
    }
    Edge twin;
    std::vector<double> space_eater;
};


typedef boost::adjacency_list< OUT_EDGE,               // out-edge storage
                               VERTEX_LIST,            // vertex set storage
                               boost::bidirectionalS,  // directed tag
                               boost::no_property,     // vertex properties
                               EdgeProperty,           // edge properties
                               boost::no_property,     // graph-properties 
                               boost::listS            // edge storage
                               > Graph;
                                                

typedef boost::graph_traits< Graph >::edge_descriptor      Edge;
typedef boost::graph_traits< Graph >::edge_iterator        EdgeItr;
typedef boost::graph_traits< Graph >::vertex_descriptor    Vertex;

bool check_edge(Edge e, Graph& g) {
    Vertex src = boost::source(e,g); //g.source(e);
    Vertex trg = boost::target(e,g); //g.target(e);
    Edge twine = g[e].twin;
    Vertex tw_src = boost::source(twine,g);
    Vertex tw_trg = boost::target(twine,g);
    if ( !((src==tw_trg) && (trg==tw_src)) ) {
        std::cout << " check_edge() ERROR: \n";
        std::cout << "      edge: " << e << "\n";
        std::cout << "      twin: " << twine << "\n";
        std::cout << "      edge: " << src << " - " << trg << "\n";
        std::cout << "      twin: " << tw_src << " - " << tw_trg << "\n";

    }
    return ( (src==tw_trg) && (trg==tw_src) );
}

void check_all_edges(Graph& g) {
    EdgeItr it, end;
    boost::tie( it, end) = boost::edges(g);
    for( ; it!=end ; it++) {
        check_edge(*it, g);
    }
}

int main(int,char*[]) {
    Graph g;
    int Nmax=1000;
    for (int m=0;m<Nmax;m++) {
        Vertex v1 = boost::add_vertex(g);
        Vertex v2 = boost::add_vertex(g);
        bool tmp;
        Edge e1,e2;
        boost::tie(e1, tmp) = boost::add_edge(v1,v2,g);
        boost::tie(e2, tmp) = boost::add_edge(v2,v1,g);
        g[e1].twin = e2;
        g[e2].twin = e1;
        check_edge(e1,g);
        check_edge(e2,g);
    }
    check_all_edges(g);
    
    std::cout << " num_verts= " << boost::num_vertices(g) << std::endl;
    std::cout << " num_edges= " << boost::num_edges(g) << std::endl;
    return 0;
}
