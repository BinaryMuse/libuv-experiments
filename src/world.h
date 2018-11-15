#pragma once

#include <map>
#include <uv.h>
#include "connection.h"

class Player;
class Login;

class World {
  public:
    World() {};
    void AcceptConnection(uv_tcp_t* client);
    void Send(Connection& player, const std::string& message);
    void SendExcept(Connection& player, const std::string& message);

    void PromoteToPlayer(Login* player, const std::string& name);

  private:
    void HandleRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    Connection* GetConnection(uv_stream_t* client);

    std::map<uv_stream_t*, Connection*> conns_;
};
