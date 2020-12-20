set(PALETTE_SRC_DIR ${RASTER_SRC_DIR}/palette)

set(inc
)

if(SDK)
  file(MAKE_DIRECTORY ${PALETTE_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${PALETTE_SRC_DIR}
  )
endif(SDK)
