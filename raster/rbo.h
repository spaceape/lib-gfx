#ifndef gfx_raster_rbo_h
#define gfx_raster_rbo_h
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
#include <gfx.h>
#include <sfx/dc.h>
#include <sfx/raster.h>

__namespace_sonar
__namespace_gfx

/* rbo
   raster buffer object
*/
class rbo: public sfx::dc
{
  std::int16_t    m_sx;
  std::int16_t    m_sy;
  std::uint8_t    m_format;
  std::uint32_t   m_size:24;
  sfx::pixel32_t* m_data;

  public:
          rbo() noexcept;
          rbo(std::uint8_t, std::int16_t, std::int16_t) noexcept;
          rbo(const rbo&) noexcept;
          rbo(rbo&&) noexcept;
          ~rbo();

  inline  std::int16_t get_sx() const noexcept {
          return m_sx;
  }
  
  inline  std::int16_t get_sy() const noexcept {
          return m_sy;
  }
  
  inline  auto   get_format() const noexcept -> std::uint8_t {
          return m_format;
  }

  inline  bool   has_format(std::uint8_t format) const noexcept {
          return m_format & format;
  }

  inline  auto   get_ptr() const noexcept -> sfx::pixel32_t* {
          return m_data;
  }

  inline  auto   get_ptr(std::int32_t offset) const noexcept -> sfx::pixel32_t* {
          return m_data + offset;
  }

  inline  auto   get_line(std::int16_t index) const noexcept -> sfx::pixel32_t* {
          return m_data + index * m_sx;
  }

          bool  reset(std::uint8_t, std::int16_t, std::int16_t) noexcept;
          bool  reset(const rbo&) noexcept;
          bool  resize(std::int16_t, std::int16_t) noexcept;
          void  dispose() noexcept;
          void  release() noexcept;
  
  inline  std::uint8_t*   get_data_ptr() const noexcept {
          return reinterpret_cast<std::uint8_t*>(m_data);
  }
  
  inline  std::int32_t    get_data_stride() const noexcept {
          return m_sx * sizeof(sfx::pixel32_t);
  }

  inline  auto  operator[](std::int32_t index) const noexcept -> sfx::pixel32_t* {
          return get_line(index);
  }

  inline  operator bool() const noexcept {
          return m_data;
  }

          rbo&  operator=(const rbo&) noexcept;
          rbo&  operator=(rbo&&) noexcept;
};

__endspace_gfx
__endspace_sonar
#endif
