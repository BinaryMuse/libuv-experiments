#include <iostream>
#include <uv.h>
#include "world.h"

int DEFAULT_PORT = 3333;
uv_loop_t* loop;
struct sockaddr_in addr;
World* world;

void on_new_connection(uv_stream_t* server, int status) {
  if (status < 0) {
    std::cerr << "New connection error: " << uv_strerror(status) << std::endl;
    return;
  }

  uv_tcp_t* client = new uv_tcp_t;
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    world->AcceptConnection(client);
  } else {
    uv_close((uv_handle_t*)client, NULL);
  }
}

int main() {
  loop = uv_default_loop();
  world = new World(loop);

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

  uv_tcp_bind(&server, (const sockaddr*)&addr, 0);
  int r = uv_listen((uv_stream_t*)&server, 128, on_new_connection);
  if (r) {
    std::cerr << "Listen error " << r << std::endl;
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
  // uv_idle_t idler;

  // uv_idle_init(uv_default_loop(), &idler);
  // uv_idle_start(&idler, wait_for_a_spell);

  // std::cout << "Idling..." << std::endl;
  // uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  // uv_loop_close(uv_default_loop());
  // return 0;
}
