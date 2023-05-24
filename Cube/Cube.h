#ifndef INC_8_CUBE_H_
#define INC_8_CUBE_H_

#include <array>
#include <vector>
#include <string>
#include <random>
#include <ostream>

/*
 *          +-----+
 *          |  U  |
 *  +-----+ +-----+ +-----+ +-----+
 *  |  L  | |  F  | |  R  | |  B  |
 *  +-----+ +-----+ +-----+ +-----+
 *          |  D  |
 *          +-----+
 *
 *  U[0..8]
 *  L[9..17]
 *  F[18..26]
 *  R[27..35]
 *  B[36..44]
 *  D[45..53]
 */

class Cube {
 public:
  enum class Color {
    Yellow,
    Blue,
    Red,
    Green,
    Orange,
    White
  };

  enum Face {
    U = 0,
    L = 1,
    F = 2,
    R = 3,
    B = 4,
    D = 5
  };

  enum Rotation {
    Clockwise = 1,
    Double = 2,
    Anticlockwise = 3
  };

  Cube();
  explicit Cube(const std::string &string);
  void InitializeBlank();
  void Rotate(const std::string &input);
  std::string RandomScramble();
  bool IsStateCorrect();
  std::string Solve();
  explicit operator std::string() const;
  friend std::ostream &operator<<(std::ostream &os, const Cube &cube);

  friend constexpr char ColorToChar(Color color);
 private:
  std::array<Color, 54> state_{}; // 54 = (3 * 3) * 6
  static const int cube_size_ = 3;

  static constexpr int face_pieces_amount_ = 9;
  void RotateFace(Face face, Rotation rotation);
  bool Solved();
  bool SolvedCross(Face face, Color color);
  bool SolvedAdjacentToWhiteCross();
  bool SolvedWhiteEdges();
  bool SolvedSecondLayer();
  bool SolvedFace(Face face);
};

#endif //INC_8_CUBE_H_
