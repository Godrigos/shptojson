#include "shptojson.hpp"
#include <gdal.h>
#include <gdal_utils.h>

void convert(char *shpFilePath) {
  const char *drivers[2]{"ESRI Shapefile", NULL};
  int err;
  GDALDatasetH shp =
      GDALOpenEx(shpFilePath, GDAL_OF_VECTOR, drivers, NULL, NULL);
  GDALVectorTranslate(NULL, NULL, 1, &shp, NULL, &err);
  GDALClose(shp);
}