set(SRCS
  main.cc
  )

find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2 SDL2main)

add_executable(LAB1 ${SRCS})

set(LAB LAB1)

if(TARGET SDL2::SDL2main)
  target_link_libraries(${LAB} PRIVATE SDL2::SDL2main)
endif(TARGET SDL2::SDL2main)

target_link_libraries(${LAB} PRIVATE SDL2::SDL2)


