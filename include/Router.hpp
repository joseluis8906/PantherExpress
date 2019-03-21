#ifndef _PANTHER_ROUTER_
#define _PANTHER_ROUTER_

#include <memory>
#include <vector>
#include "ControllerFactory.hpp"
#include "Middleware.hpp"

namespace PantherExpress {
  class Router {
    public:
      std::string method;
      std::string path;
      std::vector<std::shared_ptr<PantherExpress::Middleware>> middlewares;
      std::shared_ptr<PantherExpress::ControllerFactory> factory;

      Router(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      Router(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::vector<std::shared_ptr<PantherExpress::Middleware>> middlewares);
      int handler(std::shared_ptr<PantherExpress::Response> res);
  };
}

#endif
