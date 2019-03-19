#ifndef _PANTHER_HANDLERMAP_
#define _PANTHER_HANDLERMAP_

#include <memory>
#include "Controller.hpp"

namespace PantherExpress {
  class HandlerMap {
    private:
      std::string method;
      std::string path;
      std::shared_ptr<PantherExpress::Controller> controller;

    public:
      HandlerMap(std::string &method, std::string &path, std::shared_ptr<PantherExpress::Controller> controller);
  };
}

#endif
