#pragma once

#include <unordered_map>
#include <string>

class Room {
  public:
    Room(int id) : id_(id) {}
    int GetId() { return id_; }
    void SetExit(const std::string& direction, int destination);
    void RemoveExit(const std::string& direction) { exits_.erase(direction); }
    int GetRoomAtExit(const std::string& direction);

    void SetDescription(const std::string& desc) { description_ = desc; }
    std::string& GetDescription() { return description_; }

  private:
    int id_;
    std::string description_;
    std::unordered_map<std::string, int> exits_;
};
