#pragma once

#include <uv.h>
#include "connection.h"
#include "world.h"

class Player final : public Connection {
  public:
    Player(World& world, uv_stream_t* conn, const std::string& name);
    void HandleInput(const std::string& input) override;
    ConnectionType GetConnectionType() override { return ConnectionType::PLAYING; }

    void SetCurrentRoom(int room_id) { current_room_ = room_id; }

    const std::string& GetName() { return name_; }

  private:
    int current_room_;
    std::string name_;
};
