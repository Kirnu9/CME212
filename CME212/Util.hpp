#ifndef CME212_UTIL_HPP
#define CME212_UTIL_HPP

/**
 * @file Util.hpp
 * Common helper code for CME212
 *
 * @brief Some common utilities for use in CME212
 */

#include <iostream>
#include <sstream>
#include <chrono>
#include <unistd.h>
#include <cassert>
#include <cstdlib>
#include <cmath>

#include <random>
#include <array>

namespace CME212 {

static std::mt19937 default_generator;

/** Return a uniform random double in [a,b] */
double random(double a, double b) {
  std::uniform_real_distribution<double> dist(a, b);
  return dist(default_generator);
}

/** Return a uniform random double in [0,1] */
double random() {
  return random(0,1);
}

/** @brief Clock class useful for timing code segments.
 *
 * @code
 * CME212::Clock clock;
 * // code to time
 * double time = clock.seconds();
 * @endcode
 */
class Clock {
 public:
  typedef std::chrono::high_resolution_clock clock;
  typedef typename clock::time_point         time_point;
  typedef typename clock::duration           duration;
  typedef typename duration::rep             tick_type;

  Clock() : starttime_(clock::now()) {}
  /** Start this clock */
  void start() {
    starttime_ = clock::now();
  }
  /** Get the duration this clock has been running */
  duration elapsed() const {
    return clock::now() - starttime_;
  }
  /** Get the number of seconds this clock has been running */
  double seconds() const {
    typedef std::chrono::duration<double> units;
    return std::chrono::duration_cast<units>(elapsed()).count();
  }
 private:
  time_point starttime_;
};

/** Forces a thread to sleep for t seconds. Accurate to microseconds. */
int sleep(double t) {
  return usleep(t*1e6);
}

/** Read a line from @a s, parse it as @a N values of type @a T
 * @param[in,out]  s  input stream to read from
 * @param[out]     v  std::array returned if the line in @a s parses
 */
template <typename T, std::size_t N>
std::istream& operator>>(std::istream& s, std::array<T,N>& v) {
  for (auto&& a : v) s >> a;
  return s;
}

/** Read a line from @a s, parse it as type T, and store it in @a value.
 * Ignores blank lines and lines that start with '#'.
 *
 * @param[in]   s      input stream
 * @param[out]  value  value returned if the line in @a s parses
 *
 * If the line doesn't parse correctly, then @a s is set to the "failed" state.
 */
template <typename T>
std::istream& getline_parsed(std::istream& s, T& value)
{
  // Get a line from the file
  std::string str;
  do {
    getline(s, str);
  } while (s && (str.empty() || str[0] == '#'));
  std::istringstream is(str);
  is >> value;
  if (is.fail())
    s.setstate(std::istream::failbit);
  return s;
}

} // end namespace CME212



#endif
