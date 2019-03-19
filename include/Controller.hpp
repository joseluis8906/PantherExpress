#ifndef _PANTHER_CONTROLLER_
#define _PANTHER_CONTROLLER_

#include <memory>
#include "Response.hpp"

namespace PantherExpress {
  class Controller {
    void handler(std::shared_ptr<PantherExpress::Response> res);
  };
}

#endif
