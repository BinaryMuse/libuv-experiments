#pragma once

#include <uv.h>
#include "world.h"

enum class ConnectionType {
  LOGIN,
  PLAYING
};

class Connection {
  public:
    void Send(const std::string& message);
    virtual void HandleInput(const std::string& input) = 0;
    uv_stream_t* GetConn() { return conn_; }
    virtual ConnectionType GetConnectionType() = 0;

  protected:
    Connection(World& world, uv_stream_t* conn) :
      world_(&world), conn_(conn) {}

    std::shared_ptr<World> world_;
    uv_stream_t* conn_;
};
