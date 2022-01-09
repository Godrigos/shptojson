#include "shptojson.hpp"
#include <execution>
#include <filesystem>

void confirmConvert(std::vector<std::string> tokens, std::string suffix,
                    int count) {
  std::string ok;

  if (suffix == "Brasil/BR/") {
    if (std::filesystem::exists("./shp/BR")) {
      if (!std::filesystem::is_empty("./shp/BR")) {
        while (ok != "y" && ok != "n") {
          std::cout << "\nConvert shapefiles? (Y/n): ";
          std::getline(std::cin, ok);
          transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
          if (ok == "y") {
            checkDir("./geoJSON/BR");
            std::for_each(
                std::execution::par_unseq, tokens.begin(), tokens.end(),
                [](const std::string &token) {
                  if (std::filesystem::exists(
                          "./geoJSON/BR/" +
                          std::filesystem::path(token).stem().string() +
                          ".geoJSON")) {
                    std::filesystem::remove(
                        "./geoJSON/BR/" +
                        std::filesystem::path(token).stem().string() +
                        ".geoJSON");
                  }
                  convert("./shp/BR/" + token, "./geoJSON/BR/");
                });
          } else if (ok == "n") {
            std::cout << "Skipping convertion process!" << std::endl;
          } else {
            std::cout << "Wrong option! Type \"y\" or \"n\"." << std::endl;
          }
        }
      } else {
        std::cout << "No shapefiles to convert!" << std::endl;
      }
    } else {
      std::cout << "No shapefiles to convert!" << std::endl;
    }
  } else if (suffix == "UFs/") {
    if (std::filesystem::exists("./shp/UFs")) {
      if (!std::filesystem::is_empty("./shp/UFs")) {
        while (ok != "y" && ok != "n") {
          std::cout << "\nConvert shapefiles? (Y/n): ";
          std::getline(std::cin, ok);
          transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
          if (ok == "y") {
            checkDir("./geoJSON/UFs");
          } else if (ok == "n") {
            std::cout << "Skipping convertion process!" << std::endl;
          } else {
            std::cout << "Wrong option! Type \"y\" or \"n\"." << std::endl;
          }
        }
      } else {
        std::cout << "No shapefiles to convert!" << std::endl;
      }
    } else {
      std::cout << "No shapefiles to convert!" << std::endl;
    }
  }
}