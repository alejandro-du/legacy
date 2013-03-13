abstract class Algorithm {
  
  int x1, y1;
  
  abstract void draw(int x, int y);
  
  void init(int x, int y) {
    x1 = x;
    y1 = y;
  }
}


class DDA extends Algorithm {
  void draw(int x2, int y2) {
    float m = (float) (y2 - y1) / (float) (x2 - x1);
    
    if(m <= 1 && m >= -1) {
      for(float x = x1, y = y1; x <= x2; x++, y += m) {
        point(x, round(y));
      }
      for(float x = x1, y = y1; x >= x2; x--, y -= m) {
        point(x, round(y));
      }
    } else {
      m = 1 / m;
      
      for(float y = y1, x = x1; y <= y2; y++, x += m) {
        point(round(x), y);
      }
      for(float y = y1, x = x1; y >= y2; y--, x -= m) {
        point(round(x), y);
      }
    }
  }
}


class Bresenham extends Algorithm {
  void draw(int x2, int y2) {
    float m = (float) (y2 - y1) / (float) (x2 - x1);
    float e = 0;
    
    if(m <= 1 && m >= -1) {
      for(int x = x1, y = y1; x <= x2; x++) {
        point(x, y);
        e += m;
        if(abs(e) > 0.5) {
          if(y2 > y1) {
            y++;
            e--;
          } else {
            y--;
            e++;
          }
        }
      }
      
      e = 0;
      for(int x = x1, y = y1; x >= x2; x--) {
        point(x, y);
        e += m;
        if(abs(e) > 0.5) {
          if(y2 > y1) {
            y++;
            e++;
          } else {
            y--;
            e--;
          }
        }
      }
    } else {
      m = 1 / m;
      for(int y = y1, x = x1; y <= y2; y++) {
        point(x, y);
        e += m;
        if(abs(e) > 0.5) {
          if(x2 > x1) {
            x++;
            e--;
          } else {
            x--;
            e++;
          }
        }
      }
      
      e = 0;
      for(int y = y1, x = x1; y >= y2; y--) {
        point(x, y);
        e += m;
        if(abs(e) > 0.5) {
          if(x2 > x1) {
            x++;
            e++;
          } else {
            x--;
            e--;
          }
        }
      }
    }
  }
}

