#include <iostream>
#include <string>
#include <uv.h>
#include "utils.h"

void alloc_buffer([[maybe_unused]] uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  buf->base = new char[suggested_size];
  buf->len = suggested_size;
}

uv_buf_t str_to_buf(std::string str) {
  return uv_buf_init(const_cast<char*>(str.c_str()), (unsigned int)str.length());
}

std::string& rtrim(std::string& str, const std::string& chars) {
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}
