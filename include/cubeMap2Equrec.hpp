#pragma once
#include <omp.h>
#include <opencv2/opencv.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

struct cart2D {
  float x;
  float y;
  int faceIndex;
};

struct cart3D {
  float x;
  float y;
  float z;
  int faceIndex;
};

enum cube_faces { X_POS, X_NEG, Y_POS, Y_NEG, Z_POS, Z_NEG };

cv::Vec2f unit3DToUnit2D(float x, float y, float z, int faceIndex);
cart3D projectX(float theta, float phi, int sign);
cart3D projectY(float theta, float phi, int sign);
cart3D projectZ(float theta, float phi, int sign);
cart2D convertEquirectUVtoUnit2D(float theta, float phi, int square_length);
