
#include <iostream>
#include <sstream>
#include <string>

#include <boost/graph/adjacency_list.hpp>

struct EdgeProperty;

typedef boost::adjacency_list_traits<boost::listS, 
                                     boost::vecS, 
                                     boost::bidirectionalS, 
                                     boost::listS >::edge_descriptor Edge;

/// edge properties
struct EdgeProperty {
    Edge next;
};


typedef boost::adjacency_list< boost::listS,           // out-edge storage
                               boost::vecS,            // vertex set storage
                               boost::bidirectionalS,              // directed tag
                                                boost::no_property,      // vertex properties
                                                EdgeProperty,        // edge properties
                                                boost::no_property,       // graph-properties 
                                                boost::listS               // edge storage
                                                > MyGraph;
                                                

typedef boost::graph_traits< MyGraph >::vertex_descriptor    Vertex;



int main(int,char*[]) {
    
    MyGraph g;
    Vertex v1 = boost::add_vertex(g);
    Vertex v2 = boost::add_vertex(g);
    Vertex v3 = boost::add_vertex(g);
    bool tmp;
    Edge e1,e2;
    boost::tie(e1, tmp) = boost::add_edge(v1,v2,g);
    boost::tie(e2, tmp) = boost::add_edge(v2,v3,g);
    g[e1].next = e2;
    g[e2].next = e1;
    std::cout << e1 << " next= " << g[e1].next << std::endl;
    std::cout << e2 << " next= " << g[e2].next << std::endl;
    return 0;
}
