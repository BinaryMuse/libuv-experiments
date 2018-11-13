#ifndef FILE_WORLD_H__
#define FILE_WORLD_H__

#include <map>
#include <uv.h>

class Player;

class World {
  public:
    World(uv_loop_t* loop) : loop_(loop) {};
    static void HandleReads(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    void AcceptConnection(uv_tcp_t* client);
    void Send(Player* player, std::string message);

  private:
    void HandleRead(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    uv_loop_t* loop_;
    std::map<uv_stream_t*, Player*> players_;
    std::map<Player*, uv_stream_t*> connections_;
};

#endif /* !FILE_WORLD_H__ */
