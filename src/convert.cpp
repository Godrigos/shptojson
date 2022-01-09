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

  GDALDataset *poDS = (GDALDataset *)GDALOpenEx(filePath.data(), GDAL_OF_VECTOR,
                                                NULL, NULL, NULL);
  if (poDS == NULL) {
    std::cerr << "Failed to open " << shpFilePath.filename() << "."
              << std::endl;
  }
  GDALDataset *pgjdDS =
      pgjDriver->Create(destPath.data(), 0, 0, 0, GDT_Unknown, NULL);
  if (pgjdDS == NULL) {
    std::cerr << "Unable to create " << shpFilePath.stem().string() + ".geoJSON"
              << " file." << std::endl;
  }

  GDALVectorTranslate(NULL, (GDALDatasetH)pgjdDS, 1, (GDALDatasetH *)&poDS,
                      NULL, &err);
  if (err == 0) {
    std::cerr << "Error converting file " << shpFilePath.filename() << "."
              << std::endl;
  }

  GDALClose(pgjdDS);
  GDALClose(poDS);
}