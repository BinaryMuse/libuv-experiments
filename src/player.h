#pragma once

#include <uv.h>
#include "connection.h"
#include "world.h"

class Player final : public Connection {
  public:
    Player(World* world, uv_stream_t* conn, const std::string& name);
    void HandleInput(const std::string& input) override;
    ConnectionType GetConnectionType() override { return ConnectionType::PLAYING; };

    const std::string& GetName() { return name_; }

  private:
    std::string name_;
};
