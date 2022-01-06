#include "shptojson.hpp"
#include <gdal_utils.h>
#include <ogrsf_frmts.h>

void convert(const std::filesystem::path shpFilePath, std::string suffix) {
  std::string dir;
  int err = 1;
  std::string filePath = "/vsizip/" + shpFilePath.string();

  if (suffix == "Brasil/BR/") {
    checkDir("./BR");
    dir = "BR/";
  } else if ("UFs/") {
    checkDir("./UFs");
    dir = "UFs/";
  }
  GDALAllRegister();

  GDALDriver *pgjDriver = GetGDALDriverManager()->GetDriverByName("GeoJSON");
  if (pgjDriver == NULL) {
    std::cerr << "GeoJSON driver not available." << std::endl;
    exit(EXIT_FAILURE);
  }

  GDALDatasetH poDS =
      GDALOpenEx(filePath.data(), GDAL_OF_VECTOR, NULL, NULL, NULL);
  if (poDS == NULL) {
    std::cerr << "Failed to open " << shpFilePath.filename() << "."
              << std::endl;
  }

  GDALDataset *pgjdDS =
      pgjDriver->Create("BR_UF_2020.geoJSON", 0, 0, 0, GDT_Unknown, NULL);
  if (pgjdDS == NULL) {
    std::cerr << "Creation of output file failed." << std::endl;
  }

  GDALVectorTranslate(NULL, (GDALDatasetH)pgjdDS, 1, &poDS, NULL, &err);
  if (err == 0) {
    std::cerr << "Error converting file." << std::endl;
  }

  GDALClose(poDS);
  GDALClose(pgjdDS);
}