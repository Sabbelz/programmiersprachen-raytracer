
add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )

add_executable(main
main.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )