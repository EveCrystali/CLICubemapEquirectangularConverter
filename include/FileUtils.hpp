#pragma once
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void verifyFolderExists(const std::string &folder);
size_t countFilesInFolder(const std::string &folder);
void verifyPermissions(const fs::path &destinationFolder);
void verifyCubeMapFolder(const std::string &folder,
                         const std::vector<std::string> &expectedFiles);
