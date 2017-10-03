cmake_minimum_required(VERSION 2.8.11)
project(Ex4)
find_package(OpenCV 3 REQUIRED)

add_executable(Ex4 src/main.cpp src/visionmethods.cpp src/visionmethods.h)

target_link_libraries(Ex4 ${OpenCV_LIBS})


#cmake_minimum_required(VERSION 2.8.11)
#project(blackBox)
#find_package(OpenCV 3 REQUIRED)
#add_executable(blackBox src/blackBox.cpp)
#target_link_libraries(blackBox ${OpenCV_LIBS})
