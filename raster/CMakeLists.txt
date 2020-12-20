
set(RASTER_SRC_DIR ${GFX_SRC_DIR}/raster)

set(inc
  cbo.h rbo.h
)

add_subdirectory(palette)
add_subdirectory(font)

if(SDK)
  file(MAKE_DIRECTORY ${RASTER_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${RASTER_SRC_DIR}
  )
endif(SDK)
