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
  } else if (input == "look") {
    auto room = world_->GetRoom(this->current_room_);
    if (!room) {
      this->Send("Uh oh, you can't tell where you are!\n");
      std::cerr << "FATAL ERROR: player looking in non-existing room " << this->current_room_ << std::endl;
      return;
    }
    this->Send(tprintf("%s\n", room->GetDescription()));
  } else if (input == "east") {
    this->Move("east");
  } else {
    this->Send(tprintf("Sorry, I didn't understand: %s\n", input));
    std::cout << "Unknown input: " << input << std::endl;
  }
}

void Player::Move(const std::string& direction) {
  auto room = this->GetCurrentRoom();
  if (!room) {
    this->Send("You can't move because you're not in a room.\n");
    std::cerr << "Player tried to move from non-existent room." << std::endl;
    return;
  }

  auto newRoom = room->GetRoomAtExit(direction);
  if (!newRoom) {
    this->Send("There is no exit in that direction.\n");
    return;
  }

  world_->MovePlayer(*this, *room, *newRoom, direction);
}
