#include "shptojson.hpp"
#include <execution>
#include <filesystem>

void confirmConvert(std::string suffix, int count) {
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
            std::vector<std::string> filesList;
            for (auto file : std::filesystem::directory_iterator("./shp/BR/")) {
              filesList.push_back(file.path().filename());
            }
            std::for_each(
                std::execution::par_unseq, filesList.begin(), filesList.end(),
                [](const std::string &file) {
                  if (std::filesystem::exists(
                          "./geoJSON/BR/" +
                          std::filesystem::path(file).stem().string() +
                          ".geoJSON")) {
                    std::filesystem::remove(
                        "./geoJSON/BR/" +
                        std::filesystem::path(file).stem().string() +
                        ".geoJSON");
                  }
                  convert("./shp/BR/" + file, "./geoJSON/BR/");
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
            std::vector<std::string> filesList;
            for (auto file :
                 std::filesystem::directory_iterator("./shp/UFs/")) {
              filesList.push_back(file.path().filename());
            }
            std::for_each(
                std::execution::par_unseq, filesList.begin(), filesList.end(),
                [](const std::string &file) {
                  if (std::filesystem::exists(
                          "./geoJSON/UFs/" +
                          std::filesystem::path(file).stem().string() +
                          ".geoJSON")) {
                    std::filesystem::remove(
                        "./geoJSON/UFs/" +
                        std::filesystem::path(file).stem().string() +
                        ".geoJSON");
                  }
                  convert("./shp/UFs/" + file, "./geoJSON/UFs/");
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
  }
}