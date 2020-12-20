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
#include "scene.h"

extern std::uint8_t   g_std8x8_data[];
extern std::uint32_t  g_std256_data[];

__namespace_sonar
__namespace_gfx

      scene::scene() noexcept:
      widget(
          nullptr,
          a_composable,
          f_visible | f_geometry_dirty | f_contents_dirty | f_valid
      ),
      m_driver(nullptr),
      m_resource(fragment::get_default()),
      m_mode(0),
      m_format(sfx::mode_argb_8888),
      m_charset_sx(8),
      m_charset_sy(8),
      m_draw_list(heap()),
      m_data_store(heap())
{
      //m_draw_list.reserve(scene_reserve_min);
      //m_data_bank.reserve(scene_reserve_min);
      // set_geometry(-128, -128, +127, +127);
      set_viewport_geometry(-32, -12, +32, +12);
}

      scene::~scene()
{
      // fbr_dispose();
}

auto  scene::dwl_make(sfx::widget* widget, std::int16_t px0, std::int16_t py0, std::int16_t px1, std::int16_t py1) noexcept -> dwl_node_t*
{
      auto l_node = m_draw_list.raw_get();
      if(l_node) {
          l_node->widget = widget;
          l_node->render_geometry = sfx::box2d_t(px0, py0, px1, py1);
          l_node->update_geometry = sfx::box2d_t(px0, py0, px1, py1);

      }
      return l_node;
}

void  scene::dwl_replace(dwl_node_t* node, sfx::widget* widget, const sfx::box2d_t& geometry) noexcept
{
      node->widget = widget;
      node->render_geometry = geometry;
      node->update_geometry = geometry;
}

void  scene::dwl_release(dwl_node_t* node) noexcept
{
      node->widget = nullptr;
      node->render_geometry = sfx::box2d_t();
}

auto  scene::dwl_at(unsigned int index) const noexcept -> dwl_node_t*
{
      return m_draw_list.at(index);
}

auto  scene::dwl_get_last_pos() const noexcept -> unsigned int
{
      return m_draw_list.get_last() - m_draw_list.get_head();
}

auto  scene::dwl_get_tail_pos() const noexcept -> unsigned int
{
      return m_draw_list.get_tail() - m_draw_list.get_head();
}

void  scene::dwl_drop() noexcept
{
      m_draw_list.raw_unget();
}

void  scene::dwl_reserve(unsigned int size) noexcept
{
      m_draw_list.reserve(size);
}

// // /* fbr_fill()
// // */
// // bool  scene::fbr_fill(gfx::blit_ptr& target, sfx::widget* widget) noexcept
// // {
// //       gfx::pixel32_t* l_line_ptr;
// //       if(s_colour_map[0] != s_colour_map[255]) {
// //           l_line_ptr = target.get_line(0);
// //           for(unsigned int l_py = 0; l_py < target.get_sy(); l_py++) {
// //               gfx::pixel32_t* l_pixel_ptr = l_line_ptr;
// //               for(unsigned int l_px = 0; l_px < target.get_sx(); l_px++) {
// //                   l_pixel_ptr->value = s_colour_map[0];
// //                   l_pixel_ptr++;
// //               }
// //               l_line_ptr += target.get_stride();
// //           }
// //       }
// //       return true;
// // }

