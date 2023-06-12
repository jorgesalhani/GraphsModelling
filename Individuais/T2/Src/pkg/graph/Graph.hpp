#ifndef _GRAPH_H
  #define _GRAPH_H

  #include <vector>
  #include <stack>
  #include <iostream>
  #include <algorithm> 
  #include "../item/Item.hpp"

  class Graph {

    public:
      Graph();
      Graph(int total_nodes, int total_edges);

      ~Graph();

      void add_edge(int from, int to);
      void print();
      void scc_tarjan_alg();
      void scc_print();
    
    private:
      int total_nodes_;
      int total_edges_;
      int timestamp_;
      int total_scc_;

      std::vector<Item*> adjacency_list_;
      std::stack<Item*> stack_;
      std::vector<std::vector<int>> sccomponents_;

      void scc_tarjan_alg_aux_(Item* item);
      void update_scc_vector_(Item* item);
  };

#endif