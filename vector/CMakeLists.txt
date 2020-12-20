
set(VECTOR_SRC_DIR ${GFX_SRC_DIR}/vector)

set(inc
  array_ptr.h buffer_ptr.h index_ptr.h texture_ptr.h shader_ptr.h program_ptr.h
)

if(SDK)
  file(MAKE_DIRECTORY ${VECTOR_SRC_DIR})
  install(
    FILES
      ${inc}
    DESTINATION
      ${VECTOR_SRC_DIR}
  )
endif(SDK)