// // /* fbr_render_window()
// //    render widget's text buffer
// // */
// // bool  scene::fbr_render_window(gfx::blit_ptr& target, sfx::widget* widget, std::int16_t px, std::int16_t py) noexcept
// // {
// //       const char*         l_text;
// //       const std::uint8_t* l_attributes;
// //       if(widget->get_text(l_text, l_attributes) == true) {
// //           unsigned int    l_max_l = py + target.get_sy() / s_charset_sy;
// //           unsigned int    l_max_c = px + target.get_sx() / s_charset_sx;
// //           // render the image for the text buffer received from the widget
// //           // for each scan line copy the appropriate glyph lines
// //           gfx::pixel32_t* l_line_ptr = target.get_line(0);
// //           for(unsigned int l_txt_l = py; l_txt_l < l_max_l; l_txt_l++) {
// //               for(unsigned int l_img_y = 0; l_img_y < s_charset_sy; l_img_y++) {
// //                   std::uint16_t   l_char_idx = l_txt_l * widget->get_sx() + px;
// //                   gfx::pixel32_t* l_colm_ptr = l_line_ptr;
// //                   for(unsigned int l_txt_c = px; l_txt_c < l_max_c; l_txt_c++) {
// //                       std::uint8_t* l_glyph_ptr = s_charset_ptr + (l_text[l_char_idx] * s_charset_sx * s_charset_sy);
// //                       for(unsigned int l_img_x = 0; l_img_x < s_charset_sx; l_img_x++) {
// //                           unsigned int l_colour_index = l_glyph_ptr[l_img_y * s_charset_sx + l_img_x];
// //                           l_colm_ptr->value = s_colour_map[l_colour_index];
// //                           l_colm_ptr++;
// //                       }
// //                       l_char_idx++;
// //                   }
// //                   l_line_ptr += target.get_stride();
// //               }
// //           }
// //       }
// //       return true;
// // }


/* sds_push()
*/
void  scene::sds_push() noexcept
{
      // save the current context
      m_save_charset_sx = s_charset_sx;
      m_save_charset_sy = s_charset_sy;
      m_save_charset_ptr = s_charset_ptr;
      m_save_palette = s_palette;
      m_save_dc = s_dc;

      // apply the scene context
      s_charset_sx = m_charset_sx;
      s_charset_sy = m_charset_sy;
      s_charset_ptr = g_std8x8_data;
      s_palette = g_std256_data,
      s_dc = this;
}

/* sds_find()
   find the surface data store node relevant to given <widget>;
   if not found and <create> is set then create a new node.
*/
auto  scene::sds_find(sfx::widget* widget, bool create) noexcept -> sds_node_t*
{
      sds_node_t* l_data_node = nullptr;
      if(widget->get_hook()) {
          l_data_node = widget->cast_hook<sds_node_t>();
      } else
      if(create) {
          if(l_data_node = m_data_store.emplace(); l_data_node != nullptr) {
              widget->set_hook(l_data_node);
          }
      }
      return l_data_node;
}

// void  scene::sds_make_cbo(sfx::cbo& cb, std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept
// {
//       cb.reset(format, sx, sy);
// }

// void  scene::sds_reset_cbo(sfx::cbo& cb, std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept
// {
//       cb.reset(format, sx, sy);
// }

// void  scene::sds_free_cbo(sfx::cbo& cb) noexcept
// {
//       cb.dispose();
// }

// void  scene::sds_make_rbo(sfx::rbo& rb, std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept
// {
//       rb.reset(format, sx, sy);
//       scb_make_surface(rb);
// }

// void  scene::sds_reset_rbo(sfx::rbo& rb, std::uint8_t format, std::int16_t sx, std::int16_t sy) noexcept
// {
//       rb.reset(format, sx, sy);
//       scb_make_surface(rb);
// }

// void  scene::sds_free_rbo(sfx::rbo& rb) noexcept
// {
//       scb_free_surface(rb);
//       rb.dispose();
// }

bool  scene::sdc_make_cbo(char*& data, std::uint8_t format, std::uint16_t sx, std::uint16_t sy, std::size_t& size) noexcept
{
      char*       l_data = data;
      std::size_t l_size = sfx::get_surface_bytes(format, sx, sy);
      if(l_size > 0) {
          if(l_size < 0x01000000) {
              if(l_size > size) {
                  l_data = reinterpret_cast<char*>(m_resource->reallocate(data, size, l_size, 8));
                  if(l_data == nullptr) {
                      return false;
                  }
                  data = l_data;
                  size = l_size;
              }
              return true;
          }
      }
      return false;
}

bool  scene::sdc_free_cbo(char*& data, std::uint8_t format, std::uint16_t sx, std::uint16_t sy, std::size_t& size) noexcept
{
      if(data) {
          if(size) {
              m_resource->deallocate(data, size);
              size = 0;
          }
          data = nullptr;
      }
      return true;
}

