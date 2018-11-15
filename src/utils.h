#pragma once

#include <string>
#include <boost/format.hpp>
#include <uv.h>

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
uv_buf_t str_to_buf(std::string str);
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

template <typename F, typename... Args>
inline std::string tprintf(const F& format, Args&&... args);

#include "tprintf.hpp"
