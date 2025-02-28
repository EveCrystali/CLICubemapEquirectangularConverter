cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Exo_AC_C__)

# Utilisation du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Répertoire des headers de votre projet
include_directories(${PROJECT_SOURCE_DIR}/include)

# Récupération automatique de tous les fichiers .cpp du dossier src
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Création de l'exécutable principal avec main.cpp et les autres sources
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Définir le chemin vers le fichier de configuration CMake d'OpenCV
set(OpenCV_DIR "C:/Program Files/opencv/build/x64/vc16/lib")
# Recherche d'OpenCV
find_package(OpenCV REQUIRED)


# Ajout des répertoires d'includes fournis par OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("C:/Program Files/opencv/build/include/opencv2")

# Liaison de l'exécutable avec les bibliothèques OpenCV trouvées
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})