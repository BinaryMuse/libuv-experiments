#include <iostream>
#include <string>
#include "login.h"
#include "utils.h"

Login::Login(World* world, uv_stream_t* conn) :
  Connection(world, conn) {}

void Login::HandleInput(const std::string& input) {
  std::string name(input);
  rtrim(name);
  std::cout << "Got new char: " << name << std::endl;
  world_->PromoteToPlayer(this, name);
}
