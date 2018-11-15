#include <iostream>
#include <string>
#include <uv.h>
#include "connection.h"
#include "utils.h"

void Connection::Send(const std::string& message) {
  uv_write_t* req = new uv_write_t;
  uv_buf_t wrbuf = str_to_buf(message);
  uv_write(req, conn_, &wrbuf, 1, [](uv_write_t* req, int status) {
    if (status) {
      std::cerr << "Write error: " << uv_strerror(status) << std::endl;
    }
    delete req;
  });
}
