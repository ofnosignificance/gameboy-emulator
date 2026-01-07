#pragma once

#include <memory>

namespace DMG01
{
  class Memory
  {
    public:
      std::unique_ptr<unsigned char[]> space;
      Memory();
  };
}
