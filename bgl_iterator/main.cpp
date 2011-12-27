
// example for using iterators to traverse the edges of a face in a 
// planar BGL graph.
// AW 2011 December

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

typedef boost::graph_traits< Graph >::vertex_descriptor    Vertex;

// see http://www.boost.org/doc/libs/1_48_0/libs/iterator/doc/iterator_facade.htm
class edge_iterator : public boost::iterator_facade<
               edge_iterator,
               Edge,
               boost::forward_traversal_tag> 
{
public:
    //typedef typename boost::graph_traits< BGLGraph >::edge_descriptor BGLEdge;
    explicit edge_iterator(Graph& g, Edge e): m_edge(e), m_g(g), m_inc(false)  {}
protected:
    friend class boost::iterator_core_access;
    void increment() { 
        m_edge = ( m_g[m_edge].next ); 
        if(!m_inc) m_inc = true;
    }
    bool equal( edge_iterator const& other) const {
        return (((m_edge) == (other.m_edge)) && m_inc);
    }
    Edge& dereference() const { 
        Edge cpy(m_edge);
        Edge&  e = cpy; 
        return e; 
    } 
    
    Edge m_edge;
    Graph& m_g;
    bool m_inc;
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
    // direct traversal of graph
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
    // do-while with iterators
    //typedef edge_iterator<Graph> eitr;
    
    edge_iterator current_itr(g,e1);
    edge_iterator end_itr = current_itr;
    std::cout << "2nd way:\n";
    do {
        std::cout << *current_itr++ << "\n";
    } while (current_itr!=end_itr);
    // output:
    // 2nd way:
    // (0,1)
    // (1,2)
    // (2,3)
    // (3,0)
    
    // 3rd way to iterate around face of graph
    // for_each and iterators
    edge_iterator begin(g,e1);
    edge_iterator end(g,e1);    
    std::cout << "3rd way:\n";
    BOOST_FOREACH(Edge e, std::make_pair(begin,end)) {
        std::cout << e << "\n";
    }
    
    return 0;
}
