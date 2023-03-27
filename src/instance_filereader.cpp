#include "../include/instance_filereader.h"

#include <fstream>
#include <sstream>
#include <cassert>

InstanceFileReader::InstanceFileReader(std::string filePath) {
  assert(filePath.size() > 0);

  std::vector<std::vector<std::string>> lines;

  std::ifstream file(filePath);
  std::string line;
  while (std::getline(file, line)) {
    std::vector<std::string> tokens;
    std::istringstream ss(line);
    std::string token;
    while (ss >> token) {
      tokens.push_back(token);
    }
    lines.push_back(tokens);
  }

  const int kAmountOfPoints = std::stof(lines[0][0]);
  const int kDimensionOfPoints = std::stof(lines[1][0]);
  for (int i = 2; i < kAmountOfPoints + 2; ++i) {
    std::vector<std::variant<float, std::string>> components;
    for (int j = 0; j < kDimensionOfPoints; ++j) {
      std::variant<float, std::string> component;
      try {
        component = std::stof(lines[i][j]);
      } catch (std::invalid_argument& error) {
        component = lines[i][j];
      }
      components.push_back(component);
    }
    points_.push_back(PointBasic(components));
  }
}

InstanceFileReader::~InstanceFileReader() {}

std::vector<PointBasic> InstanceFileReader::getPoints() {
  return points_;
}
