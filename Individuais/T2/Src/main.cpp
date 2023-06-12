#include <iostream>
#include "pkg/graph/Graph.hpp"
#include "pkg/item/Item.hpp"

int main() {
  int nodes, edges;

  std::cin >> nodes;
  std::cin >> edges;

  Graph graph(nodes, edges);
  for (int i = 0; i < edges; i++) {
    int from, to;

    std::cin >> from;
    std::cin >> to;

    graph.add_edge(from, to);
  }
    
  graph.print();
  std::cout << "\n";

  graph.scc_tarjan_alg();
  return 0;
}