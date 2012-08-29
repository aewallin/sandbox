
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <fstream> // std::filebuf

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/graphviz.hpp>

int main(int,char*[]) {
    using namespace std;
    using namespace boost;

    typedef adjacency_list<    vecS,            // out-edge storage
                               vecS,            // vertex set storage
                               directedS,       // directed tag
                               no_property,     // vertex properties
                               no_property,     // edge properties
                               no_property,     // graph-properties 
                               listS            // edge storage
                               > Graph;
                               
    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    Graph G(6);
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
    // output:
    // A topological ordering: 2 5 0 1 4 3 
    filebuf fb;
    fb.open ("test.dot",ios::out);
    ostream out(&fb);
    write_graphviz( out, G);
    return 0;
}
