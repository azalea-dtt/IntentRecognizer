cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

add_library(intent)

target_sources(intent
  PRIVATE    
    fs.cpp
    csvrow.cpp
    csv.cpp
    input.cpp
  PUBLIC    
    fs.h
    csvrow.h
    csv.h
    input.h
  )



target_include_directories(intent
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )



add_executable (demo main.cpp)
target_link_libraries (demo intent)

add_compile_definitions(DATA_PATH="${PROJECT_SOURCE_DIR}/data")
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
