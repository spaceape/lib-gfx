#ifndef sonar_gfx_raster_blit_h
#define sonar_gfx_raster_blit_h
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
#include <gfx/raster.h>
#include "surface.h"

/* blit_ptr
 * blit buffer
*/

__namespace_sonar
__namespace_gfx

class blit_ptr: public box2d_t
{
  surface_ptr*  m_surface;

  public:
          blit_ptr() noexcept;
          blit_ptr(surface_ptr&) noexcept;
          blit_ptr(surface_ptr&, std::int16_t, std::int16_t, std::int16_t, std::int16_t) noexcept;
          blit_ptr(surface_ptr&, std::int16_t, std::int16_t, std::uint16_t, std::uint16_t) noexcept;
          blit_ptr(const blit_ptr&) noexcept;
          blit_ptr(blit_ptr&&) noexcept;
          ~blit_ptr();

  inline  std::uint8_t  get_format() const noexcept {
          return m_surface->get_format();
  }

  inline  std::uint16_t get_stride() const noexcept {
          return m_surface->get_sx();
  }

  inline  gfx::pixel32_t* get_line(std::uint16_t index) const noexcept {
          return m_surface->get_line(index + get_py0()) + get_px0();
  }

          void assign(const blit_ptr&) noexcept;
          void reset() noexcept;
          void release() noexcept;

  inline  operator bool() const noexcept {
          return m_surface;
  }

          blit_ptr& operator=(const blit_ptr& rhs) noexcept;
          blit_ptr& operator=(blit_ptr&& rhs) noexcept;
};
__endspace_gfx
__endspace_sonar
#endif
