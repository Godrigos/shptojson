#include <indicators/progress_bar.hpp>

// Creates a progress bar which recieves a counter as MaxProgress.
indicators::ProgressBar progressBar(std::string_view prefix, int count) {
  return indicators::ProgressBar{
      indicators::option::BarWidth{40},
      indicators::option::Start{" |"},
      indicators::option::Fill{"█"},
      indicators::option::Lead{"█"},
      indicators::option::Remainder{"-"},
      indicators::option::End{"|"},
      indicators::option::PrefixText{prefix},
      indicators::option::ForegroundColor{indicators::Color::yellow},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      indicators::option::ShowPercentage{true},
      indicators::option::MaxProgress{count},
      indicators::option::FontStyles{
          std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
}