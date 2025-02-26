#include "ImageService.hpp"


std::vector<cv::Mat> loadCubeMap(const std::string& dossierImages) {
    // Noms des fichiers des faces du cube map (à adapter si nécessaire)
    std::vector<std::string> nomsFaces = {"posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"};
    std::vector<cv::Mat> cubeMapFaces;

    for (const auto& nomFace : nomsFaces) {
        std::string cheminImage = dossierImages + "/" + nomFace;
        cv::Mat image = cv::imread(cheminImage);

        if (image.empty()) {
            throw std::runtime_error("Impossible de charger l'image : " + cheminImage);
        }

        cubeMapFaces.push_back(image);
        std::cout << "Image chargée : " << cheminImage << std::endl;
    }

    return cubeMapFaces;
}

cv::Mat convertCubeMapEnEquirect(const std::vector<cv::Mat>& cubeMapFaces, int largeur, int hauteur) {
    // TODO : Implémenter la conversion cube map -> équirectangulaire
    cv::Mat equirectImage(hauteur, largeur, CV_8UC3, cv::Scalar(0, 0, 0));
    return equirectImage;
}

void saveImage(const cv::Mat& image, const std::string& cheminFichier) {
    if (!cv::imwrite(cheminFichier, image)) {
        throw std::runtime_error("Impossible de sauvegarder l'image dans le fichier : " + cheminFichier);
    }
}



