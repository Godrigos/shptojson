#include "shptojson.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <zip.h>

/*
This Function downloads files from IBGE database. It recieves a detination
file name its download path and the remote file link.
It first evaluate if the file already exists and it valid (not corrupted), then
it calls checkDir function to create, if needed, the directories to download
the files to. It returns an empty string if the operation is suceessful
or the name of file if it fails.
*/
std::string download(std::string filename, std::string downloadDir,
                     std::string uri) {

  int err = 0;

  zip_t *zipFile =
      zip_open((downloadDir + "/" + filename).data(), ZIP_CHECKCONS, &err);
  if (err != 0) {
    std::ofstream of(downloadDir + "/" + filename, std::ios::binary);
    cpr::Response r =
        cpr::Download(of, cpr::Url{uri}, cpr::LowSpeed(15, 3 * MIN));
    of.close();
    if (r.status_code != 200) {
      return filename;
    }
  }

  return "";
}