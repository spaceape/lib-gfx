
set(TILE_SRC_DIR ${GFX_SRC_DIR}/tile)

set(inc
  window.h
)

add_subdirectory(palette)
add_subdirectory(font)

if(SDK)
  file(MAKE_DIRECTORY ${TILE_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${TILE_SRC_DIR}
  )
endif(SDK)
