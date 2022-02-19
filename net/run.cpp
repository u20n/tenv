#include <uttu.hpp>
#include <iostream>

void new_peer(std::shared_ptr<Peer> p) {
  std::cout << "got new peer\n";
  
  p->Key_Exchange();
  p->Write("hi", 3000);
  std::cout << p->Read(3000) << '\n';
  
  std::cout << "closing peer\n";
  p->Close();
}

void contact(std::shared_ptr<Peer> p) {
  p->Key_Exchange();
  std::cout << p->Read(3000) << '\n';
  p->Write("hello!", 3000);
  p->Close();
}

int main() {
  Session S = Create(1337, 5, 3000);

  S.Criteria([](std::string){return true;});
  S.Lazy(new_peer, false);
  S.Open();

  Session C = Create(1338, 5, 3000);
  contact(C.Connect("127.0.0.1:1337"));
}
