#include "Application.hpp"
#include "ControllerFactory.hpp"
#include "Controller.hpp"
#include "Middleware.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace PantherExpress;
using namespace std;

class SumMiddleware: public Middleware {
  public:
    int validate(shared_ptr<Response> res) {
      if ( 2 + 2 == 2 ) {
        return res->status(HTTP_STATUS::CONFLICT)->send("2 + 2 is diferent to 2.");
      }
      return 0;
    }
};

class DiffMiddleware: public Middleware {
  public:
    int validate(shared_ptr<Response> res) {
      if ( 2 - 2 == 2 ) {
        return res->status(HTTP_STATUS::CONFLICT)->send("2 - 2 diferent to 2.");
      }
      return 0;
    }
};

class HelloGetController: public Controller {
  public:
    int handler(shared_ptr<Response> res) {
      return res->send("Hello GET controller");
    }
};

class HelloControllerFactory: public ControllerFactory {
  public:
    shared_ptr<Controller> makeGetController() {
      return shared_ptr<HelloGetController>(new HelloGetController());
    }
    
    shared_ptr<Controller> makePostController() {
      return NULL;
    }
    
    shared_ptr<Controller> makePutController() {
      return NULL;
    }
    
    shared_ptr<Controller> makeDeleteController() {
      return NULL;
    }
};

int main(int argc, char** argv) {
  shared_ptr<Application> app = shared_ptr<Application>(new Application());
  string endPoint = "/hello";
  vector<shared_ptr<Middleware>> helloMiddlewares;
  helloMiddlewares.push_back(shared_ptr<Middleware>(new SumMiddleware()));
  helloMiddlewares.push_back(shared_ptr<Middleware>(new DiffMiddleware()));
  app->Get(endPoint, shared_ptr<HelloControllerFactory>(new HelloControllerFactory()), helloMiddlewares);
  return app->listen(8888);
}
