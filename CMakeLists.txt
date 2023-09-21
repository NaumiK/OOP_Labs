cmake_minimum_required(VERSION 3.24)
project(OOP_Labs VERSION 0.0)


add_subdirectory(libs)
message(STATUS "Collected libs: ${LIBLIST}")
foreach(LIB ${LIBLIST})
  target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include/${LIB}/)
endforeach(LIB ${LIBLIST})

add_subdirectory(labs)
message(STATUS "Collected labs: ${LABLIST}")
foreach(LAB ${LABLIST})
  target_include_directories(${LAB} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(${LAB} PRIVATE ${CMAKE_SOURCE_DIR}/include/${LAB}/)
endforeach(LAB ${LABLIST})

