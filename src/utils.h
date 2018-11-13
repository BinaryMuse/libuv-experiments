#ifndef FILE_UTILS_H__
#define FILE_UTILS_H__

#include <string>
#include <uv.h>

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
uv_buf_t str_to_buf(std::string str);
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

#endif /* !FILE_UTILS_H__ */
