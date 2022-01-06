#include "shptojson.hpp"
#include <ogrsf_frmts.h>

void convert(const std::filesystem::path shpFilePath, std::string suffix) {
  std::string dir;
  std::string filePath = "/vsizip/" + shpFilePath.string();

  if (suffix == "Brasil/BR/") {
    checkDir("./BR");
    dir = "BR/";
  } else if ("UFs/") {
    checkDir("./UFs");
    dir = "UFs/";
  }
  GDALAllRegister();

  GDALDataset *poDS;
  poDS = (GDALDataset *)GDALOpenEx(filePath.data(), GDAL_OF_VECTOR, NULL, NULL,
                                   NULL);
  if (poDS == NULL) {
    std::cerr << "Open " << shpFilePath.filename() << " failed." << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << poDS->GetDriverName() << std::endl;
}