bool  scene::sdc_make_rbo(void*& data, std::uint8_t format, std::uint16_t sx, std::uint16_t sy, std::size_t& size) noexcept
{
      void*       l_data = data;
      std::size_t l_size = sfx::get_surface_bytes(format, sx, sy);
      if(l_size > 0) {
          if(l_size < 0x01000000) {
              if(l_size > size) {
                  l_data = reinterpret_cast<char*>(m_resource->reallocate(data, size, l_size, 8));
                  if(l_data == nullptr) {
                      return false;
                  }
                  data = l_data;
                  size = l_size;
              }
              return true;
          }
      }
      return false;
}

bool  scene::sdc_free_rbo(void*& data, std::uint8_t format, std::uint16_t sx, std::uint16_t sy, std::size_t& size) noexcept
{
      if(data) {
          if(size) {
              m_resource->deallocate(data, size);
              size = 0;
          }
          data = nullptr;
      }
      return true;
}

/* sds_reserve_widget()
   alocate a node for the given <widget> in the surface data store;
   if <descend> is set, a node will be allocated for all the widgets in <widget>'s tree.
*/
bool  scene::sds_reserve_widget(sfx::widget* widget, bool descend) noexcept
{
      sds_node_t* l_data_node = sds_find(widget, true);
      if(l_data_node) {
          if(widget != this) {
              // set up the render node for the widget
              if(has_attributes(a_use_cbr)) {
                  l_data_node->cbo.reset(0, widget->get_sx(), widget->get_sy());
              }
              if(has_attributes(a_use_fbr)) {
                  l_data_node->rbo.reset(m_format, widget->get_sx() * s_charset_sx, widget->get_sy() * s_charset_sy);
              }
          } else
          if(widget == this) {
              // set up the root render node; the root render node always has a surface attached,
              // irrespective of whether the engine is running in cached mode or not
              l_data_node->rbo.reset(m_format | sfx::attr_primary, widget->get_sx() * s_charset_sx, widget->get_sy() * s_charset_sy);
          }
      }
      if(descend) {
          int l_widget_count = 0;
          int l_reserve_count = 0;
          for(auto l_widget_iter = widget->get_widget(0); l_widget_iter != nullptr; l_widget_iter = l_widget_iter->get_sibling(0)) {
              if(sds_reserve_widget(l_widget_iter, descend)) {
                  l_reserve_count++;
              }
              l_widget_count++;
          }
          return l_widget_count == l_reserve_count;
      }
      return true;       
}

/* sds_dispose_widget()
   free the node for the given <widget> in the surface data store;
   if <descend> is set, the nodes for all the widgets in <widget>'s tree will be freed.
*/
bool  scene::sds_dispose_widget(sfx::widget* widget, bool descend) noexcept
{
      sds_node_t* l_data_node = sds_find(widget, false);
      if(l_data_node) {
          l_data_node->rbo.dispose();
          l_data_node->cbo.dispose();
      }
      if(descend) {
          int l_widget_count = 0;
          int l_dispose_count = 0;
          for(auto l_widget_iter = widget->get_widget(0); l_widget_iter != nullptr; l_widget_iter = l_widget_iter->get_sibling(0)) {
              if(sds_dispose_widget(l_widget_iter, descend)) {
                  l_dispose_count++;
              }
              l_widget_count++;
          }
          return l_widget_count == l_dispose_count;
      }
      return true;
}

/* sds_pop()
   restore the previous context
*/
void  scene::sds_pop() noexcept
{
      s_dc = m_save_dc;
      s_palette = m_save_palette;
      s_charset_ptr = m_save_charset_ptr;
      s_charset_sy = m_save_charset_sy;
      s_charset_sx = m_save_charset_sx;
}

/* set_contents_dirty()
*/
void  scene::set_contents_dirty(widget* widget) noexcept
{
      m_flags |= f_contents_dirty;
}

/* set_geometry_dirty()
*/
void  scene::set_geometry_dirty(widget* widget, unsigned int flags) noexcept
{
      if constexpr (scene_reserve_cbo) {
          if(widget != this) {
              if(flags & opt_notify_resize) {
                  sds_push();
                  sds_reserve_widget(widget, false);
                  sds_pop();
              }
          }
      }
      m_flags |= f_geometry_dirty;
}

