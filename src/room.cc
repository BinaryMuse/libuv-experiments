#include "room.h"
#include "player.h"

void Room::SetExit(const std::string& direction, int destination) {
  exits_[direction] = destination;
}

int Room::GetRoomIdAtExit(const std::string& direction) {
  auto match = exits_.find(direction);
  if (match == exits_.end()) {
    return 0;
  } else {
    return match->second;
  }
}

std::shared_ptr<Room> Room::GetRoomAtExit(const std::string& direction) {
  return world_->GetRoom(GetRoomIdAtExit(direction));
}

void Room::AddPlayer(const Player& player) {
  players_.insert(player.GetName());
}

void Room::RemovePlayer(const Player& player) {
  players_.erase(player.GetName());
}
