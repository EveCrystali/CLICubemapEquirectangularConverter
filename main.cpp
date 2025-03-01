#include "ImageService.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
  {
    using namespace std;

    // Active l'UTF-8 pour la console (fonctionne sur Windows)
    system("chcp 65001");
    setlocale(LC_ALL, "fr_FR.UTF-8");

    // --- Introduction Message ---
    cout << "***************************************************" << endl;
    cout << "*    Bienvenue dans CubeMap to Equirectangular!   *" << endl;
    cout << "*                                                 *" << endl;
    cout << "* Ce programme convertit une CubeMap en un        *" << endl;
    cout << "* panorama équirectangulaire.                     *" << endl;
    cout << "*                                                 *" << endl;
    cout << "* Veuillez suivre les instructions ci-dessous :   *" << endl;
    cout << "***************************************************" << endl;
    cout << endl;
    try {

      string cube_images_folder;
      cout << "Entrez le dossier contenant les images : ";
      cin >> cube_images_folder;

      string panorama_result_folder;
      cout << "Entrez le dossier de sauvegarde pour le résultat du panorama "
              "équirectangulaire: ";
      cin >> panorama_result_folder;
      if (cube_images_folder.empty() || panorama_result_folder.empty()) {
        cerr << "Erreur : Les dossiers ne peuvent pas être vides." << endl;
        return -1;
      }

      if (cube_images_folder == "q" || panorama_result_folder == "q") {
        cout << "Programme terminé." << endl;
        return 0;
      }

      vector<cv::Mat> cubeMapFaces = loadCubeMap(cube_images_folder);
      cv::Mat equirectImage = convertCubeMapEnEquirect(cubeMapFaces);
      saveImage(equirectImage, panorama_result_folder + "/panorama_result.jpg");

      cout << "Conversion terminée. Image sauvegardée dans : "
           << panorama_result_folder << endl;

    } catch (const std::exception &e) {
      cerr << "Erreur : " << e.what() << std::endl;
      cin.ignore();
      system("pause");
      return -1;
    }
    cin.ignore();
    system("pause");
    return 0;
  }
}
