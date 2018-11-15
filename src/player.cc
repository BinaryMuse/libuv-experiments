#include <iostream>
#include <string>
#include "connection.h"
#include "player.h"
#include "world.h"
#include "utils.h"

Player::Player(World& world, uv_stream_t* conn, const std::string& name) :
  Connection(world, conn), name_(name) {}

void Player::HandleInput(const std::string& input) {
  if (input == "quit") {
    this->Send("Goodbye!\n");
    world_->Logout(*this);
  } else {
    this->Send(tprintf("Sorry, I didn't understand: %s\n", input));
    std::cout << "Unknown input: " << input << std::endl;
  }
}

// void Player::HandleInput([[maybe_unused]] uv_stream_t* client, [[maybe_unused]] ssize_t nread, const uv_buf_t* buf) {
//   if (state_ == PlayerState::AWAITING_LOGIN) {
//     std::string name(buf->base);
//     name_ = rtrim(name);
//     std::cout << "Got new char: " << name_ << std::endl;
//     state_ = PlayerState::CONTROLLING_NAME;
//     this->Send(tprintf("Welcome to the game, %s!\n", name_));
//     world_->SendExcept(this, tprintf("%s has joined the game!\n", name_));
//   } else {
//     std::string input(buf->base);
//     std::string message = rtrim(input);
//     this->Send(tprintf("You say: %s\n", message));
//     world_->SendExcept(this, tprintf("%s says: %s\n", name_, message));
//   }
// }
