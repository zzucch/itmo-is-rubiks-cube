#include "FileIO.h"

bool CubeIO::ReadFromFile(const std::string &filename, Cube &cube) {
  std::ifstream input_file(filename);
  if (!input_file) {
    return false;
  }
  std::string cube_string;
  std::getline(input_file, cube_string);
  cube = Cube(cube_string);
  return true;
}

bool CubeIO::WriteToFile(const std::string &filename, const Cube &cube) {
  std::ofstream output_file(filename);
  if (!output_file) {
    return false;
  }
  output_file << cube.operator std::string();
  return true;
}
