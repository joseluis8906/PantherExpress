#include "Router.hpp"

PantherExpress::Router::Router(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->method = method;
  this->path = path;
  this->factory = factory;
}

PantherExpress::Router::Router(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::vector<std::shared_ptr<PantherExpress::Middleware>> middlewares) {
  this->method = method;
  this->path = path;
  this->factory = factory;
  this->middlewares = middlewares;
}

int PantherExpress::Router::handler(std::shared_ptr<PantherExpress::Response> res) {
  if (this->middlewares.size() != 0) {
    for (std::vector<std::shared_ptr<PantherExpress::Middleware>>::iterator it = this->middlewares.begin(); it != this->middlewares.end(); ++it){      
      std::shared_ptr<PantherExpress::Middleware> middleware = *it;
      int ret = middleware->validate(res);
      if (ret) {
        return ret;
      }
    }
  }

  if (this->method == "GET") {
    return this->factory->makeGetController()->handler(res);
  }
  
  if (this->method == "POST") {
    return this->factory->makePostController()->handler(res);
  }
  
  if (this->method == "PUT") {
    return this->factory->makePutController()->handler(res);
  }
  
  if (this->method == "DELETE") {
    return this->factory->makeDeleteController()->handler(res);
  }

  return res->status(PantherExpress::HTTP_STATUS::NOT_FOUND)->send("Not Found.");
}
