#include <iostream>
#include <string>
#include "player.h"
#include "world.h"
#include "utils.h"

Player::Player(World* world) {
  world_ = world;
  state_ = PlayerState::AWAITING_LOGIN;
}

void Player::HandleInput(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
  if (state_ == PlayerState::AWAITING_LOGIN) {
    std::string name(buf->base);
    name_ = rtrim(name);
    std::cout << "Got new char: " << name_ << std::endl;
    state_ = PlayerState::CONTROLLING_NAME;
    this->Send(tprintf("Welcome to the game, %s! It's %d o'clock\n", name_, 3));
    world_->SendExcept(this, tprintf("%s has joined the game!\n", name_));
  } else {
    std::string input(buf->base);
    std::string message = rtrim(input);
    this->Send(tprintf("You say: %s\n", message));
    world_->SendExcept(this, tprintf("%s says: %s\n", name_, message));
  }
}

void Player::Send(std::string message) {
  return world_->Send(this, message);
}
