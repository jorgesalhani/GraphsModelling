#include "Graph.hpp"

using namespace std;

Graph :: Graph(int nodes, int edges) {
  total_nodes_ = nodes;
  total_edges_ = edges;
  index_ = 0;
  total_scc_ = 0;
  for (int i = 0; i < total_nodes_; i++) {
    Item* item = new Item(i);
    adjacency_list_.emplace_back(item);
  }
}

Graph :: ~Graph() {
  for (int i = 0; i < total_nodes_; i++) {
    delete adjacency_list_[i];
  }
}

void Graph :: add_edge(int from, int to) {
  Item* item_to = adjacency_list_[to];
  adjacency_list_[from]->add_connection(item_to);
}

void Graph :: print() {
  for (int i = 0; i < total_nodes_; i++) {
    Item* item_head = adjacency_list_[i];
    cout << item_head->parse_string() << ": -> ";
    vector<Item*> connects = adjacency_list_[i]->get_connections();
    int node_degree = (int) connects.size();
    for (int j = 0; j < node_degree; j++) {
      cout << connects[j]->parse_string() << ", ";
    }
    cout << "\n";
  }
}

void Graph :: scc_tarjan_alg_aux(Item* v) {
  v->set_index(index_);
  v->set_low_v(index_);
  ++index_;

  stack_.push(v);
  v->set_on_stack(true);
  
  for (Item* w : v->get_connections()) {
    if (w->get_index() == -1) {
      scc_tarjan_alg_aux(w);
      v->set_low_v(std::min(v->get_low_v(), w->get_low_v()));
    } else

    if (w->is_on_stack()) {
      v->set_low_v(std::min(v->get_low_v(), w->get_index()));
    }
  }

  if (v->get_low_v() == v->get_index()) {
    vector<int> scc;
    while (true) {
      Item* w = stack_.top();
      scc.push_back(w->get_key());
      stack_.pop();
      w->set_on_stack(false);
      if (w == v) break;
    }
    std::sort(scc.begin(), scc.end());
    sccomponents_.push_back(scc);
    total_scc_++;
  } 
}

void Graph :: scc_tarjan_alg() {
  for (Item*& v : adjacency_list_) {
    if (v->get_index() == -1) {
      scc_tarjan_alg_aux(v);
    }
  }

  std::sort(sccomponents_.begin(), sccomponents_.end());
}

void Graph :: scc_print() {
  cout << total_scc_ << endl;
  for (vector<int> v : sccomponents_) {
    for (int v_id : v) {
      cout << v_id << " ";
    }
    cout << endl;
  }
}