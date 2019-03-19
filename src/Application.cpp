#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Application.hpp"
#include "HandlerMap.hpp"

int PantherExpress::Application::listen(int port) {
  daemon = MHD_start_daemon(
    MHD_USE_THREAD_PER_CONNECTION,
    port,
    NULL,
    NULL,
    &PantherExpress::Application::answer_to_connection,
    this,
    MHD_OPTION_END);
  
  if (NULL == daemon) {
    std::cerr << "Error: was not possible to initiate a daemon" << std::endl;
    return 1;
  }
  
  std::cout << "Listen on port: " << port << std::endl;
  getchar ();

  MHD_stop_daemon (daemon);

  return 0;
}

int PantherExpress::Application::answer_to_connection(
  void *cls,
  struct MHD_Connection *connection,
  const char *url,
  const char *method_, 
  const char *version,
  const char *body,
  size_t *body_size, 
  void **con_cls) {

  PantherExpress::Application* app = (PantherExpress::Application*) cls;
  app->setConnection(connection);

  std::string method = (std::string) method_;
  std::unique_ptr<PantherExpress::Response> res = std::unique_ptr<PantherExpress::Response>(new PantherExpress::Response());
  res->setConnection(this->getConnection());

  return res->send("<html><body>PantherExpress Hello World!</body></html>");
}

void PantherExpress::Application::setConnection(struct MHD_Connection *connection) {
  this->connection = connection;
}

struct MHD_Connection* PantherExpress::Application::getConnection(){ 
  return this->connection;
}

