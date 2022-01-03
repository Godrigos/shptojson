#include "shptojson.hpp"
#include <cpr/cpr.h>

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " "
              << "mesh name [\"BR\" or \"UFs\"]." << std::endl;
    exit(EXIT_FAILURE);
  }
  Total total{0, 0};

  std::string sufix;
  std::string mesh = argv[1];
  transform(mesh.begin(), mesh.end(), mesh.begin(), ::tolower);

  if (mesh == "br") {
    sufix = "Brasil/BR/";
    total = summary(sufix);

  } else if (mesh == "ufs") {
    sufix = "UFs/";
    total = summary(sufix);
  } else {
    std::cerr << "Wrong mesh name." << '\n';
    std::cerr << "Usage: " << argv[0] << " "
              << "mesh name [\"BR\" or \"UFs\"]." << std::endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}