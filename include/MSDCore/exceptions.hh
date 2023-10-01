#ifndef MSDCORE_EXCEPTIONS_HH
#define MSDCORE_EXCEPTIONS_HH

#include <stdexcept>

struct sdl_error : public std::runtime_error {
  sdl_error(const char *s) : std::runtime_error(s) {}
};

#endif

