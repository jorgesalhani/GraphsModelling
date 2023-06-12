#ifndef _ITEM_H
  #define _ITEM_H

  #include <iostream>
  #include <vector>
  #include <string>


  class Item {
    public:
      Item(int key);
            
      int get_key();
      int get_index();
      bool is_available();
      void set_availability(bool available);
      void set_index(int index);
      int get_low_v();
      void set_low_v(int low_v);
      void set_on_stack(bool on_stack);
      bool is_on_stack();
      void add_connection(Item *item);
      std::vector<Item*> get_connections();
      std::string parse_string();

    private:
      int key_;
      int index_;
      bool on_stack_;
      bool available_;
      int low_v_;
      std::vector<Item*> connections_;
  };

#endif