/* set_hierarchy_dirty()
*/
void  scene::set_hierarchy_dirty(sfx::widget*, unsigned int) noexcept
{
      m_flags |= f_geometry_dirty;
}

/* build_draw_list()
*/
bool  scene::build_draw_list() noexcept
{
      bld_tree_t l_tree;
      bld_path_t l_path;

      //reserve()
      // create root draw node
      // its coordinates are the scene coordinates represented into the global geometry
      if(auto l_draw_node = dwl_make(this, 0, 0, get_sx(), get_sy()); l_draw_node != nullptr) {
          l_path.root = nullptr;
          l_path.widget = this;
          l_path.list_head_pos = 0;
          l_path.list_last_pos = 0;
          if(auto l_widget_iter = get_widget(0); l_widget_iter != nullptr) {
              bool  l_build_result = true;
              l_path.widget_geometry.assign(
                  get_px(),
                  get_py(),
                  get_sx(),
                  get_sy()
              );
              l_path.global_geometry.assign(
                  0 - get_px(),
                  0 - get_py(),
                  get_sx(),
                  get_sy()
              );
              while(l_widget_iter && l_build_result) {
                  l_build_result = build_draw_list(l_widget_iter, l_path, l_tree);
                  if(l_build_result) {
                      l_widget_iter = l_widget_iter->get_sibling(0);
                  }
              }
              return l_build_result;
          }
      }
      return false;
}

bool  scene::build_draw_list(sfx::widget* widget, bld_path_t& root, bld_tree_t& tree) noexcept
{
      bld_tree_t&  l_tree = tree;
      bld_path_t   l_path;

      if(widget->is_visible()) {
          // setup the draw path node
          l_path.root = std::addressof(root);
          l_path.widget = widget;
          l_path.widget_geometry = widget->get_geometry();
          l_path.global_geometry = l_path.widget_geometry.translated(root.global_geometry.get_px0(), root.global_geometry.get_py0());

          l_path.list_head_pos = dwl_get_last_pos();

          if(true) {
              int  l_find_ctr = 0;
              int  l_fail_ctr = 0;
              int  l_draw_head = root.list_head_pos;
              int  l_draw_iter = root.list_last_pos;
              // find an existing draw list item from parent's draw list to borrow space from or
              // potentially replace
              while(l_draw_iter >= l_draw_head) {
                  dwl_node_t* l_draw_node = dwl_at(l_draw_iter);
                  if((l_draw_node->widget == root.widget) || (l_draw_node->widget->get_parent() == widget->get_parent())) {
                      sfx::box2d_t l_compare_geometry;
                      sfx::box2d_t l_intersect_geometry;
                      if(l_path.global_geometry.intersects(l_draw_node->render_geometry, l_intersect_geometry)) {
                          l_path.global_geometry.compare(l_draw_node->render_geometry, l_compare_geometry);
                          if(l_compare_geometry.get_py0() > 0) {
                              dwl_make(
                                  l_draw_node->widget,
                                  l_draw_node->render_geometry.get_px0(),
                                  l_draw_node->render_geometry.get_py0(),
                                  l_draw_node->render_geometry.get_px1(),
                                  l_intersect_geometry.get_py0()
                              ) || l_fail_ctr++;
                          }
                          if(l_compare_geometry.get_px0() > 0) {
                              dwl_make(
                                  l_draw_node->widget,
                                  l_draw_node->render_geometry.get_px0(),
                                  l_intersect_geometry.get_py0(),
                                  l_intersect_geometry.get_px0(),
                                  l_intersect_geometry.get_py1()
                              ) || l_fail_ctr++;
                          }
                          if(l_compare_geometry.get_px1() < 0) {
                              dwl_make(
                                  l_draw_node->widget,
                                  l_intersect_geometry.get_px1(),
                                  l_intersect_geometry.get_py0(),
                                  l_draw_node->render_geometry.get_px1(),
                                  l_intersect_geometry.get_py1()
                              ) || l_fail_ctr++;
                          }
                          if(l_compare_geometry.get_py1() < 0) {
                              dwl_make(
                                  l_draw_node->widget,
                                  l_draw_node->render_geometry.get_px0(),
                                  l_intersect_geometry.get_py1(),
                                  l_draw_node->render_geometry.get_px1(),
                                  l_draw_node->render_geometry.get_py1()
                              ) || l_fail_ctr++;
                          }
                          // assume ownership of the original node, which we've just split;
                          // if there is a second intersection, node must be erased;
                          // optimise: with l_find_ctr > 0, there is a chance that some of the
                          // split rectangles can be merged together
                          if(l_fail_ctr == 0) {
                              if(l_find_ctr == 0) {
                                  dwl_replace(dwl_at(l_draw_iter), widget, l_path.global_geometry);
                              } else
                              if(l_find_ctr > 0) {
                                  dwl_release(dwl_at(l_draw_iter));
                              }
                              l_find_ctr++;
                          } else
                          if(l_fail_ctr > 0) {
                              return false;
                          }
                      }
                  }
                  l_draw_iter--;
              }
          }

          l_path.list_last_pos = dwl_get_last_pos();

          // build the draw list for child widgets
          if(auto l_widget_iter = widget->get_widget(0); l_widget_iter != nullptr) {
              bool l_widget_build = true;
              while(l_widget_iter && l_widget_build) {
                  l_widget_build = build_draw_list(l_widget_iter, l_path, l_tree);
                  if(l_widget_build) {
                      l_widget_iter = l_widget_iter->get_sibling(0);
                  }
              }
              if(l_widget_build == false) {
                  return false;
              }
          }

          // save range to root node
          root.list_last_pos = l_path.list_last_pos;
      }
      return true;
}

