set(SRCS
  main.cc
  )

find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(imgui CONFIG REQUIRED)

add_executable(test ${SRCS})


if(TARGET SDL2::SDL2main)
  target_link_libraries(test PRIVATE SDL2::SDL2main)
endif(TARGET SDL2::SDL2main)

target_link_libraries(test PRIVATE SDL2::SDL2)
target_link_libraries(test PRIVATE imgui::imgui)


