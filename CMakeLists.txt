cmake_minimum_required(VERSION 3.10)

# Définition du projet
project(AtisCloud)

# Utilisation du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(AtisCloud ${SOURCES})

# Ajout du dossier include/
target_include_directories(AtisCloud PRIVATE include)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(AtisCloud ${OpenCV_LIBS})