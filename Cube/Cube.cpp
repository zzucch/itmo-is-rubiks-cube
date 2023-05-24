#include "Cube.h"

Cube::Cube() {
  InitializeBlank();
}

Cube::Cube(const std::string &string) {
  for (int i = 0; i < state_.size(); ++i) {
    switch (string[i]) {
      case 'Y':
        state_[i] = Color::Yellow;
        break;
      case 'B':
        state_[i] = Color::Blue;
        break;
      case 'R':
        state_[i] = Color::Red;
        break;
      case 'G':
        state_[i] = Color::Green;
        break;
      case 'O':
        state_[i] = Color::Orange;
        break;
      case 'W':
        state_[i] = Color::White;
        break;
    }
  }
}

void Cube::InitializeBlank() {
  for (int i = 0; i < (cube_size_ * cube_size_); i++) {
    state_[(U * face_pieces_amount_) + i] = Color::Yellow;
    state_[(L * face_pieces_amount_) + i] = Color::Blue;
    state_[(F * face_pieces_amount_) + i] = Color::Red;
    state_[(R * face_pieces_amount_) + i] = Color::Green;
    state_[(B * face_pieces_amount_) + i] = Color::Orange;
    state_[(D * face_pieces_amount_) + i] = Color::White;
  }
}

bool Cube::Solved() {
  for (int i = 0; i < face_pieces_amount_; i++) {
    if (state_[(U * face_pieces_amount_) + i] != Color::Yellow ||
        state_[(L * face_pieces_amount_) + i] != Color::Blue ||
        state_[(F * face_pieces_amount_) + i] != Color::Red ||
        state_[(R * face_pieces_amount_) + i] != Color::Green ||
        state_[(B * face_pieces_amount_) + i] != Color::Orange ||
        state_[(D * face_pieces_amount_) + i] != Color::White) {
      return false;
    }
  }
  return true;
}

constexpr char ColorToChar(Cube::Color color) {
  switch (color) {
    case Cube::Color::Yellow:
      return 'Y';
    case Cube::Color::Blue:
      return 'B';
    case Cube::Color::Red:
      return 'R';
    case Cube::Color::Green:
      return 'G';
    case Cube::Color::Orange:
      return 'O';
    case Cube::Color::White:
      return 'W';
    default:
      return '-';
  }
}

void Cube::RotateFace(Face face, Rotation rotation) {
  for (int i = 0; i < rotation; ++i) {
    std::array<Color, 54> initial_state = state_;
    std::array<int, face_pieces_amount_>
        turned_pieces_ids = {6, 3, 0, 7, 4, 1, 8, 5, 2};

    for (int j = 0; j < face_pieces_amount_; ++j) {
      state_[face * face_pieces_amount_ + j] =
          initial_state[face * face_pieces_amount_
              + turned_pieces_ids[j]];
    }

    const int adjacent_pieces_amount = 3 * 4;

    std::array<int, adjacent_pieces_amount> adjacent_face_indexes{};

    switch (face) {
      case U:
        adjacent_face_indexes =
            {F * face_pieces_amount_ + 2, F * face_pieces_amount_ + 1,
             F * face_pieces_amount_ + 0,
             L * face_pieces_amount_ + 2, L * face_pieces_amount_ + 1,
             L * face_pieces_amount_ + 0,
             B * face_pieces_amount_ + 2, B * face_pieces_amount_ + 1,
             B * face_pieces_amount_ + 0,
             R * face_pieces_amount_ + 2, R * face_pieces_amount_ + 1,
             R * face_pieces_amount_ + 0};
        break;
      case L:
        adjacent_face_indexes =
            {F * face_pieces_amount_ + 0, F * face_pieces_amount_ + 3,
             F * face_pieces_amount_ + 6,
             D * face_pieces_amount_ + 0, D * face_pieces_amount_ + 3,
             D * face_pieces_amount_ + 6,
             B * face_pieces_amount_ + 8, B * face_pieces_amount_ + 5,
             B * face_pieces_amount_ + 2,
             U * face_pieces_amount_ + 0, U * face_pieces_amount_ + 3,
             U * face_pieces_amount_ + 6};
        break;
      case F:
        adjacent_face_indexes =
            {U * face_pieces_amount_ + 6, U * face_pieces_amount_ + 7,
             U * face_pieces_amount_ + 8,
             27, 30, 33,
             47, 46, 45,
             17, 14, 11};
        break;
      case R:
        adjacent_face_indexes = {26, 23, 20,
                                 8, 5, 2,
                                 36, 39, 42,
                                 53, 50, 47};
        break;
      case B:
        adjacent_face_indexes =
            {35, 32, 29,
             U * face_pieces_amount_ + 2, U * face_pieces_amount_ + 1,
             U * face_pieces_amount_ + 0,
             9, 12, 15,
             51, 52, 53};
        break;
      case D:
        adjacent_face_indexes =
            {24, 25, 26,
             33, 34, 35,
             42, 43, 44,
             15, 16, 17};
        break;
    }

    for (int j = 0; j < adjacent_pieces_amount; ++j) {
      state_[adjacent_face_indexes[j]] =
          initial_state[adjacent_face_indexes[(j + 9)
              % adjacent_pieces_amount]];
    }
  }
}

