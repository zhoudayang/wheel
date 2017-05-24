#pragma once

#include <stdint.h>
#include <cstddef>

namespace zy
{
  inline uint32_t hash(const char* data, size_t n, uint32_t seed)
  {
    const uint32_t m = 0xc6a4a793;
    const uint32_t r = 24;
    const char* limit = data + n;
    uint32_t h = seed ^ (n * m);

    // Pick up four bytes at a time
    while (data + 4 <= limit) {
      // tricky way
      uint32_t w = *reinterpret_cast<const uint32_t*>(static_cast<const void*>(data));
      data += 4;
      h += w;
      h *= m;
      h ^= (h >> 16);
    }

    // Pick up remaining bytes
    switch (limit - data) {
      case 3:
        h += static_cast<unsigned char>(data[2]) << 16;
      case 2:
        h += static_cast<unsigned char>(data[1]) << 8;
      case 1:
        h += static_cast<unsigned char>(data[0]);
        h *= m;
        h ^= (h >> r);
        break;
    }
    return h;
  }

}
