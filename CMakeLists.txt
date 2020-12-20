#gfx
#generic graphics utilities

set(GFX_SRC_DIR ${SONAR_SRC_DIR}/gfx)

set(inc
  driver.h scene.h
)

add_subdirectory(raster)
add_subdirectory(vector)

if(SDK)
  file(MAKE_DIRECTORY ${GFX_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${GFX_SRC_DIR}
  )
endif(SDK)
