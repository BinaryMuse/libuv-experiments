#pragma once

#include <unordered_map>
#include <memory>
#include <uv.h>

class Player;
class Login;
class Room;
class Connection;

class World {
  public:
    World();
    void AcceptConnection(uv_tcp_t* client);
    void Send(Connection& player, const std::string& message);
    void SendExcept(Connection& player, const std::string& message);

    void PromoteToPlayer(Login& player, const std::string& name);
    void Logout(Player& player);

    void TeleportPlayerToRoom(Player& player, int room_id);
    void MovePlayer(Player& player, Room& old_room, Room& new_room, const std::string& direction);

    std::shared_ptr<Room> GetRoom(int room_id);

  private:
    void HandleRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    std::shared_ptr<Connection> GetConnection(uv_stream_t* client);

    std::unordered_map<std::string, std::shared_ptr<Player>> players_by_name_;
    std::unordered_map<uv_stream_t*, std::shared_ptr<Connection>> conns_;
    std::unordered_map<int, std::shared_ptr<Room>> rooms_;
};
