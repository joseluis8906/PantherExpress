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
#include <vector>
#include <memory>

#include "Controller.hpp"
#include "Router.hpp"

namespace PantherExpress {
  class Application {
    private:
      std::vector<std::shared_ptr<PantherExpress::Router>> getRouters;
      std::vector<std::shared_ptr<PantherExpress::Router>> postRouters;
      std::vector<std::shared_ptr<PantherExpress::Router>> putRouters;
      std::vector<std::shared_ptr<PantherExpress::Router>> deleteRouters;

      struct MHD_Connection *connection;
      struct MHD_Daemon *daemon;
      
      static int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *body, size_t *body_size, void **con_cls);

    public:
      Application();

      int listen(int port);
      void setConnection(struct MHD_Connection *connection);
      struct MHD_Connection* getConnection();
      
      int routeResponse(std::string method, std::string path, std::shared_ptr<PantherExpress::Response> res);
      
      void Get(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      void Get(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::vector<std::shared_ptr<PantherExpress::Middleware>> middlewares);
      /*void Post(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      void Post(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares);
      void Put(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      void Put(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares);
      void Delete(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      void Delete(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares);*/
      void All(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory);
      //void All(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares);
  };
}

#endif
