#pragma once

#include <uv.h>
#include "world.h"

enum class PlayerState {
  AWAITING_LOGIN,
  CONTROLLING_NAME
};

class Player {
  public:
    Player(World* world);
    void HandleInput(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    void Send(std::string message);

    const std::string& GetName() { return name_; }

  private:
    PlayerState state_;
    std::string name_;
    World* world_;
};
