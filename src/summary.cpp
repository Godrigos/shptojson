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

    confirmDownload(tokens, "./shp/BR", suffix);
    confirmConvert(tokens, suffix);

  } else if (suffix == "UFs/") {
    int count = 0;
    std::vector<std::string> tokens;

    spinner.set_option(indicators::option::MaxProgress{states.size()});

    for (int i = 0; i < states.size(); i++) {
      cpr::Response r = cpr::Get(cpr::Url{URL + suffix + states[i] + "/"});
      tokens = parser(r.text, states[i]);
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

    confirmDownload(tokens, "./shp/UFs", suffix, count);
    confirmConvert(tokens, suffix, count);
  }
  indicators::show_console_cursor(true);

  return total;
}