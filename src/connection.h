#pragma once

#include <uv.h>

class World;

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

    World* world_;
    uv_stream_t* conn_;
};
