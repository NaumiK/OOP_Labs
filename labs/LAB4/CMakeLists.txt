set(SRCS
  main.cc

  Figure/Circle.cc
  Figure/ManhattanCircle.cc
  Figure/Ring.cc
  Figure/PictogramOfTheAncientGods.cc
  Figure/Ellipse.cc
  Figure/ManhattanEllipse.cc
  Figure/Square.cc
  Figure/Rectangle.cc

  FigureGui/CircleGui.cc
  FigureGui/ManhattanCircleGui.cc
  FigureGui/RingGui.cc
  FigureGui/PictogramOfTheAncientGodsGui.cc
  FigureGui/EllipseGui.cc
  )

find_package(SDL2 CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(imgui CONFIG REQUIRED)

find_package(SDL2_image CONFIG REQUIRED)

add_executable(LAB4 ${SRCS})

if(TARGET SDL2::SDL2main)
  target_link_libraries(LAB4 PRIVATE SDL2::SDL2main)
  target_link_libraries(LAB4 PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
endif(TARGET SDL2::SDL2main)

target_link_libraries(LAB4 PRIVATE SDL2::SDL2)
target_link_libraries(LAB4 PRIVATE imgui::imgui)

