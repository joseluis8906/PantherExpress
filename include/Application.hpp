#ifndef _PANTHER_APPLICATION_
#define _PANTHER_APPLICATION_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <cstring>
#include <cstdio>
#include <iostream>

namespace PantherExpress {
  class Application {
    private:
      struct MHD_Daemon *daemon;
       static int answer_to_connection(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **con_cls);
 
    public:
      int listen(int port);
      
      template<typename F>
      void get(std::string path, F cb) {
        std::cout << "El path es: " << path << std::endl;
        cb();
      }
      
  };
}

#endif
