public class Viewport {
  
  private final static int LEFT_CODE = 1;
  private final static int RIGHT_CODE = 2;
  private final static int BOTTOM_CODE = 4;
  private final static int TOP_CODE = 8;
  
  private int left, right, top, bottom;
  
  public Viewport(int left, int right, int top, int bottom) {
    this.left = left;
    this.right = right;
    this.top = top;
    this.bottom = bottom;
  }
  
  public void setBounds(int left, int right, int top, int bottom) {
    this.left = left >= right || left <= 0 ? this.left : left;
    this.right = right <= left || right >= width ? this.right : right;
    this.top = top >= bottom || top <= 0 ? this.top : top;
    this.bottom = bottom <= top || bottom >= height ? this.bottom : bottom;
  }
  
  public int getLeft() {
    return left;
  }
  
  public int getRight() {
    return right;
  }
  
  public int getTop() {
    return top;
  }
  
  public int getBottom() {
    return bottom;
  }
  
  public void draw() {
    noFill();
    beginShape();
    vertex(left, top);
    vertex(left, bottom);
    vertex(right, bottom);
    vertex(right, top);
    endShape(CLOSE);
  }
  
  public int getCode(int x, int y) {
    int code = 0;
    
    if(x < left) {
      code = LEFT_CODE;
    } else if(x > right) {
      code = RIGHT_CODE;
    }
    
    if(y < top) {
      code |= TOP_CODE;
    } else if(y > bottom) {
      code |= BOTTOM_CODE;
    }
    
    return code;
  }
  
  public Line clip(Line line) {
    int c1 = getCode(line.getX1(), line.getY1());
    int c2 = getCode(line.getX2(), line.getY2());
    
    if((c1 & c2) != 0) {
      return null;
    }
    
    if((c1 | c2) == 0) {
      return line;
    }
    
    int x1, y1, x2, y2, c;
    
    if(c1 != 0) {
      x1 = line.getX1();
      y1 = line.getY1();
      x2 = line.getX2();
      y2 = line.getY2();
      c = c1;
    } else {
      x1 = line.getX2();
      y1 = line.getY2();
      x2 = line.getX1();
      y2 = line.getY1();
      c = c2;
    }
    
    float m = (float) (y2 - y1) / (x2 - x1);
    
    if((c & TOP_CODE) == TOP_CODE) {
      y1 = top;
      x1 = m == 0 ? x1 : (int) ((y1 - y2) / m + x2);
    } else if((c & BOTTOM_CODE) == BOTTOM_CODE) {
      y1 = bottom;
      x1 = m == 0 ? x1 : (int) ((y1 - y2) / m + x2);
    } else if((c & RIGHT_CODE) == RIGHT_CODE) {
      x1 = right;
      y1 = m == 0 ? y1 : (int) (m * (x1 - x2) + y2);
    } else if((c & LEFT_CODE) == LEFT_CODE) {
      x1 = left;
      y1 = m == 0 ? y1 : (int) (m * (x1 - x2) + y2);
    }
    
    return clip(new Line(x1, y1, x2, y2));
  }
  
}
