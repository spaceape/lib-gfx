#ifndef sonar_GFX_driver_h
#define sonar_GFX_driver_h
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
#include <sfx.h>
#include <memory>
#include <memory/pool.h>
#include <memory/bank.h>

__namespace_sonar
__namespace_gfx

class allocator
{
  public:
          allocator() noexcept;
          allocator(const allocator&) noexcept;
          allocator(allocator&&) noexcept;
          ~allocator();
          allocator& operator=(const allocator&) noexcept;
          allocator& operator=(allocator&&) noexcept;
};

class driver
{
  public:
          driver() noexcept;
          driver(const driver&) noexcept = delete;
          driver(driver&&) noexcept = delete;
          ~driver();
          driver& operator=(const driver&) noexcept = delete;
          driver& operator=(driver&&) noexcept = delete;
};

__endspace_gfx
__endspace_sonar
#endif
