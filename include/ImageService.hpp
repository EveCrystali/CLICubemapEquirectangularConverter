#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

std::vector<cv::Mat> loadCubeMap(const std::string &imagesFolder);
cv::Mat convertCubeMapEnEquirect(const std::vector<cv::Mat> &cubeMapFaces);
void saveImage(const cv::Mat &image, const std::string &filePath);