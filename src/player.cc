#include <iostream>
#include <string>
#include <sstream>
#include "player.h"
#include "world.h"
#include "utils.h"

Player::Player(World* world) {
  world_ = world;
  state_ = AWAITING_LOGIN;
}

void Player::HandleInput(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
  if (state_ == AWAITING_LOGIN) {
    std::cout << "Got new char: " << buf->base << std::endl;
    std::string name(buf->base);
    name_ = rtrim(name);
    state_ = CONTROLLING_NAME;
    std::ostringstream msg;
    msg << "Welcome to the game, " << name_ << "!" << std::endl;
    this->Send(msg.str());
  } else {
    std::cout << "Would process command: " << buf->base << " for " << name_ << std::endl;
  }
}

void Player::Send(std::string message) {
  return world_->Send(this, message);
}
