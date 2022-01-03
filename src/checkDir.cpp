#include "shptojson.hpp"
#include <filesystem>

/*
This function recieves a path as parameter,
checks if the needed directories of the path exists
and creates them if not.
*/
void checkDir(std::string downloadDir) {
  try {
    std::filesystem::exists(downloadDir);
    std::filesystem::is_directory(downloadDir);
    std::filesystem::create_directories(downloadDir);
  } catch (std::exception &e) {
    std::cerr << std::string{e.what()} << std::endl;
    exit(EXIT_FAILURE);
  }
}