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
#include "blit.h"

__namespace_sonar
__namespace_gfx

      blit_ptr::blit_ptr() noexcept:
      box2d_t(),
      m_surface(nullptr)
{
}

      blit_ptr::blit_ptr(surface_ptr& surface) noexcept:
      box2d_t(0, 0, surface.get_sx(), surface.get_sy()),
      m_surface(std::addressof(surface))
{
}

      blit_ptr::blit_ptr(surface_ptr& surface, std::int16_t px0, std::int16_t py0, std::int16_t px1, std::int16_t py1) noexcept:
      box2d_t(px0, py0, px1, py1),
      m_surface(std::addressof(surface))
{
}

      blit_ptr::blit_ptr(surface_ptr& surface, std::int16_t px, std::int16_t py, std::uint16_t sx, std::uint16_t sy) noexcept:
      box2d_t(px, py, sx, sy),
      m_surface(std::addressof(surface))
{
}

      blit_ptr::blit_ptr(const blit_ptr& copy) noexcept:
      box2d_t(copy),
      m_surface(copy.m_surface)
{
}

      blit_ptr::blit_ptr(blit_ptr&& copy) noexcept:
      box2d_t(std::move(copy)),
      m_surface(copy.m_surface)
{
      copy.release();
}

      blit_ptr::~blit_ptr()
{
}

void  blit_ptr::assign(const blit_ptr& copy) noexcept
{
      box2d_t::assign(copy);
      m_surface = copy.m_surface;
}

void  blit_ptr::release() noexcept
{
      box2d_t::release();
      m_surface = nullptr;
}

blit_ptr& blit_ptr::operator=(const blit_ptr& rhs) noexcept
{
      assign(rhs);
      return *this;
}

blit_ptr& blit_ptr::operator=(blit_ptr&& rhs) noexcept
{
      assign(rhs);
      rhs.release();
      return *this;
}

__endspace_gfx
__endspace_sonar
