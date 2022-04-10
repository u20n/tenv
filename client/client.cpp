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

}

int main(void) {
  std::cout << "> Forming Tree Alias...\n";
  /** (reserve) aliased tree */
  std::map<std::string, Tree> local_forest;
  std::string tree_trip = gen_trip("seed");
  local_forest[tree_trip] = Tree("client/chains/"+tree_trip);
  
  /** register (self) user */
  Tree& local_tree = local_forest[tree_trip];
  user local_user;
  local_tree.set_pow_req(3);
  Server local_server(local_tree, akey, local_user);
  
  /** message */
  json test_json;
  test_json["c"] = "don\'t sweat the tech";

  std::cout << "> Applying Data...\n";
  std::string nmh = local_server.send_message(local_user, test_json, 'c');
  if (nmh.empty()) {
      std::cout << "! Could Not Apply Data\n";
  } else {
    std::cout << "% New Message (self) Hash: " << nmh << '\n'; 
  }
   
  /** network */
  Node local_node(
      (short unsigned) 5, // queue
      (short unsigned) 1338, // port
      local_forest, // cm
      (unsigned) 30000, // timeout
      &hl, // handling logic
      [] (std::string) -> bool {return true;}
  );
  local_node.Contact(tree_trip, 1, "127.0.0.1", 1337);
}
