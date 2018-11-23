#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "player.h"
#include "world.h"
#include "room.h"

class Room {
  public:
    Room(World& world, int id) : world_(&world), id_(id) {}
    int GetId() { return id_; }

    void SetExit(const std::string& direction, int destination);
    void RemoveExit(const std::string& direction) { exits_.erase(direction); }
    int GetRoomIdAtExit(const std::string& direction);
    std::shared_ptr<Room> GetRoomAtExit(const std::string& direction);

    void SetDescription(const std::string& desc) { description_ = desc; }
    std::string& GetDescription() { return description_; }

    void AddPlayer(const Player& player);
    void RemovePlayer(const Player& player);

  private:
    std::shared_ptr<World> world_;
    int id_;
    std::string description_;
    std::unordered_map<std::string, int> exits_;
    std::unordered_set<std::string> players_;
};
