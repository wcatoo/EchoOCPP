#ifndef ECHOOCPP_IO_HPP
#define ECHOOCPP_IO_HPP
#include <optional>
#include <string>
#include <filesystem>
#include <fstream>

namespace System_IO {
std::optional<std::string> readFromFile(const std::filesystem::path &tPath){
  std::string fileContent{};
  std::ifstream inputFile{tPath};
  inputFile.seekg(0, std::ios::end);
  std::streampos fileSize = inputFile.tellg();
  inputFile.seekg(0, std::ios::beg);
  fileContent.resize(static_cast<size_t>(fileSize));
  inputFile.read(&fileContent[0], fileSize);
  inputFile.close();
  if (fileContent.empty()) {
    return std::nullopt;
  }
  return fileContent;

}
inline void writeToFile(const std::string &fileContext,
                         const std::filesystem::path &tPath) {
  std::ofstream outputFile(tPath);
  if (outputFile.good()) {
    outputFile << fileContext;
    outputFile.close();
  }
}

}
#endif