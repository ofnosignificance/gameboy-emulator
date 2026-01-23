#include "Memory.hpp"
#include "Common.hpp" 
#include <memory>

namespace DMG01
{
  
  Memory::Memory()
  {
    this->space = std::make_unique<unsigned char[]>(0xffff);
  }
}
