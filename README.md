# shptojson

A C++ version of [pySHPtoJSON](https://github.com/Godrigos/pySHPtoJSON) that do parallel conversion, making it way faster. It has a limitation of only being capable to generating GeoJSON files.

All maps are downloaded from [IBGE (Instituto Brasileiro de Geografia e Estatística)](http://www.ibge.gov.br/), the agency responsible for
statistical, geographic, cartographic, geodetic and environmental information
in Brazil and were published on 2022.

## Usage

Download the release binary and execute it as `./shptojson mesh` where mesh should be `BR` or `UFs`. Make sure that `shptojson` file has execution permission.

GeoJSON files will be generated inside `geoJSON/` directory.

## More Information

Running `./shptojson BR` will generate GeoJSON files for
Brazil and  `./shptojson UFs` for each of its states, municipalities, macro and microregions. They are located in `BR/` and `UFs/` subdirectories.

Also, several original compacted shapefiles files are stored in the `shp` directory contains these files downloaded from IBGE. If you wish you may delete this extra directory after conversion.

You might need to install TBB library (libtbb-dev on Debian/Ubuntu) for multi-core processing.
