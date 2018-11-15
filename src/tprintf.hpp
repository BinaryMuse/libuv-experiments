#include <string>

template <typename F, typename... Args>
std::string tprintf(const F& format, Args&&... args) {
  boost::format fmt(format);
  (fmt % ... % std::forward<Args>(args));
  return fmt.str();
}
