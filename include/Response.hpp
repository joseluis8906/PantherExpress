#ifndef _PANTHER_RESPONSE_
#define _PANTHER_RESPONSE_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <memory>

namespace PantherExpress {
  class Response {
    private:
      struct MHD_Response *response;
      struct MHD_Connection *connection;

    public:
      int send(const std::string& body);

      void setConnection(struct MHD_Connection *connection);
      struct MHD_Connection* getConnection();
  };
}

#endif

