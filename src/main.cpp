#include "Application.hpp"
#include "ControllerFactory.hpp"
#include "Controller.hpp"
#include <iostream>

class HelloGetController: public PantherExpress::Controller {
  public:
  int handler(std::shared_ptr<PantherExpress::Response> res) {
    return res->send("Hello GET controller");
  }
};

class HelloPostController: public PantherExpress::Controller {
  public:
  int handler(std::shared_ptr<PantherExpress::Response> res) {
    return res->send("Hello POST controller");
  }
};

class HelloPutController: public PantherExpress::Controller {
  public:
  int handler(std::shared_ptr<PantherExpress::Response> res) {
    return res->send("Hello PUT controller");
  }
};

class HelloDeleteController: public PantherExpress::Controller {
  public:
  int handler(std::shared_ptr<PantherExpress::Response> res) {
    return res->send("Hello DELETE controller");
  }
};

class HelloControllerFactory: public PantherExpress::ControllerFactory {
  public:
  std::shared_ptr<PantherExpress::Controller> makeGetController() {
    return std::shared_ptr<HelloGetController>(new HelloGetController());
  }
  
  std::shared_ptr<PantherExpress::Controller> makePostController() {
    return std::shared_ptr<HelloPostController>(new HelloPostController());
  }
  
  std::shared_ptr<PantherExpress::Controller> makePutController() {
    return std::shared_ptr<HelloPutController>(new HelloPutController());
  }
  
  std::shared_ptr<PantherExpress::Controller> makeDeleteController() {
    return std::shared_ptr<HelloDeleteController>(new HelloDeleteController());
  }
};

int main(int argc, char** argv) {
  PantherExpress::Application app = PantherExpress::Application();
  std::string endPoint = "/hello";
  app.All(endPoint, std::shared_ptr<HelloControllerFactory>(new HelloControllerFactory()));
  return app.listen(8888);
}
