#include "shptojson.hpp"
#include <gdal.h>
#include <gdal_utils.h>

void convert(const std::filesystem::path shpFilePath) {
  const char *inputDriver[2]{"ESRI Shapefile", NULL};
  const char *geoJSON[2]{"GeoJSON", NULL};
  const char *topoJSON[2]{"TopoJSON", NULL};
  int err = 1;
  std::string baseFileName = shpFilePath.stem();

  std::string outGeoJson = baseFileName + ".geoJSON";
  std::string outTopoJson = baseFileName + ".json";

  GDALDatasetH shp = GDALOpenEx(shpFilePath.string().data(), GDAL_OF_VECTOR,
                                inputDriver, NULL, NULL);
  GDALDatasetH geo =
      GDALCreate(geoJSON, outGeoJson.data(), 0, 0, 0, GDT_Unknown, NULL);
  GDALDatasetH topo =
      GDALCreate(topoJSON, outTopoJson.data(), 0, 0, 0, GDT_Unknown, NULL);

  GDALVectorTranslate(NULL, geo, 1, &shp, NULL, &err);
  if (err == 0) {
    std::cerr << "Error converting file " << shpFilePath.filename()
              << " to GeoJSON." << std::endl;
  }
  GDALVectorTranslate(NULL, topo, 1, &shp, NULL, &err);
  if (err == 0) {
    std::cerr << "Error converting file " << shpFilePath.filename()
              << " to TopoJSON." << std::endl;
  }

  GDALClose(shp);
  GDALClose(geo);
  GDALClose(topo);
}