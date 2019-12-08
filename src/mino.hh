#ifndef __MINO_HH
#define __MINO_HH

#include "color.hh"

class MinoRenderer;

class Mino {
  public:
    Mino(int x, int y, const Color& color) : color{color}, x{x}, y{y} {}

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    void moveX(int offset) { x += offset; }
    void moveY(int offset) { y += offset; }

    int getX() const { return x; }
    int getY() const { return y; }

    bool operator==(const Mino& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Mino& o) const { return x != o.x || y != o.y; }

  private:
    Color color;
    int x;
    int y;

    friend MinoRenderer;
};

#endif
