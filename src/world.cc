#include <iostream>
#include <stdarg.h>
#include <memory>
#include <uv.h>
#include "login.h"
#include "world.h"
#include "player.h"
#include "utils.h"

#include <cassert>

World::World() {
  {
    std::shared_ptr<Room> room(new Room(*this, 1));
    room->SetDescription("A Plain Room\n\nThis is a plain room. There's not much here. There is a foyer to the east.");
    rooms_[room->GetId()] = room;
    room->SetExit("east", 2);
  }

  {
    std::shared_ptr<Room> room(new Room(*this, 2));
    room->SetDescription("The Foyer\n\nThis is an ornate foyer. There is a chandelier overhead. There is a very plain looking room to the west.");
    rooms_[room->GetId()] = room;
    room->SetExit("west", 1);
  }
}

void World::AcceptConnection(uv_tcp_t* client) {
  client->data = this;
  std::shared_ptr<Connection> login(new Login(*this, (uv_stream_t*) client));
  conns_.insert_or_assign((uv_stream_t*)client, login);
  login->Send("Welcome to the game! Please enter your character name.\n");
  uv_read_start((uv_stream_t*)client, alloc_buffer,
    [](uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
      World* world = static_cast<World*>(client->data);
      world->HandleRead(client, nread, buf);
    }
  );
}

void World::HandleRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
  if (nread < 0) {
    if (nread != UV_EOF) {
      std::cerr << "Read error: " << uv_err_name(nread) << std::endl;
    } else {
      std::cout << "Client disconnecting." << std::endl;
    }
    uv_close((uv_handle_t*)client, NULL);
    conns_.erase(client);
  } else if (nread > 0) {
    std::shared_ptr<Connection> player = this->GetConnection(client);
    if (!player) {
      std::cerr << "Could not process input as no connection was found." << std::endl;
    } else {
      std::string input(buf->base, nread);
      rtrim(input);
      player->HandleInput(input);
    }
  }

  if (buf->base) {
    delete buf->base;
  }
}

void World::PromoteToPlayer(Login& player, const std::string& name) {
  uv_stream_t* conn = player.GetConn();
  std::shared_ptr<Player> loggedIn(new Player(*this, conn, name));
  conns_.insert_or_assign(conn, loggedIn);
  players_by_name_.insert_or_assign(loggedIn->GetName(), loggedIn);
  loggedIn->Send(tprintf("Welcome to the game, %s!\n", loggedIn->GetName()));

  this->TeleportPlayerToRoom(*loggedIn, 1);
}

void World::Logout(Player& player) {
  const std::string& name = player.GetName();
  auto client = player.GetConn();
  uv_close((uv_handle_t*)client, NULL);
  conns_.erase(client);
  players_by_name_.erase(name);
}

void World::TeleportPlayerToRoom(Player& player, int room_id) {
  auto room = this->GetRoom(room_id);
  if (!room) {
    std::cerr << "Could not move player to room " << room_id <<
      " because the room does not exist" << std::endl;
    return;
  }

  auto currentRoom = player.GetCurrentRoom();
  if (currentRoom) {
    currentRoom->RemovePlayer(player);
  }

  player.SetCurrentRoomId(room_id);
  room->AddPlayer(player);
}

void World::MovePlayer(Player& player, Room& old_room, Room& new_room, const std::string& direction) {
  //
}

std::shared_ptr<Room> World::GetRoom(int room_id) {
  if (room_id == 0) return nullptr;

  auto match = rooms_.find(room_id);
  if (match == rooms_.end()) {
    return nullptr;
  } else {
    return match->second;
  }
}

void World::Send(Connection& player, const std::string& message) {
  player.Send(message);
}

void World::SendExcept(Connection& player, const std::string& message) {
  for (auto it = conns_.begin(); it != conns_.end(); ++it) {
    std::shared_ptr<Connection> otherPlayer = it->second;
    if (&player == otherPlayer.get()) {
      continue;
    }

    otherPlayer->Send(message);
  }
}

std::shared_ptr<Connection> World::GetConnection(uv_stream_t* client) {
  auto match = conns_.find(client);
  if (match == conns_.end()) {
    return nullptr;
  } else {
    return match->second;
  }
}
