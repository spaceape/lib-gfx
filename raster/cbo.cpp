/**
    Copyright (c) 2020, wicked systems

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
    THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
#include "cbo.h"
#include <cstring>

__namespace_sonar
__namespace_gfx

      cbo::cbo() noexcept:
      dc(),
      m_sx(0),
      m_sy(0),
      m_format(sfx::fmt_undef),
      m_size(0),
      m_data(nullptr)
{
}

      cbo::cbo(std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept:
      cbo()
{
      reset(format, sx, sy);
}

      cbo::cbo(const cbo& copy) noexcept:
      cbo()
{
      reset(copy);
}

      cbo::cbo(cbo&& copy) noexcept:
      cbo(copy)
{
      copy.release();
}

      cbo::~cbo()
{
      dispose();
}

bool  cbo::reset(std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept
{
      char*       l_data = m_data;
      std::size_t l_size = m_size;
      if(sdc_make_cbo(l_data, format, sx, sy, l_size)) {
          m_data = l_data;
          m_size = l_size;
          return true;
      }
      return false;
}

bool  cbo::reset(const cbo& copy) noexcept
{
      if(reset(copy.m_format, copy.m_sx, copy.m_sy)) {
          std::memcpy(m_data, copy.m_data, copy.m_size);
          return true;
      }
      return false;
}

bool  cbo::resize(std::int16_t sx, std::int16_t sy) noexcept
{
      if((sx > m_sx) || (sy > m_sy)) {
          return reset(m_format, sx, sy);
      }
      return true;
}

void  cbo::dispose() noexcept
{
      char*       l_data = m_data;
      std::size_t l_size = m_size;
      if(sdc_free_cbo(l_data, m_format, m_sx, m_sy, l_size)) {
          m_data = nullptr;
          m_size = 0;
      }
}

void  cbo::release() noexcept
{
      m_size = 0;
      m_data = nullptr;
}
  
cbo&  cbo::operator=(const cbo& rhs) noexcept
{
      if(this != std::addressof(rhs)) {
          reset(rhs);
      }
      return *this;
}

cbo&  cbo::operator=(cbo&& rhs) noexcept
{
      if(this != std::addressof(rhs)) {
          m_sx = rhs.m_sx;
          m_sy = rhs.m_sy;
          m_format = rhs.m_format;
          m_size = rhs.m_size;
          m_data = rhs.m_data;
          rhs.release();
      }
      return *this;
}

__endspace_gfx
__endspace_sonar
