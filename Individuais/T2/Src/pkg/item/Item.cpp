#include "Item.hpp"

Item :: Item(int key) {
  key_ = key;
  index_ = -1;
  available_ = false;
  on_stack_ = false;
  low_v_ = 0;
}

int Item :: get_key() { return key_ ; }

int Item :: get_index() { return index_ ; }

void Item :: set_index(int index) { index_ = index ; }

int Item :: get_low_v() { return low_v_ ; }

void Item :: set_low_v(int low_v) { low_v_ = low_v ; }

bool Item :: is_available() { return available_; }

void Item :: set_availability(bool available) { available_ = available; }

void Item :: set_on_stack(bool on_stack) { on_stack_ = on_stack; }

bool Item :: is_on_stack() { return on_stack_; }

void Item :: add_connection(Item *item) {connections_.emplace_back(item); }

std::vector<Item*> Item :: get_connections() {return connections_; }

std::string Item :: parse_string() {
  return std::to_string(key_);
}