bool  scene::render_draw_list() noexcept
{
      int          l_fail_ctr  = 0;
      dwl_node_t*  l_draw_node = m_draw_list.get_head();
      dwl_node_t*  l_draw_tail = m_draw_list.get_tail();

      // root render node surface coordinates
      std::int16_t l_root_px = 0;
      std::int16_t l_root_py = 0;

      // find root render node
      sds_node_t*  l_data_node = sds_find(this, true);

      sds_push();

      // set up the root render node; the root render node always has a surface attached,
      // irrespective of whether the engine is running in cached mode or not
      if(l_data_node) {
          std::uint16_t l_blit_sx  = l_draw_node->widget->get_sx() * s_charset_sx;
          std::uint16_t l_blit_sy  = l_draw_node->widget->get_sy() * s_charset_sy;
          gfx::rbo&     l_blit_ptr = l_data_node->rbo;
          if((l_blit_ptr.get_sx() != l_blit_sx) || (l_blit_ptr.get_sy() != l_blit_sy)) {
              l_blit_ptr.reset(m_format | sfx::attr_primary, l_blit_sx, l_blit_sy);
          } else
              l_blit_ptr.reset(m_format | sfx::attr_primary, l_blit_sx, l_blit_sy);
      }

      // process the draw list
      while(l_draw_node < l_draw_tail) {
          if(l_draw_node->widget) {
              if(l_draw_node->update_geometry.is_valid()) {
                  // surface coordinates
                  std::int16_t l_blit_px;
                  std::int16_t l_blit_py;

                  // draw node graphics coordinates
                  std::int16_t l_draw_px = l_draw_node->render_geometry.get_px() * s_charset_sx;
                  std::int16_t l_draw_py = l_draw_node->render_geometry.get_py() * s_charset_sy;

                  // if running in cached mode - find the appropriate render node for the
                  // widget that we are rendering and set up the surface offsets
                  if((m_attributes & a_use_fbr) != 0) {
                      l_data_node = sds_find(l_draw_node->widget, true);
                      if(l_data_node) {
                          std::int16_t  l_blit_sx;
                          std::int16_t  l_blit_sy;
                          gfx::rbo&     l_blit_ptr = l_data_node->rbo;
                          if(l_draw_node->widget != this) {
                              l_blit_px = 0;
                              l_blit_py = 0;
                              if(l_draw_node->widget->has_attributes(a_text)) {
                                  l_blit_sx = l_draw_node->widget->get_sx() * s_charset_sx;
                                  l_blit_sy = l_draw_node->widget->get_sy() * s_charset_sy;
                                  if((l_blit_ptr.get_sx() != l_blit_sx) || (l_blit_ptr.get_sy() != l_blit_sy)) {
                                      l_blit_ptr.reset(m_format, l_blit_sx, l_blit_sy);
                                  } else
                                      l_blit_ptr.reset(m_format, l_blit_sx, l_blit_sy);
                              }
                          }
                      }
                  } else
                  if((m_attributes & a_use_fbr) == 0) {
                      l_blit_px = l_draw_px - l_root_px;
                      l_blit_py = l_draw_py - l_root_py;
                  }

                  // finally render the draw node
                  auto& l_blit_ptr = l_data_node->rbo;
                  if(l_draw_node->widget->has_attributes(a_text)) {
                      auto& l_tile_ptr = l_data_node->cbo;
                      if constexpr (scene_partial_redraw == 0) {
                      }
                  } else
                  if(l_draw_node->widget->has_attributes(a_raster)) {
                      if(l_draw_node->widget->has_attributes(a_vector)) {
                      }
                  }
              }
          }
          l_draw_node++;
      }

      sds_pop();

      //         // finally render the draw node
      //         if(l_data_node) {
      //             sfx::widget::context_t l_local_context;
      //             gfx::surface_ptr&      l_surface_ptr = l_data_node->surface;
      //             if(l_surface_ptr == true) {
      //                 std::uint16_t l_draw_sx = l_draw_node->geometry.get_sx() * s_charset_sy;
      //                 std::uint16_t l_draw_sy = l_draw_node->geometry.get_sy() * s_charset_sy;
      //                 //gfx::blit_ptr l_blit_ptr(l_surface_ptr, l_blit_px, l_blit_py, l_draw_sx, l_draw_sy);
      //                 if(true) {
      //                     blt_save(l_local_context);
      //                     if(l_draw_node->widget->has_attributes(a_active)) {
      //                         std::int16_t  l_widget_px = l_draw_node->geometry.get_px();
      //                         std::int16_t  l_widget_py = l_draw_node->geometry.get_py();
      //                         l_draw_node->widget->get_local_offset(l_widget_px, l_widget_py);
      //                         //fbr_render_window(l_blit_ptr, l_draw_node->widget, l_widget_px, l_widget_py);
      //                     } else
      //                     if(l_draw_node->widget->has_attributes(a_raster)) {
      //                         if(l_draw_node->widget->has_attributes(a_vector)) {
      //                         }
      //                     } else
      //                     if(l_draw_node->widget->has_attributes(a_opaque)) {
      //                         //fbr_fill(l_blit_ptr, l_draw_node->widget);
      //                     }
      //                     blt_restore(l_local_context);
      //                 }
      //             } else
      //                 l_fail_ctr++;
      //         } else
      //             l_fail_ctr++;

      // while(l_draw_node < l_draw_tail) {
      //     if(l_draw_node->widget) {
      //         // surface coordinates
      //         std::int16_t l_blit_px;
      //         std::int16_t l_blit_py;
      //         // draw node graphics coordinates
      //         std::int16_t l_draw_px = l_draw_node->geometry.get_px() * s_charset_sx;
      //         std::int16_t l_draw_py = l_draw_node->geometry.get_py() * s_charset_sy;
      //         // if running in cached mode - find the appropriate render node for the
      //         // widget that we are rendering
      //         if((m_attributes & a_cache) == a_cache) {
      //             l_data_node = fbr_find(l_draw_node->widget, l_data_node);
      //             // setup the rendering surface and update the offsets
      //             // if(l_data_node) {
      //             //     std::int16_t      l_blit_sx;
      //             //     std::int16_t      l_blit_sy;
      //             //     // gfx::surface_ptr& l_surface_ptr = l_data_node->surface;
      //             //     if(l_data_node->widget != this) {
      //             //         if(l_data_node->widget == l_draw_node->widget) {
      //             //             l_blit_px = 0;
      //             //             l_blit_py = 0;
      //             //             l_blit_sx = l_data_node->widget->get_sx() * s_charset_sx;
      //             //             l_blit_sy = l_data_node->widget->get_sx() * s_charset_sx;
      //             //             if(l_data_node->widget->has_attributes(a_active | a_opaque)) {
      //             //                 if(l_surface_ptr == true) {
      //             //                     if((l_blit_sx != l_surface_ptr.get_sx()) || (l_blit_sy != l_surface_ptr.get_sy())) {
      //             //                         l_surface_ptr = fbr_make_surface(l_surface_ptr, m_format, l_blit_sx, l_blit_sy);
      //             //                     }
      //             //                 } else
      //             //                 if(l_surface_ptr == false) {
      //             //                     l_surface_ptr = fbr_make_surface(l_surface_ptr, m_format, l_blit_sx, l_blit_sy);
      //             //                 }
      //             //             }
      //             //         }
      //             //     }
      //             // }
      //         } else
      //         if((m_attributes & a_cache) == 0) {
      //             l_blit_px = l_draw_px - l_root_px;
      //             l_blit_py = l_draw_py - l_root_py;
      //         }

      //         // finally render the draw node
      //         if(l_data_node) {
      //             sfx::widget::context_t l_local_context;
      //             gfx::surface_ptr&      l_surface_ptr = l_data_node->surface;
      //             if(l_surface_ptr == true) {
      //                 std::uint16_t l_draw_sx = l_draw_node->geometry.get_sx() * s_charset_sy;
      //                 std::uint16_t l_draw_sy = l_draw_node->geometry.get_sy() * s_charset_sy;
      //                 //gfx::blit_ptr l_blit_ptr(l_surface_ptr, l_blit_px, l_blit_py, l_draw_sx, l_draw_sy);
      //                 if(true) {
      //                     blt_save(l_local_context);
      //                     if(l_draw_node->widget->has_attributes(a_active)) {
      //                         std::int16_t  l_widget_px = l_draw_node->geometry.get_px();
      //                         std::int16_t  l_widget_py = l_draw_node->geometry.get_py();
      //                         l_draw_node->widget->get_local_offset(l_widget_px, l_widget_py);
      //                         //fbr_render_window(l_blit_ptr, l_draw_node->widget, l_widget_px, l_widget_py);
      //                     } else
      //                     if(l_draw_node->widget->has_attributes(a_raster)) {
      //                         if(l_draw_node->widget->has_attributes(a_vector)) {
      //                         }
      //                     } else
      //                     if(l_draw_node->widget->has_attributes(a_opaque)) {
      //                         //fbr_fill(l_blit_ptr, l_draw_node->widget);
      //                     }
      //                     blt_restore(l_local_context);
      //                 }
      //             } else
      //                 l_fail_ctr++;
      //         } else
      //             l_fail_ctr++;
      //     }
      //     l_draw_node++;
      // }
      return l_fail_ctr == 0;
}

