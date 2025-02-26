#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


// Déclaration des fonctions (signatures)
std::vector<cv::Mat> loadCubeMap(const std::string &dossierImages);
cv::Mat convertCubeMapEnEquirect(const std::vector<cv::Mat> &cubeMapFaces, int largeur, int hauteur);
void saveImage(const cv::Mat &image, const std::string &cheminFichier);