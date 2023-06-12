#ifndef _GRAPH_H
  #define _GRAPH_H

  #include <vector>
  #include <stack>
  #include <iostream>
  #include "../item/Item.hpp"

  class Graph {

    public:
      Graph();
      Graph(int total_nodes, int total_edges);

      ~Graph();

      void add_edge(int from, int to);
      void print();
      void scc_tarjan_alg();
    
    private:
      int total_nodes_;
      int total_edges_;
      int index_;

      std::vector<Item*> adjacency_list_;
      std::stack<Item*> stack_;
      std::vector<Item*> sccomponents_;

      void scc_tarjan_alg_aux(Item* item);
  };

#endif