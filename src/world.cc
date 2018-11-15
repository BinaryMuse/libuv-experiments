#include <iostream>
#include <stdarg.h>
#include <uv.h>
#include "utils.h"
#include "world.h"
#include "player.h"

void World::AcceptConnection(uv_tcp_t* client) {
  client->data = this;
  Player* player = new Player(this);
  // TODO: remove from map when disconnected
  players_.insert(std::make_pair((uv_stream_t*)(client), player));
  connections_.insert(std::make_pair(player, (uv_stream_t*)(client)));
  this->Send(player, "Welcome to the game! Please enter your character name.\n");
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
      uv_close((uv_handle_t*)client, NULL);
      return;
    }
  } else if (nread > 0) {
    auto match = players_.find(client);
    if (match == players_.end()) {
      std::cerr << "Could not process input as no player was found." << std::endl;
      if (buf->base) {
        free(buf->base);
      }
      return;
    } else {
      Player* player = match->second;
      player->HandleInput(client, nread, buf);
    }
  }

  if (buf->base) {
    free(buf->base);
  }
}

void World::Send(const Player* player, const std::string& message) {
  auto match = connections_.find(player);
  if (match == connections_.end()) {
    std::cerr << "Could not find connection to send message to player.";
    return;
  } else {
    uv_stream_t* client = match->second;
    uv_write_t* req = new uv_write_t;
    uv_buf_t wrbuf = str_to_buf(message);
    uv_write(req, client, &wrbuf, 1, [](uv_write_t* req, int status) {
      if (status) {
        std::cerr << "Write error: " << uv_strerror(status) << std::endl;
      }
      delete req;
    });
  }
}

void World::SendExcept(const Player* player, const std::string& message) {
  for (auto it = connections_.begin(); it != connections_.end(); ++it) {
    const Player* otherPlayer = it->first;
    if (player == otherPlayer) {
      continue;
    }

    this->Send(otherPlayer, message);
  }
}
