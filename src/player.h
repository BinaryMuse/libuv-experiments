#pragma once

#include <uv.h>
#include "connection.h"
#include "room.h"
#include "world.h"

class Player final : public Connection {
  public:
    Player(World& world, uv_stream_t* conn, const std::string& name);
    void HandleInput(const std::string& input) override;
    ConnectionType GetConnectionType() override { return ConnectionType::PLAYING; }

    int GetCurrentRoomId() { return current_room_; }
    void SetCurrentRoomId(int room_id) { current_room_ = room_id; }
    std::shared_ptr<Room> GetCurrentRoom() {
      return world_->GetRoom(GetCurrentRoomId());
    }
    void Move(const std::string& direction);

    const std::string& GetName() const { return name_; }

  private:
    int current_room_ = 0;
    std::string name_;
};
