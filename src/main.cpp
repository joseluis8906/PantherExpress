#include "Application.hpp"
#include <iostream>

int main(int argc, char** argv) {
  PantherExpress::Application app = PantherExpress::Application();
  return app.listen(8888);
}
