#ifndef INC_8_FILEIO_H_
#define INC_8_FILEIO_H_

#include <fstream>
#include "Cube.h"

class CubeIO {
 public:
  static bool ReadFromFile(const std::string &filename, Cube &cube);
  static bool WriteToFile(const std::string &filename, const Cube &cube);
};

#endif //INC_8_FILEIO_H_
