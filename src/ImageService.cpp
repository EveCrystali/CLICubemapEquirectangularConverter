#include "ImageService.hpp"
#include "cubeMap2Equrec.hpp"
#include <algorithm>

using namespace std;

std::vector<cv::Mat> loadCubeMap(const std::string &imagesFolder)
{
    // File names of the cube map faces (adapt if necessary)
    std::vector<std::string> faceNames = {"front.jpg", "right.jpg", "top.jpg", "bottom.jpg", "left.jpg", "back.jpg"};
    std::vector<cv::Mat> cubeMapFacesList;

    for (const auto &faceName : faceNames)
    {
        std::string imagePath = imagesFolder + "/" + faceName;
        cv::Mat image = cv::imread(imagePath);

        if (image.empty())
        {
            throw std::runtime_error("Unable to load image : " + imagePath);
        }

        cubeMapFacesList.push_back(image);
        std::cout << "Image loaded : " << imagePath << std::endl;
    }

    return cubeMapFacesList;
}

cv::Mat convertCubeMapEnEquirect(const std::vector<cv::Mat> &cubeFacesList)
{

    // Correspondance des faces de la liste à la position des faces.
    // cubeFacesList order : {"front.jpg", "right.jpg", "top.jpg", "bottom.jpg", "left.jpg", "back.jpg"};
    cv::Mat posY = cubeFacesList[2]; // top
    cv::Mat posX = cubeFacesList[0]; // front
    cv::Mat negY = cubeFacesList[3]; // bottom
    cv::Mat negX = cubeFacesList[4]; // left
    cv::Mat negZ = cubeFacesList[5]; // back
    cv::Mat posZ = cubeFacesList[1]; // right

    const int output_width = cubeFacesList[0].rows * 2;
    const int output_height = cubeFacesList[0].rows;
    const int square_length = output_height;

    // Placeholder image for the result
    cv::Mat destination(output_height, output_width, CV_8UC3,
                        cv::Scalar(255, 255, 255));

    auto begin = chrono::high_resolution_clock::now();

#pragma omp parallel for
    // 1. Loop through all of the pixels in the output image
    for (int j = 0; j < destination.cols; j++)
    {
        // #pragma omp parallel for
        for (int i = 0; i < destination.rows; i++)
        {
            // 2. Get the normalised u,v coordinates for the current pixel
            float U = (float)j / (output_width - 1); // 0..1
            float V = (float)i /
                      (output_height - 1); // No need for 1-... as the image output
                                           // needs to start from the top anyway.
            // 3. Taking the normalised cartesian coordinates calculate the polar
            // coordinate for the current pixel
            float theta = U * 2 * M_PI; // M_PI is defined in math.h when _USE_MATH_DEFINES is defined
            float phi = V * M_PI;       // M_PI is defined in math.h when _USE_MATH_DEFINES is defined
            // 4. calculate the 3D cartesian coordinate which has been projected to
            // a cubes face
            cart2D cart = convertEquirectUVtoUnit2D(theta, phi, square_length);

            // 5. use this pixel to extract the colour
            cv::Vec3b val;
            // clamp the values to be inside the image
            cart.x = std::max(0.0f, std::min((float)(square_length - 1), cart.x));
            cart.y = std::max(0.0f, std::min((float)(square_length - 1), cart.y));
            if (cart.faceIndex == X_POS)
            {
                val = posX.at<cv::Vec3b>(cart.y, cart.x);
            }
            else if (cart.faceIndex == X_NEG)
            {
                val = negX.at<cv::Vec3b>(cart.y, cart.x);
            }
            else if (cart.faceIndex == Y_POS)
            {
                val = posY.at<cv::Vec3b>(cart.y, cart.x);
            }
            else if (cart.faceIndex == Y_NEG)
            {
                val = negY.at<cv::Vec3b>(cart.y, cart.x);
            }
            else if (cart.faceIndex == Z_POS)
            {
                val = posZ.at<cv::Vec3b>(cart.y, cart.x);
            }
            else if (cart.faceIndex == Z_NEG)
            {
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

void saveImage(const cv::Mat &image, const std::string &filePath)
{
    if (!cv::imwrite(filePath, image))
    {
        throw std::runtime_error("Impossible de sauvegarder l'image dans le fichier : " + filePath);
    }
}
