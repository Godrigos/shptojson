#include "shptojson.hpp"
#include <cpr/cpr.h>
#include <indicators/cursor_control.hpp>
#include <indicators/progress_spinner.hpp>

/*
This function lists the selected mesh number of files and total download size.
It askes the user about downloading after presenting such data. It calls the
download function if yes or ends the application if no.
*/
Total summary(std::string suffix) {

  Total total{0, 0};
  std::string ok;

  indicators::show_console_cursor(false);

  // Progress spinner
  indicators::ProgressSpinner spinner{
      indicators::option::PostfixText{"Checking download size"},
      indicators::option::SpinnerStates{
          std::vector<std::string>{"⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁"}},
      indicators::option::ForegroundColor{indicators::Color::yellow},
      indicators::option::FontStyles{
          std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};

  if (suffix == "Brasil/BR/") {
    std::vector<std::string> err;
    const std::string downloadDir = "./shp/BR";

    cpr::Response r = cpr::Get(cpr::Url{URL + suffix});
    std::vector<std::string> tokens = parser(r.text, "BR");
    spinner.set_option(indicators::option::MaxProgress{tokens.size()});
    total.files = tokens.size();

    for (int i = 0; i < tokens.size(); i++) {
      cpr::Response r = cpr::Head(cpr::Url{URL + suffix + tokens[i]});
      total.size += stof(r.header["Content-Length"]);
      spinner.tick();
    }
    std::cout << '\n';
    spinner.set_option(
        indicators::option::ForegroundColor{indicators::Color::white});
    spinner.set_option(indicators::option::PrefixText{"✔"});
    spinner.set_option(indicators::option::ShowSpinner{false});
    spinner.set_option(indicators::option::ShowPercentage{false});
    spinner.set_option(indicators::option::PostfixText{
        "BR download size: " + std::to_string(total.size / (1024 * 1024)) +
        " MiB " + "(" + std::to_string(total.files) + " files)"});
    spinner.mark_as_completed();

    while (ok != "y" && ok != "n") {
      std::cout << "Download the files? (Y/n): ";
      std::getline(std::cin, ok);
      transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
      if (ok == "y") {
        checkDir("./shp/BR");
        indicators::ProgressBar bar = progressBar(tokens.size());
        for (int i = 0; i < tokens.size(); i++) {
          std::string downStatus =
              download(tokens[i], downloadDir, URL + suffix + tokens[i]);
          if (!downStatus.empty()) {
            err.push_back(downStatus);
          } else {
            bar.tick();
          }
        }
        if (!err.empty()) {
          bar.mark_as_completed();
          std::cout << "Error downloading files:\n";
          std::for_each(err.begin(), err.end(), [](const std::string &file) {
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
    std::vector<std::string> err;
    int count = 0;
    const std::string downloadDir = "./shp/UFs";

    spinner.set_option(indicators::option::MaxProgress{states.size()});

    for (int i = 0; i < states.size(); i++) {
      cpr::Response r = cpr::Get(cpr::Url{URL + suffix + states[i] + "/"});
      std::vector<std::string> tokens = parser(r.text, states[i]);
      total.files += tokens.size();
      for (int j = 0; j < tokens.size(); j++) {
        cpr::Response r =
            cpr::Head(cpr::Url{URL + suffix + states[i] + "/" + tokens[j]});
        total.size += stof(r.header["Content-Length"]);
        count++;
      }
      spinner.tick();
    }
    std::cout << '\n';
    spinner.set_option(
        indicators::option::ForegroundColor{indicators::Color::white});
    spinner.set_option(indicators::option::PrefixText{"✔"});
    spinner.set_option(indicators::option::ShowSpinner{false});
    spinner.set_option(indicators::option::ShowPercentage{false});
    spinner.set_option(indicators::option::PostfixText{
        "UFs download size: " + std::to_string(total.size / (1024 * 1024)) +
        " MiB " + "(" + std::to_string(total.files) + " files)"});
    spinner.mark_as_completed();

    while (ok != "y" && ok != "n") {
      std::cout << "Download the files? (Y/n): ";
      std::getline(std::cin, ok);
      transform(ok.begin(), ok.end(), ok.begin(), ::tolower);
      if (ok == "y") {
        checkDir("./shp/UFs");
        indicators::ProgressBar bar = progressBar(count);
        for (int i = 0; i < states.size(); i++) {
          cpr::Response r = cpr::Get(cpr::Url{URL + suffix + states[i] + "/"});
          std::vector<std::string> tokens = parser(r.text, states[i]);
          for (int j = 0; j < tokens.size(); j++) {
            std::string downStatus =
                download(tokens[j], downloadDir,
                         URL + suffix + states[i] + "/" + tokens[j]);
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
          std::for_each(err.begin(), err.end(), [](const std::string &file) {
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
  indicators::show_console_cursor(true);

  return total;
}