#include <tree.hpp>
#include <strops.hpp>
#include <crypt++.hpp>
#include <server.hpp>
#include <node.hpp>

#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
/**
 *
 * This is kinda cursed;
 * host needs to have an entire root server, add the client's user to that server, ????
*/
void run_server(Tree lt, std::string k) {
  user local_user;
  Server local_server(lt, k, local_user);
  branch rb = local_server.get_root_branch();
  std::cout << rb.messages.back().data << '\n';
}

/** yucky foward declare so rs can ref it */
std::map<std::string, Tree> local_forest;

std::string rs(Conn* c) {
  
}

int main() {
  std::cout << "> Generating Tree\n";
  
  /** generate fresh tree */
  std::string tree_trip = gen_trip("seed");
  std::cout << "> Tree Trip: " << tree_trip << '\n';
  /** add client member */
  member cm = create_member(

  /** append tree to forest */
  local_forest[tree_trip] = Tree("host/chains/"+tree_trip);
  Tree& local_tree = local_forest[tree_trip];
  
  /** using placeholder PoW */
  local_tree.set_pow_req(3);
  
  /** server/leaf key */
  std::string key = "Xv/azljSEXepU9ThHnfS6mKxLmiw0b90fMm6EsfXF5s=";
  
  /** node creation */
  std::cout << "> Initializing Node...\n";
  Node local_node(
      (short unsigned)5, 
      (short unsigned)1337,
      local_forest,
      (unsigned)30000,
      &rs,
      [] (std::string) -> bool {return true;}
      );
  
  local_node.Open();
  local_node.Lazy(true, false);
  std::this_thread::sleep_for(std::chrono::seconds(5));

  run_server(local_tree, key);
  return 0;
}