std::ostream &operator<<(std::ostream &os, const Cube &cube) {
  const int first_and_last_offset = 10;
  const int middle_offset = 4;

  for (int i = 0; i < Cube::cube_size_; ++i) {
    os << std::string(first_and_last_offset, ' ');
    for (int j = 0; j < Cube::cube_size_; ++j) {
      os << ColorToChar(cube.state_[i * Cube::cube_size_ + j]) << ' ';
    }
    os << '\n';
  }

  const int row_length = 3 * 4;
  std::array<int, row_length>
      fourth_row_ids = {9, 10, 11, 18, 19, 20, 27, 28, 29, 36, 37, 38};
  std::array<int, row_length>
      fifth_row_ids = {12, 13, 14, 21, 22, 23, 30, 31, 32, 39, 40, 41};
  std::array<int, row_length>
      sixth_row_ids = {15, 16, 17, 24, 25, 26, 33, 34, 35, 42, 43, 44};

  os << std::string(middle_offset, ' ');
  for (int i : fourth_row_ids) {
    os << ColorToChar(cube.state_[i]) << ' ';
  }
  os << '\n' + std::string(middle_offset, ' ');

  for (int i : fifth_row_ids) {
    os << ColorToChar(cube.state_[i]) << ' ';
  }
  os << '\n' + std::string(middle_offset, ' ');

  for (int i : sixth_row_ids) {
    os << ColorToChar(cube.state_[i]) << ' ';
  }
  os << '\n';

  for (int i = 0; i < Cube::cube_size_; ++i) {
    os << std::string(first_and_last_offset, ' ');
    for (int j = 0; j < Cube::cube_size_; ++j) {
      os << ColorToChar(cube.state_[
                            (Cube::cube_size_ * Cube::cube_size_) * cube.D
                                + i * Cube::cube_size_ + j]) << ' ';
    }
    os << '\n';
  }
  os << '\n';
  return os;
}

std::string Cube::RandomScramble() {
  std::string scramble;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 12);
  const int number_of_permutations = 18 + 3 * dist(gen);
  int action;
  for (int i = 0; i < number_of_permutations; ++i) {
    action = dist(gen);
    switch (action) {
      case 1:
        scramble += "R ";
        break;
      case 2:
        scramble += "R\' ";
        break;
      case 3:
        scramble += "L ";
        break;
      case 4:
        scramble += "L\' ";
        break;
      case 5:
        scramble += "F ";
        break;
      case 6:
        scramble += "F\' ";
        break;
      case 7:
        scramble += "U ";
        break;
      case 8:
        scramble += "U\' ";
        break;
      case 9:
        scramble += "D ";
        break;
      case 10:
        scramble += "D\' ";
        break;
      case 11:
        scramble += "B ";
        break;
      case 12:
        scramble += "B\' ";
        break;
      default:
        break;
    }
  }
  Rotate(scramble);
  return scramble;
}

