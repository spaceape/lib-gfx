/*
  Copyright (c) 2016-2019, wicked systems
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
  conditions are met:
      * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
  disclaimer.
      * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
  disclaimer in the documentation and/or other materials provided with the distribution.
      * Neither the name of wicked systems nor the names of its contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
  EVENT SHALL WICKED SYSTEMS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
*/
#include "texture_ptr.h"

__namespace_sonar
__namespace_gfx

      texture_ptr::texture_ptr() noexcept:
      m_texture(0),
      m_target(0)
{
}

      texture_ptr::texture_ptr(GLenum target) noexcept:
      m_texture(0),
      m_target(target)
{
      gl::GenTextures(1, std::addressof(m_texture));
}

      texture_ptr::texture_ptr(texture_ptr&& copy) noexcept:
      m_texture(0),
      m_target(0)
{
      assign(std::move(copy));
}

      texture_ptr::~texture_ptr()
{
      reset(false);
}

void  texture_ptr::assign(const texture_ptr& copy) noexcept
{
      if(m_texture) {
          if(m_texture == copy.m_texture) {
              return;
          }
          reset(false);
      }
      m_texture = copy.m_texture;
      m_target = copy.m_target;
}

void  texture_ptr::assign(texture_ptr&& copy) noexcept
{
      assign(copy);
      copy.release();
}

GLuint texture_ptr::bind() noexcept
{
      if(m_texture != 0) {
          gl::BindTexture(m_target, m_texture);
      }
      return m_texture;
}

void  texture_ptr::unbind() noexcept
{
      gl::BindTexture(m_target, 0);
}

void  texture_ptr::release() noexcept
{
      m_texture = 0;
}

void  texture_ptr::reset(bool reset) noexcept
{
      if(m_texture) {
          gl::DeleteTextures(1, std::addressof(m_texture));
          if(reset) {
              m_texture = 0;
          }
      }
}

bool  texture_ptr::is_defined() const noexcept
{
      return m_texture;
}

      texture_ptr::operator GLuint() const noexcept
{
      return m_texture;
}

      texture_ptr::operator bool() const noexcept
{
      return is_defined();
}

texture_ptr& texture_ptr::operator=(texture_ptr&& rhs) noexcept
{
      assign(std::move(rhs));
      return *this;
}
__endspace_gfx
__endspace_sonar
