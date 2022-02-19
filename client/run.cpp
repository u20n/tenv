#include <tree.hpp>
#include <strops.hpp>
#include <crypt++.hpp>
#include <server.hpp>
#include <node.hpp>
#include <iostream>
#include <string>
#include <map>

std::string akey = "Xv/azljSEXepU9ThHnfS6mKxLmiw0b90fMm6EsfXF5s=";

std::string hl(Conn* c) {
  return "dude idk";
}

int main(void) {
  std::cout << "initializing node...\n";
  /** init */
  std::map<std::string, Tree> local_forest;
  std::string tree_trip = gen_trip("seed");
  local_forest[tree_trip] = Tree("client/chains/"+tree_trip);
  Tree& local_tree = local_forest[tree_trip];
  user local_user;
  local_tree.set_pow_req(3);
  Server local_server(local_tree, akey, local_user);
  
  /** message */
  std::ifstream art_ifs("ascii.txt");
  std::stringstream art_buffer;
  art_buffer << art_ifs.rdbuf();
  json test_json;
  test_json["c"] = art_buffer.str();

  /** network */
  local_server.send_message(local_user, test_json, 'c');
  Node local_node(
      5, // queue
      1338, // port
      local_forest, // cm
      30000, // timeout
      &hl, // handling logic
      [](std::string s) -> bool {return true;} // watch dog
  );
  local_node.Contact(tree_trip, 1, "127.0.0.1", 1337);
}
