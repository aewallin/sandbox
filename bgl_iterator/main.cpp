
#include <iostream>
#include <sstream>
#include <string>

#include <boost/foreach.hpp> 
#include <boost/graph/adjacency_list.hpp>
#include <boost/iterator/iterator_facade.hpp>

#define OUT_EDGE boost::listS
#define VERTEX_LIST boost::vecS

typedef boost::adjacency_list_traits<OUT_EDGE, 
                                     VERTEX_LIST, 
                                     boost::bidirectionalS, 
                                     boost::listS >::edge_descriptor Edge;
                                     
struct EdgeProperty {
    Edge next;
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
typedef boost::graph_traits< Graph >::vertex_descriptor    Vertex;

// see http://www.boost.org/doc/libs/1_48_0/libs/iterator/doc/iterator_facade.htm
class edge_iterator : public boost::iterator_facade<
               edge_iterator,
               Edge,
               boost::forward_traversal_tag> 
{
public:
    edge_iterator(): m_edge( 0 ) {} // is this constructor ever used? leaves m_g uninitialized!
    
    explicit edge_iterator(Graph* g, Edge* e): m_edge(e), m_g(g)  {}
private:
    friend class boost::iterator_core_access;
    void increment() { m_edge = &( (*m_g)[*m_edge].next ); } 
    bool equal( edge_iterator const& other) const {
        return *(this->m_edge) == *(other.m_edge);
    }
    Edge& dereference() const { return *m_edge; } 
    
    Edge* m_edge;
    Graph* m_g;
}; 

int main(int,char*[]) {
    Graph g;

    Vertex v1 = boost::add_vertex(g);
    Vertex v2 = boost::add_vertex(g);
    Vertex v3 = boost::add_vertex(g);
    Vertex v4 = boost::add_vertex(g);
    bool tmp;
    Edge e1,e2,e3,e4;
    boost::tie(e1, tmp) = boost::add_edge(v1,v2,g);
    boost::tie(e2, tmp) = boost::add_edge(v2,v3,g);
    boost::tie(e3, tmp) = boost::add_edge(v3,v4,g);
    boost::tie(e4, tmp) = boost::add_edge(v4,v1,g);
    
    // hook up the edges to form a face:
    g[e1].next = e2;
    g[e2].next = e3;
    g[e3].next = e4;
    g[e4].next = e1;
    
    // 1st way to iterate around face of graph
    Edge current=e1;
    Edge start=current;
    std::cout << "1st way:\n";
    do {
        std::cout << current << "\n";
        current = g[current].next;
    } while (current!=start);
    // output:
    // 1st way:
    // (0,1)
    // (1,2)
    // (2,3)
    // (3,0)

    
    // 2nd way to iterate around face of graph
    edge_iterator begin(&g,&e1);
    // edge_iterator end(&g,&e1); // this gives no output at all!
    // edge_iterator end(&g,&e2); // this gives (0,1)
    // edge_iterator end(&g,&e4); // this gives (0,1) (1,2) (2,3)   (but NOT (3,0) !)
    Edge e1_cpy = e1;
    edge_iterator end(&g,&e1_cpy); // this gives no output at all!
    
    std::pair<edge_iterator,edge_iterator> face_edges(begin,end);
    std::cout << "2nd way:\n";
    BOOST_FOREACH(Edge e, face_edges) {
        std::cout << e << "\n";
    }
    
    std::cout << " num_verts= " << boost::num_vertices(g) << std::endl;
    std::cout << " num_edges= " << boost::num_edges(g) << std::endl;
    return 0;
}