void  scene::clear_draw_list() noexcept
{
      m_draw_list.clear();
}

bool  scene::sync_tree(sfx::widget* widget, float dt) noexcept
{
      bool l_result = false;
      if(widget->is_visible()) {
          if(auto l_widget_iter = widget->get_widget(0); l_widget_iter != nullptr) {
              while(l_widget_iter) {
                  if(sync_tree(l_widget_iter, dt)) {
                      l_result |= true;
                  }
                  l_widget_iter = l_widget_iter->get_sibling(0);
              }
          }
          if(auto l_widget_sync = widget->sync(dt); l_widget_sync == true) {
              l_result |= true;
          }
      }
      return l_result;
}

int   scene::get_charset_sx() const noexcept
{
      return m_charset_sx;
}

int   scene::get_charset_sy() const noexcept
{
      return m_charset_sy;
}

void  scene::set_viewport_position(int16_t px, uint16_t py) noexcept
{
      if(px != get_px()) {
          if(py != get_py()) {
              int l_px0 = px;
              int l_px1 = px + get_sx();
              int l_py0 = py;
              int l_py1 = py + get_sy();
              set_geometry(l_px0, l_py0, l_px1, l_py1);
              if(bool l_ready = m_flags & f_ready; l_ready == true) {
                  if(bool l_valid =(l_px0 < l_px1) && (l_py0 < l_py1); l_valid == false) {
                      suspend();
                  }
              }
          }
      }
}

