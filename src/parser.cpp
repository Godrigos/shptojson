#include <iostream>
#include <string>
#include <vector>

/*
This function parses the html response of the IBGE directory storing the
shapefiles. It extract the file names that will compose the download links.
*/
std::vector<std::string> parser(std::string html, std::string mesh) {
  std::vector<std::string> tokens;

  while (html.find("<a href=\"" + mesh) != std::string::npos) {
    std::size_t begin = html.find("<a href=\"" + mesh) + 9;
    std::size_t end = html.find(".zip\">") + 4;

    tokens.push_back(html.substr(begin, end - begin));
    html.erase(0, end);
  }

  return tokens;
}