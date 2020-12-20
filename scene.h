#ifndef sonar_GFX_scene_h
#define sonar_GFX_scene_h
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
#include <sfx/raster.h>
#include <sfx/object.h>
#include <sfx/widget.h>
#include <gfx/raster/cbo.h>
#include <gfx/raster/rbo.h>
#include "driver.h"
#include <memory>
#include <memory/pool.h>
#include <memory/bank.h>
#include <memory/fragment.h>

__namespace_sonar
__namespace_gfx

class scene: public sfx::widget
{
  driver*           m_driver;
  fragment*         m_resource;
  std::uint8_t      m_mode;
  std::uint8_t      m_format;
  std::uint8_t      m_charset_sx;
  std::uint8_t      m_charset_sy;

  std::uint16_t     m_save_charset_sx;
  std::uint16_t     m_save_charset_sy;
  std::uint8_t*     m_save_charset_ptr;
  std::uint32_t*    m_save_palette;
  dc*               m_save_dc;

  private:
  static constexpr std::uint8_t f_geometry_dirty = f_user_min << 0;   // geometry of the scene or one of the widgets in the scene has changed
  static constexpr std::uint8_t f_contents_dirty = f_user_min << 1;

  protected:
  /* bld_path_t
  */
  struct bld_path_t {
    bld_path_t*     root;
    sfx::widget*    widget;
    std::int16_t    list_head_pos;  
    std::int16_t    list_last_pos;
    sfx::box2d_t    widget_geometry;
    sfx::box2d_t    global_geometry;
  };

  /* bld_tree_t
  */
  struct bld_tree_t {
  };

  /* dwl_node_t
     draw list node
  */
  struct dwl_node_t {
    sfx::widget*    widget;           // source of the draw node
    sfx::box2d_t    render_geometry;  // draw node geometry, relative to widget geometry
    sfx::box2d_t    update_geometry;  // update geometry, relative to widget geometry
  };

  /* sds_node_t
     surface data store node
  */
  struct sds_node_t {
    gfx::cbo  cbo;
    gfx::rbo  rbo;
    bool      dirty;
  };

  /* syn_path_t
  */
  struct syn_path_t {
    float     dt;
  };

  protected:
  memory::pool<dwl_node_t, heap>          m_draw_list;
  memory::bank<sds_node_t, 1024, 1, heap> m_data_store;

  protected:

  // draw list routines
          auto  dwl_make(sfx::widget*, std::int16_t, std::int16_t, std::int16_t, std::int16_t) noexcept -> dwl_node_t*;
          void  dwl_replace(dwl_node_t*, sfx::widget*, const sfx::box2d_t&) noexcept;
          void  dwl_release(dwl_node_t*) noexcept;
          auto  dwl_at(unsigned int) const noexcept -> dwl_node_t*;
          auto  dwl_get_last_pos() const noexcept -> unsigned int;
          auto  dwl_get_tail_pos() const noexcept -> unsigned int;
          void  dwl_drop() noexcept;
          void  dwl_reserve(unsigned int) noexcept;

  // surface draw routines
          void  sds_push() noexcept;
          auto  sds_find(sfx::widget*, bool) noexcept -> sds_node_t*;
  virtual bool  sdc_make_cbo(char*&, std::uint8_t, std::uint16_t, std::uint16_t, std::size_t&) noexcept override;
  virtual bool  sdc_free_cbo(char*&, std::uint8_t, std::uint16_t, std::uint16_t, std::size_t&) noexcept override;
  virtual bool  sdc_make_rbo(void*&, std::uint8_t, std::uint16_t, std::uint16_t, std::size_t&) noexcept override;
  virtual bool  sdc_free_rbo(void*&, std::uint8_t, std::uint16_t, std::uint16_t, std::size_t&) noexcept override;
          bool  sds_reserve_widget(sfx::widget*, bool) noexcept;
          bool  sds_dispose_widget(sfx::widget*, bool) noexcept;
          void  sds_pop() noexcept;

  protected:
  // virtual void  blt_draw_background(rbo&, std::int16_t, std::int16_t, std::int16_t, std::int16_t) noexcept;
  // virtual void  blt_draw_widget(rbo&, sfx::widget*, std::int16_t, std::int16_t, std::int16_t, std::int16_t) noexcept;
  //         //void  bld_draw_window() noexcept;

  // virtual void  blt_draw_foreground(rbo&, std::int16_t, std::int16_t, std::int16_t, std::int16_t) noexcept;
  //         void  blt_save(sfx::widget::context_t&) noexcept;
  //         void  blt_restore(sfx::widget::context_t&) noexcept;

  virtual void  set_contents_dirty(sfx::widget*) noexcept override final;
  virtual void  set_geometry_dirty(sfx::widget*, unsigned int) noexcept override final;
  virtual void  set_hierarchy_dirty(sfx::widget*, unsigned int) noexcept override final;


          //bool  fbr_fill(gfx::blit_ptr&, sfx::widget*) noexcept;
          //bool  fbr_render_window(gfx::blit_ptr&, sfx::widget*, std::int16_t = 0, std::int16_t = 0) noexcept;

  private:
          bool  build_draw_list() noexcept;
          bool  build_draw_list(sfx::widget*, bld_path_t&, bld_tree_t&) noexcept;
          bool  render_draw_list() noexcept;
          bool  patch_draw_list() noexcept;
          void  clear_draw_list() noexcept;

          bool  sync_tree(sfx::widget*, float) noexcept;

  public:
  static constexpr uint8_t a_intern  = a_user_min << 0;
  static constexpr uint8_t a_use_cbr = a_user_min << 0;       // use character buffers
  static constexpr uint8_t a_use_fbr = a_user_min << 1;       // use pixel buffers
  static constexpr uint8_t a_cache   = a_use_cbr | a_use_fbr;

  public:
          scene() noexcept;
          scene(const scene&) noexcept = delete;
          scene(scene&&) noexcept = delete;
  virtual ~scene();

          int    get_charset_sx() const noexcept;
          int    get_charset_sy() const noexcept;

          void   set_viewport_position(int16_t, uint16_t) noexcept;
          void   set_viewport_size(int16_t, int16_t) noexcept;
          void   set_viewport_geometry(int16_t, int16_t, int16_t, int16_t) noexcept;

          bool   attach(sfx::widget*, std::uint8_t) noexcept;
          bool   detach(sfx::widget*) noexcept;
          bool   resume() noexcept;

          std::int8_t get_viewport_width() const noexcept;
          std::int8_t get_viewport_height() const noexcept;

          bool   suspend() noexcept;

          void   draw() noexcept;

  virtual bool   sync(float) noexcept override;

          scene& operator=(const scene&) noexcept = delete;
          scene& operator=(scene&&) noexcept = delete;
};

__endspace_gfx
__endspace_sonar
#endif
