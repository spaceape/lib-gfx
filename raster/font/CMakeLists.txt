
set(FONT_SRC_DIR ${RASTER_SRC_DIR}/font)

set(inc
)

if(SDK)
  file(MAKE_DIRECTORY ${FONT_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${FONT_SRC_DIR}
  )
endif(SDK)
