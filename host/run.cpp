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

void run_server(Tree lt, std::string k) {
  std::ifstream art_ifs("ascii.txt");
  std::stringstream ab;
  user local_user;
  Server local_server(lt, k, local_user);
  branch rb = local_server.get_root_branch();
  std::cout << rb.messages.back().data << '\n';
}

bool wd(std::string ip) {
  std::cout << "IP: " << ip << '\n';
  return true;
}

int main() {
  std::cout << "initializing node...\n";
  std::map<std::string, Tree> local_forest;
  std::string tree_trip = gen_trip("seed");
  std::cout << "tree_trip: " << tree_trip << '\n';
  local_forest[tree_trip] = Tree("host/chains/"+tree_trip);
  Tree& local_tree = local_forest[tree_trip];
  local_tree.set_pow_req(3);

  std::string key = "Xv/azljSEXepU9ThHnfS6mKxLmiw0b90fMm6EsfXF5s=";
   
  Node local_node(5, 1337, local_forest, 30000, &wd);
  
  local_node.Open();
  local_node.Is_Lazy(true, false);
  std::this_thread::sleep_for(std::chrono::seconds(5));

  run_server(local_tree, key);
  return 0;
}
