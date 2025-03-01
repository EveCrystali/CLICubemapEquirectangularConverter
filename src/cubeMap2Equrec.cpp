#include "cubeMap2Equrec.hpp"

using namespace std;

cv::Vec2f unit3DToUnit2D(float x, float y, float z, int faceIndex) {
  float x2D, y2D;

  if (faceIndex == X_POS) {
    // X+
    x2D = y + 0.5;
    y2D = z + 0.5;
  } else if (faceIndex == X_NEG) {
    // X-
    x2D = (y * -1) + 0.5;
    y2D = z + 0.5;
  } else if (faceIndex == Y_POS) {
    // Y+
    x2D = x + 0.5;
    y2D = z + 0.5;
  } else if (faceIndex == Y_NEG) {
    // Y-
    x2D = (x * -1) + 0.5;
    y2D = z + 0.5;
  } else if (faceIndex == Z_POS) {
    // Z+
    x2D = y + 0.5;
    y2D = (x * -1) + 0.5;
  } else {
    // Z-
    x2D = y + 0.5;
    y2D = x + 0.5;
  }

  y2D = 1 - y2D;

  return cv::Vec2f(x2D, y2D);
}

cart3D projectX(float theta, float phi, float sign) {
  cart3D result{};

  result.x = sign * 0.5;
  result.faceIndex = sign > 0 ? X_POS : X_NEG;
  float rho = result.x / (cos(theta) * sin(phi));
  result.y = rho * sin(theta) * sin(phi);
  result.z = rho * cos(phi);
  return result;
}

cart3D projectY(float theta, float phi, float sign) {
  cart3D result{};

  result.y = -sign * 0.5;
  result.faceIndex = sign > 0 ? Y_POS : Y_NEG;
  float rho = result.y / (sin(theta) * sin(phi));
  result.x = rho * cos(theta) * sin(phi);
  result.z = rho * cos(phi);
  return result;
}

static cart3D projectZ(float theta, float phi, float sign, float shift) {
  cart3D result{};

  result.z = sign * 0.5;
  result.faceIndex = sign > 0 ? Z_POS : Z_NEG;
  float rho = result.z / cos(phi);
  // Add the shift
  result.x = rho * cos(theta - shift) * sin(phi);
  result.y = rho * sin(theta - shift) * sin(phi);
  return result;
}

cart2D convertEquirectUVtoUnit2D(float theta, float phi, int square_length) {
  // Calculate the unit vector
  float x = cos(theta) * sin(phi);
  float y = sin(theta) * sin(phi);
  float z = cos(phi);

  // Find the maximum value in the unit vector
  float maximum = max({abs(x), abs(y), abs(z)});
  float xx = x / maximum;
  float yy = -y / maximum;
  float zz = z / maximum;

  // Project ray to cube surface
  cart3D equirectUV;
  float shift = M_PI / 2.0; // 90 degrees shift
  if (abs(xx) > abs(yy) && abs(xx) > abs(zz)) {
    equirectUV = projectX(theta, phi, xx);
  } else if (abs(yy) > abs(zz)) {
    equirectUV = projectY(theta, phi, yy);
  } else {
    equirectUV = projectZ(theta, phi, zz, shift);
  }

  cv::Vec2f unit2D = unit3DToUnit2D(equirectUV.x, equirectUV.y, equirectUV.z,
                                    equirectUV.faceIndex);

  unit2D[0] *= square_length;
  unit2D[1] *= square_length;

  cart2D result{};
  result.x = static_cast<int>(unit2D[0]);
  result.y = static_cast<int>(unit2D[1]);
  result.faceIndex = equirectUV.faceIndex;

  return result;
}