void  scene::set_viewport_size(int16_t sx, int16_t sy) noexcept
{
      if(sx != get_sx()) {
          if(sy != get_sy()) {
              int l_px0 = 0 - sx / 2;
              int l_px1 = sx - l_px0;
              int l_py0 = 0 - sx / 2;
              int l_py1 = sy - l_py0;
              set_geometry(l_px0, l_py0, l_px1, l_py1);
              if(bool l_ready = m_flags & f_ready; l_ready == true) {
                  if(bool l_valid =(l_px0 < l_px1) && (l_py0 < l_py1); l_valid == false) {
                      suspend();
                  }
              }
          }
      }
}

void  scene::set_viewport_geometry(int16_t px0, int16_t py0, int16_t px1, int16_t py1) noexcept
{
      int l_px = px0;
      int l_py = py0;
      int l_sx = px1 - px0;
      int l_sy = py1 - py0;
      if((l_px != get_px()) || (l_py != get_py())) {
          if((l_sx != get_sx()) || (l_sy != get_sy())) {
              set_geometry(px0, py0, px1, py1);
              if(bool l_ready = m_flags & f_ready; l_ready == true) {
                  if(bool l_valid =(l_sx > 0) && (l_sy > 0); l_valid == false) {
                      suspend();
                  }
              }
          }
      }
}

