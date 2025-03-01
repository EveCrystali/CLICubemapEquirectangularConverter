#include "FileUtils.hpp"
#include "ImageService.hpp"
#include "LoadingAnimation.hpp"

using namespace std;

int main() {
  {

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

    std::thread loadingThread;

    try {

      string cube_images_folder;
      cout << "Entrez le dossier contenant les images (ou appuyez sur 'q' puis "
              "'entrée' pour quitter): ";
      getline(cin, cube_images_folder);
      if (cube_images_folder == "q") {
        cout << "Programme terminé." << endl;
        return 0;
      }

      string panorama_result_folder;
      cout << "Entrez le dossier de sauvegarde pour le résultat du panorama "
              "équirectangulaire (ou appuyez sur 'q' puis 'entrée' pour "
              "quitter): ";
      getline(cin, panorama_result_folder);
      if (panorama_result_folder == "q") {
        cout << "Programme terminé." << endl;
        return 0;
      }

      if (cube_images_folder.empty() || panorama_result_folder.empty()) {
        cerr << "Erreur : Les dossiers ne peuvent pas être vides." << endl;
        return -1;
      }

      // Start the loading animation
      loadingThread = thread(loadingAnimation);

      // Initial verification in order to avoid useless processing
      const vector<string> expectedFiles = {"left.jpg",   "front.jpg",
                                            "right.jpg",  "back.jpg",
                                            "bottom.jpg", "top.jpg"};
      verifyCubeMapFolder(cube_images_folder, expectedFiles);
      verifyFolderExists(panorama_result_folder);

      vector<cv::Mat> cubeMapFaces = loadCubeMap(cube_images_folder);
      cv::Mat equirectImage = convertCubeMapEnEquirect(cubeMapFaces);
      saveImage(equirectImage, panorama_result_folder + "/panorama_result.jpg");

      cout << "Conversion terminée." << endl;

      stopAnimation();
      if (loadingThread.joinable()) {
        loadingThread.join();
      }
    } catch (const std::exception &e) {
      processingDone = true;
      if (loadingThread.joinable()) {
        loadingThread.join();
      }
      // erase "En cours de traitement..."
      cout << "\r" << string(30, ' ') << "\r";
      cerr << "Echec : " << e.what() << std::endl;
      
      system("pause");
      return -1;
    }
    
    system("pause");
    return 0;
  }
}
