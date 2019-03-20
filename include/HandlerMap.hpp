#ifndef _PANTHER_HANDLERMAP_
#define _PANTHER_HANDLERMAP_

#include <memory>
#include "ControllerFactory.hpp"

namespace PantherExpress {
  class HandlerMap {
    public:
      std::string method;
      std::string path;
      std::shared_ptr<PantherExpress::ControllerFactory> factory;

      HandlerMap(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
  };
}

#endif
