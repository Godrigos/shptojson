#include "shptojson.hpp"
#include <gdal_utils.h>
#include <ogrsf_frmts.h>

void convert(const std::filesystem::path shpFilePath, std::string geoFilePath) {
  int err = 1;
  std::string filePath = "/vsizip/" + shpFilePath.string();
  std::string destPath = geoFilePath + shpFilePath.stem().string() + ".geoJSON";

  GDALAllRegister();

  GDALDriver *pgjDriver = GetGDALDriverManager()->GetDriverByName("GeoJSON");
  if (pgjDriver == NULL) {
    std::cerr << "GeoJSON driver not available." << std::endl;
    exit(EXIT_FAILURE);
  }

  try {
    GDALDataset *poDS = (GDALDataset *)GDALOpenEx(
        filePath.data(), GDAL_OF_VECTOR, NULL, NULL, NULL);

    GDALDataset *pgjdDS =
        pgjDriver->Create(destPath.data(), 0, 0, 0, GDT_Unknown, NULL);

    GDALVectorTranslate(NULL, (GDALDatasetH)pgjdDS, 1, (GDALDatasetH *)&poDS,
                        NULL, &err);

    GDALClose(pgjdDS);
    GDALClose(poDS);
  } catch (std::exception &e) {
    std::cerr << std::string{e.what()} << std::endl;
  }
}