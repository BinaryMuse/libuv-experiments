#include "room.h"

void Room::SetExit(const std::string& direction, int destination) {
  exits_[direction] = destination;
}

int Room::GetRoomAtExit(const std::string& direction) {
  auto match = exits_.find(direction);
  if (match == exits_.end()) {
    return 0;
  } else {
    return match->second;
  }
}
