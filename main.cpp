/** core */
#include <tree.hpp>
#include <strops.hpp>
#include <crypt.hpp>
#include <node.hpp>

/** proto */
#include <hclc.hpp>

/** std */
#include <iostream>
#include <string>
#include <map>

/** right now we're just going to test r/w, no complicated standard (concord relay chat) */
namespace crc {
struct user {
  std::string nick;
  std::string trip;
};

struct message {
  std::string trip;
  std::string content;
  struct _t {
    unsigned long long declared;
    unsigned long long recieved;
    unsigned long long difference;
  } time;  
};

struct brain {
  private:
    std::vector<Node*> av; // Active (Node) Vector
    std::string graphId = gen::trip("seed"); 
    Tree unifiedT;
    std::map<std::string, Tree> Forest{{graphId, unifiedT}};
  protected:
    void logic() { // user-interactive part
      std::cout << "New blocks: \n" << "********" << '\n';
    }
    void update(Node* n) {
      try {
        if (n->Connections.empty()){return;}
        for (auto& c: n->Connections) {
          if(!c.Flags.GetFlag(ConnCtx::ACTIVE)) {
            hclc hcpy(graphId, -1);
            hcpy.ConnHandle(&c);
            this->logic();
          }
        }
      } catch(std::exception& e) {
        std::cout << "[!] " << e.what() << '\n';
        // ...
      }
   }
  public:
    void add_node(unsigned int port) {
      Node n(
          port,
          Forest, 
          [] (std::string) -> bool {return true;}
      );
      n.Lazy(true, false);
      n.Open();
      this->av.push_back(&n);
    }
    void remove_node(int index) {
      this->av.at(index)->Close();
    } 
    void contact(std::string ip, unsigned int port) {
      /** pull first available node */
      Node* me = av.front();
      std::cout << "actually contacting...\n";
      me->Contact(ip, port);
      std::cout << "updating...\n";
      /** do compare */
      this->update(me);
    };
    brain(std::string dir) {
      this->unifiedT.load(dir);
    };
  };
};

int main(void) {
  std::cout << "starting\n";
  crc::brain one("./achain/"), two("./bchain/");
  one.add_node(1337);
  two.add_node(1338);
  std::cout << "thing 1 contacting thing 2 ...\n";
  one.contact("127.0.0.1", 1338); 
  std::cout << "done\n";
  return 0;
};