void Cube::Rotate(const std::string &input) {
  int i = 0;
  while (i < input.length()) {
    Face rotation_face;
    Rotation rotation_type = Clockwise;

    switch (input[i]) {
      case 'U': {
        rotation_face = U;
        break;
      }
      case 'L': {
        rotation_face = L;
        break;
      }
      case 'F': {
        rotation_face = F;
        break;
      }
      case 'R': {
        rotation_face = R;
        break;
      }
      case 'B': {
        rotation_face = B;
        break;
      }
      case 'D': {
        rotation_face = D;
        break;
      }
      default:
        return;
    }
    ++i;

    if ((input.length() - i) > 0) {
      switch (input[i]) {
        case '2':
          rotation_type = Double;
          ++i;
          break;
        case '\'':
          rotation_type = Anticlockwise;
          ++i;
          break;
        case ' ':
          break;
        default:
          throw std::invalid_argument("invalid characters");
      }
      ++i;
    }
    RotateFace(rotation_face, rotation_type);
  }
}

void Cube::RotateWithOutput(const std::string &input, std::string &output) {
  output += input;
  if (input[input.length() - 1] != ' ') {
    output += ' ';
  }
  int i = 0;
  while (i < input.length()) {
    Face rotation_face;
    Rotation rotation_type = Clockwise;

    switch (input[i]) {
      case 'U': {
        rotation_face = U;
        break;
      }
      case 'L': {
        rotation_face = L;
        break;
      }
      case 'F': {
        rotation_face = F;
        break;
      }
      case 'R': {
        rotation_face = R;
        break;
      }
      case 'B': {
        rotation_face = B;
        break;
      }
      case 'D': {
        rotation_face = D;
        break;
      }
      default:
        return;
    }
    ++i;

    if ((input.length() - i) > 0) {
      switch (input[i]) {
        case '2':
          rotation_type = Double;
          ++i;
          break;
        case '\'':
          rotation_type = Anticlockwise;
          ++i;
          break;
        case ' ':
          break;
        default:
          throw std::invalid_argument("invalid characters");
      }
      ++i;
    }
    RotateFace(rotation_face, rotation_type);
  }
}

