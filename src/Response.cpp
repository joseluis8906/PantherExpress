#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>

#include "Response.hpp"

int PantherExpress::Response::send(const std::string &body) {
  int ret;
  this->response = MHD_create_response_from_buffer (body.size(), (void*) body.data(), MHD_RESPMEM_MUST_COPY);
  ret = MHD_queue_response (this->connection, MHD_HTTP_OK, this->response);
  MHD_destroy_response (response);
  return ret;
}

void PantherExpress::Response::setConnection(struct MHD_Connection *connection){
  this->connection = connection;
}

struct MHD_Connection* PantherExpress::Response::getConnection(){
  return this->connection;
}

