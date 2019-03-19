#ifndef _PANTHER_APPLICATION_
#define _PANTHER_APPLICATION_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <memory>

#include "Controller.hpp"
#include "HandlerMap.hpp"

namespace PantherExpress {
  class Application {
    private:
      std::set<PantherExpress::HandlerMap> handlers;

      struct MHD_Connection *connection;
      struct MHD_Daemon *daemon;
      
      static int answer_to_connection(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *body,
        size_t *body_size,
        void **con_cls);

    public:
      int listen(int port);
      void setConnection(struct MHD_Connection *connection);
      struct MHD_Connection* getConnection();
      
      //void get(std::string &path, std::shared_ptr<PantherExpress::Controller> controller);
  };
}

#endif
