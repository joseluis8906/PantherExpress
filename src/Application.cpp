#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "Application.hpp"

PantherExpress::Application::Application() {}

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
    for (std::vector<std::shared_ptr<PantherExpress::Router>>::iterator it = this->getRouters.begin(); it != this->getRouters.end(); ++it){
      std::shared_ptr<PantherExpress::Router> router = *it;
      if (router->path == path) {
        return router->handler(res);
      }
    }
  }
  
  if (method == "POST") {
    for (std::vector<std::shared_ptr<PantherExpress::Router>>::iterator it = this->postRouters.begin(); it != this->postRouters.end(); ++it){
      std::shared_ptr<PantherExpress::Router> router = *it;
      if (router->path == path) {
        return router->handler(res);
      }
    }
  }
  
  if (method == "PUT") {
    for (std::vector<std::shared_ptr<PantherExpress::Router>>::iterator it = this->putRouters.begin(); it != this->putRouters.end(); ++it){
      std::shared_ptr<PantherExpress::Router> router = *it;
      if (router->path == path) {
        return router->handler(res);
      }
    }
  }
  
  if (method == "DELETE") {
    for (std::vector<std::shared_ptr<PantherExpress::Router>>::iterator it = this->deleteRouters.begin(); it != this->deleteRouters.end(); ++it){
      std::shared_ptr<PantherExpress::Router> router = *it;
      if (router->path == path) {
        return router->handler(res);
      }
    }
  }

  return res->status(PantherExpress::HTTP_STATUS::NOT_FOUND)->send("Not found.");
}

void PantherExpress::Application::Get(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->getRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory)));
}

void PantherExpress::Application::Get(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::vector<std::shared_ptr<PantherExpress::Middleware>> middlewares) {
  this->getRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory, middlewares)));
}
/*
void PantherExpress::Application::Post(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->postRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("POST", path, factory)));
}

void PantherExpress::Application::Post(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares) {
  this->postRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory, middlewares)));
}

void PantherExpress::Application::Put(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->putRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("PUT", path, factory)));
}

void PantherExpress::Application::Put(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares) {
  this->putRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory, middlewares)));
}

void PantherExpress::Application::Delete(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->deleteRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("DELETE", path, factory)));
}

void PantherExpress::Application::Delete(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares) {
  this->deleteRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory, middlewares)));
}
*/
void PantherExpress::Application::All(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->getRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory)));
  this->postRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("POST", path, factory)));
  this->putRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("PUT", path, factory)));
  this->deleteRouters.push_back(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("DELETE", path, factory)));
}
/*
void PantherExpress::Application::All(std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory, std::set<PantherExpress::Middleware> middlewares) {
  this->getRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("GET", path, factory, middlewares)));
  this->postRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("POST", path, factory, middlewares)));
  this->putRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("PUT", path, factory, middlewares)));
  this->deleteRouters.insert(std::shared_ptr<PantherExpress::Router>(new PantherExpress::Router("DELETE", path, factory, middlewares)));
}
*/
