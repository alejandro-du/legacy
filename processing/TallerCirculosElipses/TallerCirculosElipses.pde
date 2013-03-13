void setup() {
  size(800, 500);
}

void draw() {
  stroke((int) random(80, 200), (int) random(80, 200), (int) random(80, 200));
  bresCircle((int) random(screen.width), (int) random(screen.height), (int) random(200), (int) random(1, 8));
  bresEllipse((int) random(screen.width), (int) random(screen.height), (int) random(200), (int) random(200), (int) random(1, 8));
}

void bresCircle(int xc, int yc, int r, int t) {
  int y = r, d = 0;
  
  for(int x = 0; x < y; x++) {
    if(d < 0) {
      d += 2 * x + 3;
    } else {
      d += 2 * x - 2 * y + 5;
      y--;
    }
    
    for(int ty = 0; ty < t; ty++) {
      for(int tx = 0; tx < t; tx++) {
        point(xc + x + tx, yc + y + ty);
        point(xc + x + tx, yc - y + ty);
        point(xc - x + tx, yc + y + ty);
        point(xc - x + tx, yc - y + ty);
    
        point(xc + y + tx, yc + x + ty);
        point(xc + y + tx, yc - x + ty);
        point(xc - y + tx, yc + x + ty);
        point(xc - y + tx, yc - x + ty);
      }
    }
  }
}

void bresEllipse(int xc, int yc, int a, int b, int t) {
  int x = 0;
  int y = b;
  int d = b*b + a * (-b + 1/4);
  
  while(a*a * (y - 1/2) >= b*b * (x + 1)) {
    
    if(d < 0) {
      d += b*b * (2*x + 3);
    } else {
      d += b*b * (2*x + 3) + a*a * (-2*y + 3);
      y--;
    }
    
    for(int ty = 0; ty < t; ty++) {
      for(int tx = 0; tx < t; tx++) {
        point(xc + x + tx, yc + y + ty);
        point(xc + x + tx, yc - y + ty);
        point(xc - x + tx, yc + y + ty);
        point(xc - x + tx, yc - y + ty);
      }
    }
    
    x++;
  }
  
  while(y > 0) {
    
    if(d < 0) {
      d += b*b * (2*x + 2) + a*a * (-2*y + 3);
      x++;
    } else {
      d += a*a * (-2*y + 3);
    }
    
    for(int ty = 0; ty < t; ty++) {
      for(int tx = 0; tx < t; tx++) {
        point(xc + x + tx, yc + y + ty);
        point(xc + x + tx, yc - y + ty);
        point(xc - x + tx, yc + y + ty);
        point(xc - x + tx, yc - y + ty);
      }
    }
    
    y--;
  }
}
