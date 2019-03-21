#ifndef _PANTHER_MIDDLEWARE_
#define _PANTHER_MIDDLEWARE_

#include <memory>
#include "Response.hpp"

namespace PantherExpress {
  class Middleware {
    public:
      virtual int validate(std::shared_ptr<PantherExpress::Response> res) = 0;
  };
}

#endif
