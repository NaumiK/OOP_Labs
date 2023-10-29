set(SRCS
  main.cc

  Figure/Circle.cc
  Figure/ManhattanCircle.cc
  Figure/Ring.cc
  Figure/PictogramOfTheAncientGods.cc

  FigureGui/CircleGui.cc
  FigureGui/ManhattanCircleGui.cc
  FigureGui/RingGui.cc
  FigureGui/PictogramOfTheAncientGodsGui.cc
  )

find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(imgui CONFIG REQUIRED)

add_executable(LAB2 ${SRCS})

if(TARGET SDL2::SDL2main)
  target_link_libraries(LAB2 PRIVATE SDL2::SDL2main)
endif(TARGET SDL2::SDL2main)

target_link_libraries(LAB2 PRIVATE SDL2::SDL2)
target_link_libraries(LAB2 PRIVATE imgui::imgui)

