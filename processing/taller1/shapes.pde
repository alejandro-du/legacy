abstract class Shape {
  
  int x1, y1;
  
  abstract void draw(int x, int y);
  
  void init(int x, int y) {
    x1 = x;
    y1 = y;
  }
}


class Point extends Shape {
  void draw(int x, int y) {
    point(x, y);
  }
}


class Line extends Shape {
  void draw(int x, int y) {
    line(x1, y1, x, y);
  }
}


class Ellipse extends Shape {
  void draw(int x, int y) {
    int w = (x - x1);
    int h = (y - y1);
    ellipse(x1 + w / 2, y1 + h / 2, w, h);
  }
}


class Circle extends Shape {
  void draw(int x, int y) {
    int d = (int) dist(x1, y1, x, y) * 2;
    ellipse(x1, y1, d, d);
  }
}


class Rectangle extends Shape {
  void draw(int x, int y) {
    rect(x1, y1, x - x1, y - y1);
  }
}


class Square extends Shape {
  void draw(int x, int y) {
    int d = (int) dist(x1, y1, x, y);
    rect(x1 - d, y1 - d, d * 2, d * 2);
  }
}


class Triangle extends Shape {
  void draw(int x, int y) {
    triangle(x1 + (x - x1) / 2, y1, x, y, x1, y);
  }
}

