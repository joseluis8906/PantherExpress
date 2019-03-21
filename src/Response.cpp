#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>

#include "Response.hpp"

PantherExpress::Response::Response() {
  this->statusCode = PantherExpress::HTTP_STATUS::OK;
  this->set("Content-Type", "text/plain; charset=utf-8")->set("X-Powered-By", "PantherExpress");
}

int PantherExpress::Response::send(const std::string &body) {
  this->response = MHD_create_response_from_buffer (body.size(), (void*) body.data(), MHD_RESPMEM_MUST_COPY);
  this->setHeaders();

  int ret;
  ret = MHD_queue_response (this->connection, this->statusCode, this->response);
  MHD_destroy_response (response);
  return ret;
}

void PantherExpress::Response::setConnection(struct MHD_Connection *connection){
  this->connection = connection;
}

struct MHD_Connection* PantherExpress::Response::getConnection(){
  return this->connection;
}

PantherExpress::Response* PantherExpress::Response::set(std::string key, std::string value){
  this->headers.insert(std::pair<std::string, std::string>(key, value));
  return this;
}

PantherExpress::Response* PantherExpress::Response::status(HTTP_STATUS statusCode){
  this->statusCode = statusCode;
  return this;
}

void PantherExpress::Response::setHeaders() {
  for (std::map<std::string, std::string>::iterator it = this->headers.begin(); it != this->headers.end(); ++it){
    MHD_add_response_header(this->response, it->first.data(), it->second.data());
  }
}
