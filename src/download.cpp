#include "shptojson.hpp"
#include <cpr/cpr.h>
#include <fstream>

/*
This Function downloads files from IBGE database. It recieves a detination
file name its download path and the remote file link.
It calls checkDir function to create, if needed, the directories to download
the files to. It returns an empty string if the operation is suceessful
or the name of file followed by the response status code if it fails.
*/
std::string download(std::string filename, std::string downloadDir,
                     std::string uri) {

  std::ofstream of(downloadDir + "/" + filename, std::ios::binary);

  cpr::Response r =
      cpr::Download(of, cpr::Url{uri}, cpr::LowSpeed(15, 3 * MIN));
  if (r.status_code != 200) {
    of.close();
    return filename;
  }

  of.close();

  return "";
}