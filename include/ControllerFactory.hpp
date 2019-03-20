#ifndef _PANTHER_CONTROLLERFACTORY_
#define _PANTHER_CONTROLLERFACTORY_

#include <memory>
#include "Controller.hpp"

namespace PantherExpress {
  class ControllerFactory {
    public:
      virtual std::shared_ptr<PantherExpress::Controller> makeGetController() = 0;
      virtual std::shared_ptr<PantherExpress::Controller> makePostController() = 0;
      virtual std::shared_ptr<PantherExpress::Controller> makePutController() = 0;
      virtual std::shared_ptr<PantherExpress::Controller> makeDeleteController() = 0;
  };
}

#endif
