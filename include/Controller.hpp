#ifndef _PANTHER_CONTROLLER_
#define _PANTHER_CONTROLLER_

#include <memory>
#include "Response.hpp"

namespace PantherExpress {
  class Controller {
    public:
      virtual int handler(std::shared_ptr<PantherExpress::Response> res) = 0;
  };
}

#endif
