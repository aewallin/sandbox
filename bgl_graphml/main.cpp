#include <iostream>
#include <string>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>

struct Node
{
  Node () {};
  Node (std::string ip_) : ip(ip_) {};
  std::string ip;
};

int main (int argc, char *argv[])
{
  typedef boost::adjacency_list < boost::multisetS, boost::vecS, boost::bidirectionalS, Node > graph_t;
  typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;

  graph_t m_tg;

  Node u("10.10.10.1");
  Node v("10.10.10.2");

  vertex_t u1 = boost::add_vertex(u, m_tg);
  vertex_t v1 = boost::add_vertex(v, m_tg);
  boost::add_edge(u1, v1, m_tg);

  boost::dynamic_properties dp;
  dp.property("ip", boost::get(&Node::ip, m_tg));
  boost::write_graphml(std::cout, m_tg, dp, true);
}
