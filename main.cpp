#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

// Déclaration des fonctions (signatures)
void afficherUsage(const std::string &nomProgramme);
std::vector<cv::Mat> chargerCubeMap(const std::string &dossierImages);
cv::Mat convertirCubeMapEnEquirect(const std::vector<cv::Mat> &cubeMapFaces, int largeur, int hauteur);
void sauvegarderImage(const cv::Mat &image, const std::string &cheminFichier);

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
            vector<cv::Mat> cubeMapFaces = chargerCubeMap(cube_images_folder);

            // TODO : Automatic determine width and height from the images
            int width = 20480;
            int height = 10240;

            cv::Mat equirectImage = convertirCubeMapEnEquirect(cubeMapFaces, width, height);

            sauvegarderImage(equirectImage, panorama_result_folder + "/panorama_result.jpg");

            cout << "Conversion terminée. Image sauvegardée dans : " << panorama_result_folder << endl;
        }
        catch (const std::exception &e)
        {
            cerr << "Erreur : " << e.what() << endl;
            return -1;
        }

        return 0;
    }
}


