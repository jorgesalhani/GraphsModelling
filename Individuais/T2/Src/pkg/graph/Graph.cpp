#include "Graph.hpp"

using namespace std;

Graph :: Graph(int nodes, int edges) {
  total_nodes_ = nodes;
  total_edges_ = edges;
  timestamp_ = 0;
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

void Graph :: update_scc_vector_(Item* v) {
  vector<int> scc;
  int w_key = -1;
  while (w_key != v->get_key()) {
    Item* w = stack_.top();
    scc.push_back(w->get_key());
    stack_.pop();
    w->set_on_stack(false);
    w_key = w->get_key();
  }
  std::sort(scc.begin(), scc.end());
  sccomponents_.push_back(scc);
  total_scc_++;
}

void Graph :: scc_tarjan_alg_aux_(Item* v) {

  // Inicializacao do tempo de descoberta e adicao na pilha de DFS
  v->set_timestamp(timestamp_);
  v->set_low_v(timestamp_);

  stack_.push(v);
  v->set_on_stack(true);
  timestamp_++;
  
  int min_low;

  // Para cada conexao w do vertice v,
  // - caso -1:   descobrir e obter minimo entre: low_[v] low_[w]
  // - contrario: caso na pilha, obter minimo entre: low_[v] e d[v]
  for (Item* w : v->get_connections()) {
    if (w->get_timestamp() == -1) {
      scc_tarjan_alg_aux_(w);
      min_low = std::min(v->get_low_v(), w->get_low_v()); 
      v->set_low_v(min_low);
    } else

    if (w->is_on_stack()) {
      min_low = std::min(v->get_low_v(), w->get_timestamp());
      v->set_low_v(min_low);
    }
  }

  // Se low_[v] == d[v], encontramos uma componente (scc)
  if (v->get_low_v() == v->get_timestamp()) {
    update_scc_vector_(v);
  } 
}

void Graph :: scc_tarjan_alg() {
  
  // Para cada vertice do grafo (presente na lista de adjacencia)
  // - importante para pegar vertices desconexos
  for (Item* v : adjacency_list_) {
    if (v->get_timestamp() == -1) {
      scc_tarjan_alg_aux_(v);
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