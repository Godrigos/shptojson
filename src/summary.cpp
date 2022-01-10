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

    cpr::Response r = cpr::Get(cpr::Url{URL + suffix});
    std::vector<std::string> tokens = parser(r.text, "BR");
    spinner.set_option(indicators::option::MaxProgress{tokens.size()});
    total.files = tokens.size();

    for (std::string token : tokens) {
      cpr::Response r = cpr::Head(cpr::Url{URL + suffix + token});
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

    confirmDownload(tokens, "./shp/BR", suffix, total.files);
    confirmConvert(suffix, total.files);

  } else if (suffix == "UFs/") {
    std::vector<std::string> tokens;
    int count = 0;
    spinner.set_option(indicators::option::MaxProgress{states.size()});

    for (std::string state : states) {
      cpr::Response r = cpr::Get(cpr::Url{URL + suffix + state + "/"});
      tokens = parser(r.text, state);
      total.files += tokens.size();
      for (std::string token : tokens) {
        cpr::Response r =
            cpr::Head(cpr::Url{URL + suffix + state + "/" + token});
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

    confirmDownload(tokens, "./shp/UFs", suffix, count);
    confirmConvert(suffix, count);
  }
  indicators::show_console_cursor(true);

  return total;
}