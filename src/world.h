#pragma once

#include <map>
#include <uv.h>

class Player;

class World {
  public:
    World(uv_loop_t* loop) : loop_(loop) {};
    void AcceptConnection(uv_tcp_t* client);
    void Send(const Player* player, const std::string& message);
    void SendExcept(const Player* player, const std::string& message);

  private:
    void HandleRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    uv_loop_t* loop_;
    std::map<uv_stream_t*, Player*> players_;
    std::map<const Player*, uv_stream_t*> connections_;
};
