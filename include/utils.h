#pragma once
#include <algorithm>
#include <stdexcept>

// Elegant way to clip a value generically 
// Credit: https://stackoverflow.com/questions/9323903/most-efficient-elegant-way-to-clip-a-number
template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
  if (lower > upper) {
      throw std::runtime_error("Lower value  > upper value is invalid");
  }
  return std::max(lower, std::min(n, upper));
}