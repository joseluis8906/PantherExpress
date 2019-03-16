#include "Application.hpp"
#include <iostream>

int main(int argc, char** argv) {
  PantherExpress::Application app = PantherExpress::Application();
  app.get("/hello", [](void){
      std::cout << "callback" << std::endl;
  });
  return app.listen(8888);
}
