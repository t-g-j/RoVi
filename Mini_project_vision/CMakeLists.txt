cmake_minimum_required(VERSION 2.8.11)
project(MiniProject)
find_package(OpenCV 3 REQUIRED)

add_executable(MiniProject src/main.cpp src/visionmethods.cpp src/visionmethods.h)

target_link_libraries(MiniProject ${OpenCV_LIBS})


#cmake_minimum_required(VERSION 2.8.11)
#project(blackBox)
#find_package(OpenCV 3 REQUIRED)
#add_executable(blackBox src/blackBox.cpp)
#target_link_libraries(blackBox ${OpenCV_LIBS})
