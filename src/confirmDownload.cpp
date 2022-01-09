#include "shptojson.hpp"
#include <cpr/cpr.h>

void confirmDownload(std::vector<std::string> tokens, std::string downloadDir,
                     std::string suffix, int count) {
  std::string ok;
  std::vector<std::string_view> err;

  if (suffix == "Brasil/BR/") {
    while (ok != "y" && ok != "n") {
      std::cout << "Download the files? (Y/n): ";
      std::getline(std::cin, ok);
      transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
      if (ok == "y") {
        checkDir("./shp/BR");
        indicators::ProgressBar bar = progressBar(tokens.size());
        for (const std::string item : tokens) {
          std::string_view downStatus =
              download(item, downloadDir, URL + suffix + item);
          if (!downStatus.empty()) {
            err.push_back(downStatus);
          } else {
            bar.tick();
          }
        }
        if (!err.empty()) {
          bar.mark_as_completed();
          std::cout << "Error downloading files:\n";
          std::for_each(err.begin(), err.end(),
                        [](const std::string_view &file) {
                          std::cout << "\t\u2022 " << file << '\n';
                        });
        } else {
          std::cout << "All " << tokens.size()
                    << " files downloaded successfully." << std::endl;
        }
      } else if (ok == "n") {
        std::cout << "Skipping download process!" << std::endl;
      } else {
        std::cout << "Wrong option! Type \"y\" or \"n\"." << std::endl;
      }
    }
  } else if (suffix == "UFs/") {
    while (ok != "y" && ok != "n") {
      std::cout << "Download the files? (Y/n): ";
      std::getline(std::cin, ok);
      transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
      if (ok == "y") {
        checkDir("./shp/UFs");
        indicators::ProgressBar bar = progressBar(count);
        for (const std::string state : states) {
          cpr::Response r = cpr::Get(cpr::Url{URL + suffix + state + "/"});
          std::vector<std::string> tokens = parser(r.text, state);
          for (const std::string item : tokens) {
            std::string_view downStatus =
                download(item, downloadDir, URL + suffix + state + "/" + item);
            if (!downStatus.empty()) {
              err.push_back(downStatus);
            } else {
              bar.tick();
            }
          }
        }
        if (!err.empty()) {
          bar.mark_as_completed();
          std::cout << "Error downloading files:\n";
          std::for_each(err.begin(), err.end(),
                        [](const std::string_view &file) {
                          std::cout << "\t\u2022 " << file << '\n';
                        });
        } else {
          std::cout << "All " << count << " files downloaded successfully."
                    << std::endl;
        }
      } else if (ok == "n") {
        std::cout << "Skipping download process!" << std::endl;
      } else {
        std::cout << "Wrong option! Type \"y\" or \"n\"." << std::endl;
      }
    }
  }
}