std::string Cube::Solve() {
  std::string moves;

  if (Solved()) {
    return moves;
  }

  // WHITE CROSS
  if (!SolvedCross(D, Color::White) || !SolvedAdjacentToWhiteCross()) {
    // WHITE CROSS ON U
    while (!SolvedCross(U, Color::White)) {
      if (state_[10] == Color::White) {
        RotateWithOutput("L", moves);
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F", moves);
      } else if (state_[19] == Color::White) {
        RotateWithOutput("F", moves);
        while (state_[5] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("R\'", moves);
      } else if (state_[28] == Color::White) {
        RotateWithOutput("R\'", moves);
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F\'", moves);
      } else if (state_[37] == Color::White) {
        RotateWithOutput("B", moves);
        while (state_[3] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("L", moves);
      } else if (state_[12] == Color::White) {
        while (state_[1] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("B\'", moves);
      } else if (state_[14] == Color::White) {
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F", moves);
      } else if (state_[21] == Color::White) {
        while (state_[3] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("L\'", moves);
      } else if (state_[23] == Color::White) {
        while (state_[5] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("R", moves);
      } else if (state_[30] == Color::White) {
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F\'", moves);
      } else if (state_[R * face_pieces_amount_ + 5] == Color::White) {
        while (state_[U * face_pieces_amount_ + 1] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("B", moves);
      } else if (state_[39] == Color::White) {
        while (state_[5] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("R\'", moves);
      } else if (state_[41] == Color::White) {
        while (state_[3] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("L", moves);
      } else if (state_[16] == Color::White) {
        while (state_[3] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("L U B\'", moves);
      } else if (state_[25] == Color::White) {
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F U L\'", moves);
      } else if (state_[34] == Color::White) {
        while (state_[5] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("R U F\'", moves);
      } else if (state_[43] == Color::White) {
        while (state_[1] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("B U R\'", moves);
      } else if (state_[46] == Color::White) {
        while (state_[7] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("F2", moves);
      } else if (state_[48] == Color::White) {
        while (state_[3] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("L2", moves);
      } else if (state_[50] == Color::White) {
        while (state_[5] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("R2", moves);
      } else if (state_[52] == Color::White) {
        while (state_[1] == Color::White) {
          RotateWithOutput("U", moves);
        }
        RotateWithOutput("B2", moves);
      } else {
        throw std::logic_error("failed to solve white cross on U");
      }
    }

    // WHITE CROSS ON D
    while (!SolvedCross(D, Color::White)) {
      while (state_[7] != Color::White) {
        RotateWithOutput("U", moves);
      }
      switch (state_[19]) {
        case Color::Blue:
          RotateWithOutput("U L2", moves);
          break;
        case Color::Red:
          RotateWithOutput("F2", moves);
          break;
        case Color::Green:
          RotateWithOutput("U\' R2", moves);
          break;
        case Color::Orange:
          RotateWithOutput("U2 B2", moves);
          break;
        default:
          throw std::logic_error("failed to solve white cross on D");
      }
    }
    if (Solved()) {
      return moves;
    }
  }

  // SOLVE WHITE EDGES
  while (!SolvedWhiteEdges()) {
    if (state_[U * face_pieces_amount_ + 0] == Color::White) {
      if (state_[L * face_pieces_amount_ + 0] == Color::Blue) {
        RotateWithOutput(R"(U' F U F' U' F U F' U' F U F' U')", moves);
      } else if (state_[L * face_pieces_amount_ + 0] == Color::Red) {
        RotateWithOutput(R"(U2 R U R' U' R U R' U' R U R' U')", moves);
      } else if (state_[L * face_pieces_amount_ + 0] == Color::Green) {
        RotateWithOutput(R"(U B U B' U' B U B' U' B U B' U')", moves);
      } else if (state_[L * face_pieces_amount_ + 0] == Color::Orange) {
        RotateWithOutput(R"(L U L' U' L U L' U' L U L' U')", moves);
      }
    } else if (state_[U * face_pieces_amount_ + 2] == Color::White) {
      RotateWithOutput("U\'", moves);
    } else if (state_[U * face_pieces_amount_ + 6] == Color::White) {
      RotateWithOutput("U", moves);
    } else if (state_[U * face_pieces_amount_ + 8] == Color::White) {
      RotateWithOutput("U2", moves);
    } else if (state_[L * face_pieces_amount_ + 8] == Color::White) {
      RotateWithOutput("F U F\'", moves);
    } else if (state_[F * face_pieces_amount_ + 8] == Color::White) {
      RotateWithOutput("R U R\' U", moves);
    } else if (state_[R * face_pieces_amount_ + 8] == Color::White) {
      RotateWithOutput("B U B\' U2", moves);
    } else if (state_[B * face_pieces_amount_ + 8] == Color::White) {
      RotateWithOutput("L U L' U'", moves);
    } else if (state_[L * face_pieces_amount_ + 2] == Color::White) {
      RotateWithOutput(R"(F U F' U' F U F')", moves);
    } else if (state_[F * face_pieces_amount_ + 2] == Color::White) {
      RotateWithOutput("R U R\' U' R U R\' U", moves);
    } else if (state_[R * face_pieces_amount_ + 2] == Color::White) {
      RotateWithOutput(R"(B U B' U' B U B' U2)", moves);
    } else if (state_[B * face_pieces_amount_ + 2] == Color::White) {
      RotateWithOutput(R"(L U L' U' L U L' U')", moves);
    } else if (state_[L * face_pieces_amount_ + 6] == Color::White) {
      RotateWithOutput("L U\' L\'", moves);
    } else if (state_[F * face_pieces_amount_ + 6] == Color::White) {
      RotateWithOutput("F U\' F\' U", moves);
    } else if (state_[R * face_pieces_amount_ + 6] == Color::White) {
      RotateWithOutput("R U\' R\' U2", moves);
    } else if (state_[B * face_pieces_amount_ + 6] == Color::White) {
      RotateWithOutput(R"(B U' B' U')", moves);
    } else if (state_[L * face_pieces_amount_ + 0] == Color::White) {
      RotateWithOutput(R"(U L U' L' U L U' L')", moves);
    } else if (state_[F * face_pieces_amount_ + 0] == Color::White) {
      RotateWithOutput(R"(U F U' F' U F U' F' U)", moves);
    } else if (state_[R * face_pieces_amount_ + 0] == Color::White) {
      RotateWithOutput(R"(U R U' R' U R U' R' U2)", moves);
    } else if (state_[B * face_pieces_amount_ + 0] == Color::White) {
      RotateWithOutput(R"(U B U' B' U B U' B' U')", moves);
    } else if (state_[D * face_pieces_amount_ + 0] == Color::White
        && state_[L * face_pieces_amount_ + 8] != Color::Blue) {
      RotateWithOutput(R"(F U F' U' F U F' U' F U F')", moves);
    } else if (state_[D * face_pieces_amount_ + 2] == Color::White
        && state_[F * face_pieces_amount_ + 8] != Color::Red) {
      RotateWithOutput(R"(R U R' U' R U R' U' R U R' U)", moves);
    } else if (state_[D * face_pieces_amount_ + 6] == Color::White
        && state_[B * face_pieces_amount_ + 8] != Color::Orange) {
      RotateWithOutput(R"(L U L' U' L U L' U' L U L' U')", moves);
    } else if (state_[D * face_pieces_amount_ + 8] == Color::White
        && state_[R * face_pieces_amount_ + 8] != Color::Green) {
      RotateWithOutput(R"(B U B' U' B U B' U' B U B' U2)", moves);
    }
  }

  if (Solved()) {
    return moves;
  }

  // 2nd LAYER
  while (!SolvedSecondLayer()) {
    if (state_[U * face_pieces_amount_ + 7] != Color::Yellow
        && state_[F * face_pieces_amount_ + 1] != Color::Yellow) {
      if (state_[U * face_pieces_amount_ + 7] == Color::Green
          && state_[F * face_pieces_amount_ + 1] == Color::Red) {
        RotateWithOutput(R"(U R U' R' U' F' U F)", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Red
          && state_[F * face_pieces_amount_ + 1] == Color::Green) {
        RotateWithOutput(R"(U2 F' U F U R U' R')", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Orange
          && state_[F * face_pieces_amount_ + 1] == Color::Green) {
        RotateWithOutput(R"(B U' B' U' R' U R)", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Green
          && state_[F * face_pieces_amount_ + 1] == Color::Orange) {
        RotateWithOutput(R"(U R' U R U B U' B')", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Blue
          && state_[F * face_pieces_amount_ + 1] == Color::Orange) {
        RotateWithOutput(R"(U' L U' L' U' B' U B)", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Orange
          && state_[F * face_pieces_amount_ + 1] == Color::Blue) {
        RotateWithOutput(R"(B' U B U L U' L')", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Blue
          && state_[F * face_pieces_amount_ + 1] == Color::Red) {
        RotateWithOutput(R"(U' L' U L U F U' F')", moves);
      } else if (state_[U * face_pieces_amount_ + 7] == Color::Red
          && state_[F * face_pieces_amount_ + 1] == Color::Blue) {
        RotateWithOutput(R"(U2 F U' F' U' L' U L)", moves);
      }
    } else if (state_[U * face_pieces_amount_ + 5] != Color::Yellow
        && state_[R * face_pieces_amount_ + 1] != Color::Yellow) {
      RotateWithOutput("U", moves);
    } else if (state_[U * face_pieces_amount_ + 1] != Color::Yellow
        && state_[B * face_pieces_amount_ + 1] != Color::Yellow) {
      RotateWithOutput("U2", moves);
    } else if (state_[U * face_pieces_amount_ + 3] != Color::Yellow
        && state_[L * face_pieces_amount_ + 1] != Color::Yellow) {
      RotateWithOutput("U\'", moves);
    } else if (state_[B * face_pieces_amount_ + 5]
        != state_[B * face_pieces_amount_ + 4]
        || state_[L * face_pieces_amount_ + 3]
            != state_[L * face_pieces_amount_ + 4]) {
      RotateWithOutput(R"(B' U B U L U' L')", moves);
    } else if (state_[L * face_pieces_amount_ + 5]
        != state_[L * face_pieces_amount_ + 4]
        || state_[F * face_pieces_amount_ + 3]
            != state_[F * face_pieces_amount_ + 4]) {
      RotateWithOutput(R"(L' U L U F U' F')", moves);
    } else if (state_[F * face_pieces_amount_ + 5]
        != state_[F * face_pieces_amount_ + 4]
        || state_[R * face_pieces_amount_ + 3]
            != state_[R * face_pieces_amount_ + 4]) {
      RotateWithOutput(R"(F' U F U R U' R')", moves);
    } else if (state_[R * face_pieces_amount_ + 5]
        != state_[R * face_pieces_amount_ + 4]
        || state_[B * face_pieces_amount_ + 3]
            != state_[B * face_pieces_amount_ + 4]) {
      RotateWithOutput(R"(B U' B' U' R' U R)", moves);
    } else {
      throw std::logic_error("failed to solve 2nd layer");
    }
  }

  if (Solved()) {
    return moves;
  }

  // YELLOW CROSS
  while (!SolvedCross(U, Color::Yellow)) {
    // Assuming everything up until this point is correct,
    // only colors to be == are yellow because others can
    // be present only once.
    if (state_[1] == state_[3]) {
      RotateWithOutput(R"(F R U R' U' R U R' U' F')", moves);
    } else if (state_[3] == state_[5]) {
      RotateWithOutput(R"(F R U R' U' F')", moves);
    } else if (state_[U * face_pieces_amount_ + 1] != Color::Yellow
        && state_[U * face_pieces_amount_ + 3] != Color::Yellow
        && state_[U * face_pieces_amount_ + 5] != Color::Yellow
        && state_[U * face_pieces_amount_ + 7] != Color::Yellow) {
      RotateWithOutput(R"(F R U R' U' F' U2 F R U R' U' R U R' U' F')", moves);
    } else {
      RotateWithOutput("U", moves);
    }
  }
  while (state_[19] != Color::Red) {
    RotateWithOutput("U", moves);
  }
  if (state_[10] != Color::Blue || state_[19] != Color::Red
      || state_[28] != Color::Green || state_[37] != Color::Orange) {
    if (state_[10] == Color::Blue) {
      RotateWithOutput("L U L\' U L U2 L\' U", moves);
    } else if (state_[10] == Color::Orange) {
      if (state_[28] == Color::Green) {
        RotateWithOutput("F U F\' U F U2 F\' U", moves);
      } else {
        RotateWithOutput("U R U R\' U R U2 R\' U", moves);
      }
    } else if (state_[10] == Color::Green) {
      RotateWithOutput(R"(U' B U B' U B U2 B' U)", moves);
      if (state_[10] != Color::Blue || state_[19] != Color::Red
          || state_[28] != Color::Green || state_[37] != Color::Orange) {
        RotateWithOutput("U' R U R\' U R U2 R\' U2", moves);
      }
    }
  }

  // OLL
  while (!SolvedFace(U)) {
    while (state_[8] == Color::Yellow) {
      RotateWithOutput("U", moves);
    }
    if (state_[20] == Color::Yellow) {
      RotateWithOutput(R"(R F' R' F R F' R' F)", moves);
    } else if (state_[27] == Color::Yellow) {
      RotateWithOutput(R"(F' R F R' F' R F R')", moves);
    }
  }

  // PLL
  while (state_[19] != Color::Red) {
    RotateWithOutput("U", moves);
  }
  if (Solved()) {
    return moves;
  } else {
    int pll_tries = 5;
    while (!Solved() && pll_tries--) {
      int side_faces_amount = 4 + 1;
      while (side_faces_amount--) {
        if (state_[F * face_pieces_amount_ + 0]
            == state_[F * face_pieces_amount_ + 2]) {
          break;
        }
        RotateWithOutput("U", moves);
      }
      if (state_[F * face_pieces_amount_ + 0]
          == state_[F * face_pieces_amount_ + 2]) {
        if (state_[L * face_pieces_amount_ + 0]
            == state_[L * face_pieces_amount_ + 1]
            && state_[B * face_pieces_amount_ + 1]
                == state_[B * face_pieces_amount_ + 2]) {
          RotateWithOutput(R"(R' D2 R U R' D2 R U2 R' D2 R U R' D2 R)", moves);
        } else if (state_[B * face_pieces_amount_ + 0]
            == state_[B * face_pieces_amount_ + 1]
            && state_[R * face_pieces_amount_ + 1]
                == state_[R * face_pieces_amount_ + 2]) {
          RotateWithOutput(R"(L D2 L' U' L D2 L' U2 L D2 L' U' L D2 L')", moves);
        } else if (state_[R * face_pieces_amount_ + 0]
            == state_[R * face_pieces_amount_ + 2]) {
          RotateWithOutput(R"(R2 U2 R2 U2 R2 U R2 U2 R2 U2 R2 U')", moves);
        } else {
          throw std::logic_error("failed to do PLL");
        }
      } else if (state_[L * face_pieces_amount_ + 0]
          == state_[R * face_pieces_amount_ + 2]
          && state_[L * face_pieces_amount_ + 2]
              == state_[R * face_pieces_amount_ + 0]) {
        RotateWithOutput(R"(U R' U' R' D' R U' R' D R U R' D' R U R' D R2)",
                         moves);
      } else if (state_[F * face_pieces_amount_ + 0]
          == state_[B * face_pieces_amount_ + 2]
          && state_[F * face_pieces_amount_ + 2]
              == state_[B * face_pieces_amount_ + 0]) {
        RotateWithOutput(R"(R' U' R' D' R U' R' D R U R' D' R U R' D R2)",
                         moves);
      } else {
        throw std::logic_error("failed to PLL");
      }
      int count = 4;
      while (!Solved() && count--) {
        RotateFace(U, Clockwise);
        moves += "U ";
      }
    }
    int count = 4;
    while (!Solved() && count--) {
      RotateFace(U, Clockwise);
      moves += "U ";
    }
  }

  if (!Solved()) {
    throw std::logic_error("failed to do PLL");
  }

  return moves;
}

bool Cube::SolvedCross(Face face, Color color) {
  return (state_[(face * face_pieces_amount_) + 1] == color)
      && (state_[(face * face_pieces_amount_) + 3] == color)
      && (state_[(face * face_pieces_amount_) + 5] == color)
      && (state_[(face * face_pieces_amount_) + 7] == color);
}

bool Cube::SolvedAdjacentToWhiteCross() {
  return (state_[L * face_pieces_amount_ + 4]
      == state_[L * face_pieces_amount_ + 7])
      && (state_[F * face_pieces_amount_ + 4]
          == state_[F * face_pieces_amount_ + 7])
      && (state_[R * face_pieces_amount_ + 4]
          == state_[R * face_pieces_amount_ + 7])
      && (state_[B * face_pieces_amount_ + 4]
          == state_[B * face_pieces_amount_ + 7]);
}

bool Cube::SolvedWhiteEdges() {
  return (state_[D * face_pieces_amount_ + 0] == Color::White
      && state_[D * face_pieces_amount_ + 2] == Color::White
      && state_[D * face_pieces_amount_ + 6] == Color::White
      && state_[D * face_pieces_amount_ + 8] == Color::White)
      && (state_[L * face_pieces_amount_ + 4]
          == state_[L * face_pieces_amount_ + 6]
          && state_[F * face_pieces_amount_ + 4]
              == state_[F * face_pieces_amount_ + 6]
          && state_[R * face_pieces_amount_ + 4]
              == state_[R * face_pieces_amount_ + 6]
          && state_[B * face_pieces_amount_ + 4]
              == state_[B * face_pieces_amount_ + 6]);
}

bool Cube::SolvedSecondLayer() {
  return (state_[L * face_pieces_amount_ + 3]
      == state_[L * face_pieces_amount_ + 4]
      && state_[L * face_pieces_amount_ + 5]
          == state_[L * face_pieces_amount_ + 4])
      && (state_[F * face_pieces_amount_ + 3]
          == state_[F * face_pieces_amount_ + 4]
          && state_[F * face_pieces_amount_ + 5]
              == state_[F * face_pieces_amount_ + 4])
      && (state_[R * face_pieces_amount_ + 3]
          == state_[R * face_pieces_amount_ + 4]
          && state_[R * face_pieces_amount_ + 5]
              == state_[R * face_pieces_amount_ + 4])
      && (state_[B * face_pieces_amount_ + 3]
          == state_[B * face_pieces_amount_ + 4]
          && state_[B * face_pieces_amount_ + 5]
              == state_[B * face_pieces_amount_ + 4]);
}

bool Cube::SolvedFace(Face face) {
  for (int i = 0; i < face_pieces_amount_; ++i) {
    if (state_[face * face_pieces_amount_ + i]
        != state_[face * face_pieces_amount_ + 4]) {
      return false;
    }
  }
  return true;
}

bool Cube::IsStateCorrect() {
  std::array<Color, 54> initial = state_;
  try {
    Solve();
  } catch (const std::exception &exception) {
    state_ = initial;
    return false;
  }
  state_ = initial;
  return true;
}

Cube::operator std::string() const {
  std::string string;
  for (Color color : state_) {
    string += ColorToChar(color);
    string += ' ';
  }
  return string;
}
