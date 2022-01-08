#include "shptojson.hpp"
#include <cpr/cpr.h>

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " "
              << "mesh name [\"BR\" or \"UFs\"]." << std::endl;
    exit(EXIT_FAILURE);
  }
  Total total{0, 0};
  setenv("CPL_ZIP_ENCODING", "UTF-8", 0);

  std::string suffix;
  std::string mesh = argv[1];
  transform(mesh.begin(), mesh.end(), mesh.begin(), ::tolower);

  if (mesh == "br") {
    suffix = "Brasil/BR/";
    total = summary(suffix);
  } else if (mesh == "ufs") {
    suffix = "UFs/";
    total = summary(suffix);
  } else {
    std::cerr << "Wrong mesh name." << '\n';
    std::cerr << "Usage: " << argv[0] << " "
              << "mesh name [\"BR\" or \"UFs\"]." << std::endl;
    exit(EXIT_FAILURE);
  }
  unsetenv("CPL_ZIP_ENCODING");
  return EXIT_SUCCESS;
}