#include "ImageService.hpp"

namespace fs = std::filesystem;
using namespace std;

// Checks if the folder exists and is a directory
void verifyFolderExists(const string &folder) {
  if (!fs::exists(folder) || !fs::is_directory(folder)) {
    throw runtime_error("The folder does not exist or is not a directory: " +
                        folder);
  }
}

// Returns the number of files in the folder
size_t countFilesInFolder(const string &folder) {
  return distance(fs::directory_iterator(folder), fs::directory_iterator{});
}

// Loads an image from a given path
cv::Mat loadImage(const string &imagePath) {
  if (!fs::exists(imagePath) || !fs::is_regular_file(imagePath)) {
    throw runtime_error("Missing or invalid image: " + imagePath);
  }

  cv::Mat image = cv::imread(imagePath);
  if (image.empty()) {
    throw runtime_error("Unable to load the image: " + imagePath);
  }

  cout << "Image loaded: " << imagePath << endl;
  return image;
}

// Loads the cube map using the previous functions
vector<cv::Mat> loadCubeMap(const string &imagesFolder) {
  // List of expected file names
  const vector<string> faceNames = {"left.jpg", "front.jpg",  "right.jpg",
                                    "back.jpg", "bottom.jpg", "top.jpg"};

  // Basic checks
  verifyFolderExists(imagesFolder);
  if (countFilesInFolder(imagesFolder) <= 6) {
    throw runtime_error("The folder must contain at least 6 images.");
  }

  // Loading the cube map images
  vector<cv::Mat> cubeMapFaces;
  for (const auto &face : faceNames) {
    string imagePath = imagesFolder + "/" + face;
    cubeMapFaces.push_back(loadImage(imagePath));
  }

  return cubeMapFaces;
}

cv::Mat convertCubeMapEnEquirect(const std::vector<cv::Mat> &cubeFacesList) {
  // Correspondence of the cube map faces to their positions.
  // Extract images from cube map from a single file with the following format:
  //		+----+----+----+
  //		| Y+ | X+ | Y- |
  //		+----+----+----+
  //		| X- | Z- | Z+ |
  //		+----+----+----+
  cv::Mat posY = cubeFacesList[3];
  cv::Mat posX = cubeFacesList[2];
  cv::Mat negY = cubeFacesList[0];
  cv::Mat negX = cubeFacesList[1];
  cv::Mat negZ = cubeFacesList[4];
  cv::Mat posZ = cubeFacesList[5];

  const int output_width = cubeFacesList[0].rows * 2;
  const int output_height = cubeFacesList[0].rows;
  const int square_length = output_height;

  // Placeholder image for the result
  cv::Mat destination(output_height, output_width, CV_8UC3,
                      cv::Scalar(255, 255, 255));

  auto begin = chrono::high_resolution_clock::now();

#pragma omp parallel for
  // 1. Loop through all of the pixels in the output image
  for (int j = 0; j < destination.cols; j++) {
    // #pragma omp parallel for
    for (int i = 0; i < destination.rows; i++) {
      // 2. Get the normalised u,v coordinates for the current pixel
      float U = static_cast<float>(j) / (output_width - 1); // 0..1
      float V = static_cast<float>(i) /
                (output_height - 1); // No need for 1-... as the image output
      // needs to start from the top anyway.
      // 3. Taking the normalised cartesian coordinates calculate the polar
      // coordinate for the current pixel
      float theta =
          U * 2 *
          M_PI; // M_PI is defined in math.h when _USE_MATH_DEFINES is defined
      float phi =
          V *
          M_PI; // M_PI is defined in math.h when _USE_MATH_DEFINES is defined
      // 4. calculate the 3D cartesian coordinate which has been projected to
      // a cubes face
      cart2D cart = convertEquirectUVtoUnit2D(theta, phi, square_length);

      // 5. use this pixel to extract the colour
      cv::Vec3b val;
      // clamp the values to be inside the image
      if (cart.x < 0)
        cart.x = 0;
      else if (cart.x >= square_length)
        cart.x = square_length - 1;
      if (cart.y < 0)
        cart.y = 0;
      else if (cart.y >= square_length)
        cart.y = square_length - 1;

      if (cart.faceIndex == X_POS) {
        val = posX.at<cv::Vec3b>(cart.y, cart.x);
      } else if (cart.faceIndex == X_NEG) {
        val = negX.at<cv::Vec3b>(cart.y, cart.x);
      } else if (cart.faceIndex == Y_POS) {
        val = posY.at<cv::Vec3b>(cart.y, cart.x);
      } else if (cart.faceIndex == Y_NEG) {
        val = negY.at<cv::Vec3b>(cart.y, cart.x);
      } else if (cart.faceIndex == Z_POS) {
        val = posZ.at<cv::Vec3b>(cart.y, cart.x);
      } else if (cart.faceIndex == Z_NEG) {
        val = negZ.at<cv::Vec3b>(cart.y, cart.x);
      }

      destination.at<cv::Vec3b>(i, j) = val;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - begin;

  std::cout << "Processing time: " << diff.count() << " s" << std::endl;

  return destination;
}

void saveImage(const cv::Mat &image, const std::string &filePath) {
  if (!imwrite(filePath, image)) {
    throw std::runtime_error(
        "Impossible de sauvegarder l'image dans le fichier : " + filePath);
  }
}
