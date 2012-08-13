
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>

struct VertexProperty {
    int index;
};

int main(int,char*[]) {
    using namespace std;
    using namespace boost;

    typedef adjacency_list<    vecS,               // out-edge storage
                               vecS,            // vertex set storage
                               directedS,  // directed tag
                               no_property, //VertexProperty,     // vertex properties
                               no_property,           // edge properties
                               no_property,     // graph-properties 
                               listS            // edge storage
                               > Graph;
                               
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    //typedef pair<int, int> Pair;


    //Pair edges[6] = { Pair(0,1), Pair(2,4), Pair(2,5),
    //                  Pair(0,3), Pair(1,4), Pair(4,3) };
    Graph G(6); //, edges, edges + 6);
    add_edge( 0,1,G);
    add_edge( 2,4,G);
    add_edge( 2,5,G);
    add_edge( 0,3,G);
    add_edge( 1,4,G);
    add_edge( 4,3,G);
    
    typedef vector< Vertex > container;
    container c;
    topological_sort(G, back_inserter(c));

    cout << "A topological ordering: ";
    for ( container::reverse_iterator ii=c.rbegin(); ii!=c.rend(); ++ii)
    cout << (*ii) << " ";
    cout << endl;
    
    return 0;
}
