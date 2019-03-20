#ifndef _PANTHER_RESPONSE_
#define _PANTHER_RESPONSE_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <memory>
#include <map>

namespace PantherExpress {
  enum HTTP_STATUS { 
    OK=200, CREATED=201, NO_CONTENT=204,
    BAD_REQUEST=400, UNAUTHORIZED=401, NOT_FOUND=404, CONFLICT=409,
    NOT_MODIFIED=304,
    INTERNAT_SERVER_ERROR=501
  };

  class Response {
    private:
      std::map<std::string, std::string> headers;
      struct MHD_Response *response;
      struct MHD_Connection *connection;
      unsigned int statusCode;

    public:
      Response();
      int send(const std::string& body);
      Response* set(std::string key, std::string value);
      Response* status(HTTP_STATUS statusCode);

      void setConnection(struct MHD_Connection *connection);
      struct MHD_Connection* getConnection();
      void setHeaders();
  };
}

#endif

