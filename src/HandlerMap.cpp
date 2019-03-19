#include "HandlerMap.hpp"

PantherExpress::HandlerMap::HandlerMap(std::string &method, std::string &path, std::shared_ptr<PantherExpress::Controller> controller) {
  this->method = method;
  this->path = path;
  this->controller = controller;
}
