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
  daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port, NULL, NULL, &PantherExpress::Application::answer_to_connection, this, MHD_OPTION_END);
  
  if (NULL == daemon) {
    std::cerr << "Error: was not possible to initiate a daemon" << std::endl;
    return 1;
  }
  
  std::cout << "Listen on port: " << port << std::endl;
  getchar ();

  MHD_stop_daemon (daemon);

  return 0;
}

int PantherExpress::Application::answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method_, const char *version, const char *body, size_t *body_size, void **con_cls) {
  std::string method = (std::string) method_;
  std::string path = (std::string) url;

  PantherExpress::Application* app = (PantherExpress::Application*) cls;
  app->setConnection(connection);
  
  std::shared_ptr<PantherExpress::Response> res = std::unique_ptr<PantherExpress::Response>(new PantherExpress::Response());
  res->setConnection(connection);

  return app->routeResponse(method, path, res);
}

void PantherExpress::Application::setConnection(struct MHD_Connection *connection) {
  this->connection = connection;
}

struct MHD_Connection* PantherExpress::Application::getConnection(){ 
  return this->connection;
}

int PantherExpress::Application::routeResponse(std::string method, std::string path, std::shared_ptr<PantherExpress::Response> res){
  if (method == "GET") {
    for (std::set<std::shared_ptr<PantherExpress::HandlerMap>>::iterator it = this->getHandlers.begin(); it != this->getHandlers.end(); ++it){
      std::shared_ptr<PantherExpress::HandlerMap> handler = *it;
      if (handler->path == path) {
        return handler->factory->makeGetController()->handler(res);
      }
    }
  }

  if (method == "POST") {
    for (std::set<std::shared_ptr<PantherExpress::HandlerMap>>::iterator it = this->postHandlers.begin(); it != this->postHandlers.end(); ++it){
      std::shared_ptr<PantherExpress::HandlerMap> handler = *it;
      if (handler->path == path) {
        return handler->factory->makePostController()->handler(res);
      }
    }
  }

  if (method == "PUT") {
    for (std::set<std::shared_ptr<PantherExpress::HandlerMap>>::iterator it = this->putHandlers.begin(); it != this->putHandlers.end(); ++it){
      std::shared_ptr<PantherExpress::HandlerMap> handler = *it;
      if (handler->path == path) {
        return handler->factory->makePutController()->handler(res);
      }
    }
  }
    
  if (method == "DELETE") {
    for (std::set<std::shared_ptr<PantherExpress::HandlerMap>>::iterator it = this->deleteHandlers.begin(); it != this->deleteHandlers.end(); ++it){
      std::shared_ptr<PantherExpress::HandlerMap> handler = *it;
      if (handler->path == path) {
        return handler->factory->makeDeleteController()->handler(res);
      }
    }
  }
  
  return res->status(PantherExpress::HTTP_STATUS::NOT_FOUND)->send("Controller not found or Method not supported");
}

void PantherExpress::Application::Get(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->getHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("GET", path, factory)));
}

void PantherExpress::Application::Post(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->postHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("POST", path, factory)));
}

void PantherExpress::Application::Put(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->putHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("PUT", path, factory)));
}

void PantherExpress::Application::Delete(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->deleteHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("DELETE", path, factory)));
}

void PantherExpress::Application::All(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->getHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("GET", path, factory)));
  this->postHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("POST", path, factory)));
  this->putHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("PUT", path, factory)));
  this->deleteHandlers.insert(std::shared_ptr<PantherExpress::HandlerMap>(new PantherExpress::HandlerMap("DELETE", path, factory)));
}
