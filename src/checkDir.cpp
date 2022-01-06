#include "shptojson.hpp"
#include <filesystem>

/*
This function recieves a path as parameter,
checks if the needed directories of the path exists
and creates them if not.
*/
void checkDir(std::string dir) {
  try {
    std::filesystem::exists(dir);
    std::filesystem::is_directory(dir);
    std::filesystem::create_directories(dir);
  } catch (std::exception &e) {
    std::cerr << std::string{e.what()} << std::endl;
    exit(EXIT_FAILURE);
  }
}