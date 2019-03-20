#include "HandlerMap.hpp"

PantherExpress::HandlerMap::HandlerMap(std::string method, std::string path, std::shared_ptr<PantherExpress::ControllerFactory> factory) {
  this->method = method;
  this->path = path;
  this->factory = factory;
}
