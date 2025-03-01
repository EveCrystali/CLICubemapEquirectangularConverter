#include "FileUtils.hpp"
#include <stdexcept>
#include <fstream>

using namespace std;

// Checks if the folder exists and is a directory
void verifyFolderExists(const string &folder) {
  if (!fs::exists(folder) || !fs::is_directory(folder)) {
    throw runtime_error("The folder does not exist or is not a directory: " +
                        folder);
  }
}

void verifyPermissions(const fs::path &destinationFolder) {
  fs::path testFile = destinationFolder / "temp_permission_test.txt";
  std::ofstream ofs(testFile.string());
  if (!ofs) {
    throw std::runtime_error(
        "You do not have the necessary permissions to write in the folder: " +
        destinationFolder.string());
  }
  ofs.close();
  fs::remove(testFile);
}

void verifyCubeMapFolder(const string &folder,
                         const vector<string> &expectedFiles) {
  verifyFolderExists(folder);
  for (const auto &file : expectedFiles) {
    fs::path filePath = fs::path(folder) / file;
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
      throw runtime_error("Missing or invalid cube map image: " +
                          filePath.string());
    }
  }
}
