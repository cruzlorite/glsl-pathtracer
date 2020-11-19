include_directories(${CMAKE_CURRENT_BINARY_DIR}/../)
message(${CMAKE_CURRENT_BINARY_DIR}/..)

add_library(glad STATIC glad.c)

if(UNIX AND NOT APPLE)
  # On linux we need to link dl
  target_link_libraries(glad dl)
endif()
