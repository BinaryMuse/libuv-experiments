#ifndef FILE_UTILS_H__
#define FILE_UTILS_H__

#include <iostream>
#include <string>
#include <cstdio>
#include <uv.h>

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  buf->base = (char*)malloc(suggested_size);
  buf->len = suggested_size;
}

uv_buf_t str_to_buf(std::string str) {
  return uv_buf_init(const_cast<char*>(str.c_str()), (unsigned int)str.length());
}

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ") {
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

// template<typename ... Args>
// std::string str_format(const std::string& format, Args ... args) {
//     size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
//     std::unique_ptr<char[]> buf(new char[size]);
//     snprintf(buf.get(), size, format.c_str(), args ...);
//     return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
// }

#endif /* !FILE_UTILS_H__ */

