cmake_minimum_required(VERSION 3.24)
project(OOP_Labs VERSION 0.0)

set(CMAKE_CXX_STANDARD 20 REQUIRED)

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
  
  target_link_libraries(${LAB} PRIVATE ${LIBLIST})
endforeach(LAB ${LABLIST})

option(BUILD_TESTS "Enable/disable tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
