#ifndef __SHPTOJSON__
#define __SHPTOJSON__

#include <filesystem>
#include <indicators/progress_bar.hpp>
#include <iostream>
#include <stdint.h>
#include <string_view>
#include <vector>

// A minute has 60 seconds
const int MIN = 60;

// Base IBGE URL to access the shapefiles
const std::string URL =
    "geoftp.ibge.gov.br/organizacao_do_territorio/malhas_territoriais/"
    "malhas_municipais/municipio_2022/";

// A vector containing the Brazilian states abbreviations
const std::vector<std::string> states{"AC", "AL", "AP", "AM", "BA", "CE", "DF",
                                      "ES", "GO", "MA", "MT", "MS", "MG", "PA",
                                      "PB", "PR", "PE", "PI", "RJ", "RN", "RS",
                                      "RO", "RR", "SC", "SP", "SE", "TO"};

// Custom structure to overload the += operator
struct Total {
  float size;
  int files;
  struct Total &operator+=(const Total &rhs) {
    size += rhs.size;
    files += rhs.files;
    return *this;
  }
};

// Functions prototypes
std::vector<std::string> parser(std::string html, std::string mesh);
Total summary(std::string suffix);
std::string download(std::string filename, std::string dir, std::string uri);
void checkDir(std::string downloadDir);
indicators::ProgressBar progressBar(std::string_view prefix, int count);
void convert(const std::filesystem::path shpFilePath, std::string geoFilePath);
void confirmDownload(std::vector<std::string> tokens, std::string downloadDir,
                     std::string suffix, int count = 0);
void confirmConvert(std::string suffix, int count = 0);

#endif
