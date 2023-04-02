add_executable(project project.cpp)
#add_executable(merge merge.cpp)
target_link_libraries(project ${PYTHON_LIBRARIES})
include_directories(${CMAKE_SOURCE_DIR}/include)
