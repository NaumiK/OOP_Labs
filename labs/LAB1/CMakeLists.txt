set(SRCS
  main.cc
  )

find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(imgui CONFIG REQUIRED)

add_executable(LAB1 ${SRCS})

if(TARGET SDL2::SDL2main)
  target_link_libraries(LAB1 PRIVATE SDL2::SDL2main)
endif(TARGET SDL2::SDL2main)

target_link_libraries(LAB1 PRIVATE SDL2::SDL2)
target_link_libraries(LAB1 PRIVATE imgui::imgui)

