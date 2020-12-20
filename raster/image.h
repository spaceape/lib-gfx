#ifndef gfx_raster_image_h
#define gfx_raster_image_h
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

/* image_ptr
 * image_ptr buffer
*/
__namespace_sonar
__namespace_gfx

// class image_ptr
// {
//   protected:
//   std::int16_t  m_dx;
//   std::int16_t  m_dy;
//   std::int16_t  m_stride;
//   std::int16_t  m_format;
//   gfx::color_t* m_data_head;
//   gfx::color_t* m_data_tail;
// 
//   public:
//   inline  image_ptr() noexcept:
//           m_dx(0),
//           m_dy(0),
//           m_stride(0),
//           m_format(0),
//           m_data_head(nullptr),
//           m_data_tail(nullptr) {
//   }
//           
//   inline  image_ptr(std::int16_t sx, std::int16_t sy) noexcept:
//           image_ptr() {
//           resize(sx, sy);
//   }
// 
//           image_ptr(const image_ptr& copy) noexcept:
//           m_dx(copy.m_dx),
//           m_dy(copy.m_dy),
//           m_stride(copy.m_stride),
//           m_format(copy.m_format),
//           m_data_head(nullptr),
//           m_data_tail(nullptr) {
//   }
// 
//           image_ptr(image_ptr&& copy) noexcept:
//           m_dx(copy.m_dx),
//           m_dy(copy.m_dy),
//           m_stride(copy.m_stride),
//           m_format(copy.m_format),
//           m_data_head(copy.m_data_head),
//           m_data_tail(copy.m_data_tail) {
//           copy.release();
//   }
//   
//   inline  ~image_ptr() {
//           reset(false);
//   }
// 
//   inline  std::int16_t get_sx() const noexcept {
//           return m_dx;
//   }
//   
//   inline  std::int16_t get_sy() const noexcept {
//           return m_dy;
//   }
// 
//   inline  std::int16_t get_stride() const noexcept {
//           return m_stride;
//   }
// 
//   inline  std::int16_t get_format() const noexcept {
//           return m_format;
//   }
// 
//   inline  bool  resize(std::int16_t sx, std::int16_t sy) noexcept {
//           if((sx > 0) && (sy > 0)) {
//               if((sx != m_dx) || (sy != m_dy)) {
//                   std::int16_t l_dx;
//                   std::int16_t l_dy;
//                   if(sx & 7) {
//                       l_dx =(sx & 7) + 8;
//                   } else
//                       l_dx = sx;
//                   if(sy & 7) {
//                       l_dy = (sy & 7) + 8;
//                   } else
//                       l_dy = sy;
// 
//                   std::int32_t l_size = l_dx * l_dy;
//                   std::int32_t l_free = m_data_tail - m_data_head;
//                   if(l_size > l_free) {
//                       free(m_data_head);
//                       if(m_data_head = reinterpret_cast<color_t*>(malloc(l_size * sizeof(color_t))); m_data_head != nullptr) {
//                           m_data_tail = m_data_head + l_size;
//                           m_dx     = sx;
//                           m_dy     = sy;
//                           m_stride = l_dx;
//                       }
//                   }
//               }
//           }
//           return m_data_head;
//   }
// 
//   inline  color_t* get() const noexcept {
//           return m_data_head;
//   }
// 
//   inline  void  reset(bool clear = true) noexcept {
//           if(m_data_head) {
//               free(m_data_head);
//               if(clear) {
//                   release();
//               }
//           }
//   }
//   
//   inline  void  release() noexcept {
//           m_dx = 0;
//           m_dy = 0;
//           m_stride = 0;
//           m_format = 0;
//           m_data_head = nullptr;
//           m_data_tail = nullptr;
//   }
//   
//   inline  operator bool() const noexcept {
//           return m_data_head;
//   }
// 
//   inline  image_ptr& operator=(const image_ptr& rhs) noexcept {
//           resize(rhs.m_dx, rhs.m_dy);
//           return *this;
//   }
// 
//   inline  image_ptr& operator=(image_ptr&& rhs) noexcept {
//           m_dx = rhs.m_dx;
//           m_dy = rhs.m_dy;
//           m_stride = rhs.m_stride;
//           m_format = rhs.m_format;
//           m_data_head = rhs.m_data_head;
//           m_data_tail = rhs.m_data_tail;
//           rhs.release();
//           return *this;
//   }
// };
__endspace_gfx
__endspace_sonar
#endif
