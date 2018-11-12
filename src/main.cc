#include <iostream>
#include <stdlib.h>
#include <uv.h>
#include "test.h"

int main() {
  uv_loop_t* loop = static_cast<uv_loop_t*>(malloc(sizeof(uv_loop_t)));
  uv_loop_init(loop);

  std::cout << THING << std::endl;
  uv_run(loop, UV_RUN_DEFAULT);

  uv_loop_close(loop);
  free(loop);
  return 0;
}