/* attach()
   import a new widget into the scene; new widget's parent is replaced with a pointer to the
   scene object
*/
bool  scene::attach(sfx::widget* widget, std::uint8_t) noexcept
{
      if(insert(widget) == this) {
          if constexpr (scene_reserve_cbo) {
              sds_push();
              if(sds_reserve_widget(widget, true) == false) {
                  sds_dispose_widget(widget, true);
              }
              sds_pop();
          }
          return true;
      }
      return false;
}

/* detach()
   remove a widget from the scene
*/
bool  scene::detach(sfx::widget* widget) noexcept
{
      if(remove(widget) == nullptr) {
          sds_push();
          sds_dispose_widget(widget, true);
          sds_pop();
          return true;
      }
      return false;
}

bool  scene::resume() noexcept
{
      if(m_flags & f_valid) {
          m_flags |= f_ready;
          m_flags |= f_valid;
      }
      return m_flags & f_ready;
}

std::int8_t scene::get_viewport_width() const noexcept
{
      return get_sx();
}

std::int8_t scene::get_viewport_height() const noexcept
{
      return get_sy();
}

bool  scene::suspend() noexcept
{
      if(m_flags & f_ready) {
          m_flags &= ~f_ready;
      }
      return m_flags & f_ready;
}

/* draw()
*/
void  scene::draw() noexcept
{
      if(m_flags & f_ready) {
          if((m_flags & f_geometry_dirty) == f_geometry_dirty) {
              clear_draw_list();
              if(build_draw_list()) {
                  m_flags ^= f_geometry_dirty;
              }
          }
          if((m_flags & f_geometry_dirty) == 0) {
              if((m_flags & f_contents_dirty) == f_contents_dirty) {
                  render_draw_list();
                  m_flags ^= f_contents_dirty;
              }
          }
      }
}

/* sync()
*/
bool  scene::sync(float dt) noexcept
{
      bool l_sync_result = false;
      if(m_flags & f_ready) {
          if(auto l_widget_iter = get_widget(0); l_widget_iter != nullptr) {
              sds_push();
              while(l_widget_iter) {
                  if(sync_tree(l_widget_iter, dt)) {
                      l_sync_result |= true;
                  }
                  l_widget_iter = l_widget_iter->get_sibling(0);
              }
              sds_pop();
          }
      }
      return l_sync_result;
}
__endspace_gfx
__endspace_sonar
