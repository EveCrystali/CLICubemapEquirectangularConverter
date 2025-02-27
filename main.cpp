#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "ImageService.hpp"


int main()
{
    {
        using namespace std;

        cout << "Hello, World!" << endl;

        string cube_images_folder;
        cout << "Entrez le dossier contenant les images : ";
        cin >> cube_images_folder;

        string panorama_result_folder;
        cout << "Entrez le dossier pour le résultat du panorama : ";
        cin >> panorama_result_folder;

        try
        {
            vector<cv::Mat> cubeMapFaces = loadCubeMap(cube_images_folder);
            cv::Mat equirectImage = convertCubeMapEnEquirect(cubeMapFaces);
            saveImage(equirectImage, panorama_result_folder + "/panorama_result.jpg");

            cout << "Conversion terminée. Image sauvegardée dans : " << panorama_result_folder << endl;
        }
        catch (const std::exception& e)
        {
            cerr << "Erreur : " << e.what() << endl;
            return -1;
        }

        cv::waitKey();

        return 0;
    }
}
