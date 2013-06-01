#pragma once

struct Position {
  Position() {
    col = 0;
    row = 0;
  }

  Position(unsigned char col, unsigned char row) :
    col(col),
    row(row) {
  }

  bool operator== (const Position& pos) {
    return (col == pos.col && row == pos.row);
  }

  bool isValid() {
    return (1 <= col && col <= 8 && 1 <= row && row <= 8);
  }

  unsigned char col;
  unsigned char row;
};
