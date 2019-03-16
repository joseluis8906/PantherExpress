#include "Application.hpp"
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <iostream>

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
  const char *method, const char *version,
  const char *upload_data,
  size_t *upload_data_size, 
  void **con_cls) {

  const char *page  = "<html><body>PantherExpress Hello World!</body></html>";
  struct MHD_Response *response;
  int ret;
  response = MHD_create_response_from_buffer (strlen (page), (void*) page, MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);

  return ret;
}

