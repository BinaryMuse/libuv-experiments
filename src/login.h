#pragma once

#include <uv.h>
#include "connection.h"
#include "world.h"

class Login final : public Connection {
  public:
    Login(World& world, uv_stream_t* conn);
    void HandleInput(const std::string& input) override;
    ConnectionType GetConnectionType() override { return ConnectionType::LOGIN; }
};

