cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Exo_AC_C__)

# Utilisation du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les répertoires include
include_directories(include)

# Trouver OpenCV
set(OpenCV_DIR "C:/Program Files/opencv/build") # Chemin vers OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Ajouter les fichiers sources pour ImageService
set(IMAGESERVICE_SRC src/ImageService.cpp)
add_library(ImageService ${IMAGESERVICE_SRC})
target_include_directories(ImageService PRIVATE include)
target_link_libraries(ImageService ${OpenCV_LIBS})

# Ajouter les fichiers sources pour cubeMap2Equrec
set(CUBEMAP_SRC src/cubeMap2Equrec.cpp)
add_library(cubeMap2Equrec ${CUBEMAP_SRC})
target_include_directories(cubeMap2Equrec PRIVATE include)
target_link_libraries(cubeMap2Equrec ${OpenCV_LIBS})

# Ajouter l'exécutable principal
add_executable(Exo_AC_C__ main.cpp)

# Lier les bibliothèques à l'exécutable principal
target_link_libraries(Exo_AC_C__ ImageService cubeMap2Equrec ${OpenCV_LIBS})
