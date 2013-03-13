public class Quad {
  
  private PVector[] v;
  private color qColor;
  
  public Quad(PVector[] v, color qColor) {
    this.v = v;
    this.qColor = qColor;
  }
  
  public void draw() {
    pushStyle();
    stroke(10);
    strokeWeight(4);
    fill(qColor);
    
    beginShape();
    
    for(int i = 0; i < v.length; i++) {
      vertex(v[i].x, v[i].y, v[i].z);
    }
    
    endShape(CLOSE);
    popStyle();
  }
  
  private boolean pointInsideQuad(Camera camera) {
    PVector v1 = camera.projectedCoordinatesOf(v[0]);
    PVector v2 = camera.projectedCoordinatesOf(v[1]);
    PVector v3 = camera.projectedCoordinatesOf(v[2]);
    PVector v4 = camera.projectedCoordinatesOf(v[3]);
    
    return
      computePointPosition(mouseX, mouseY, v1.x, v1.y, v2.x, v2.y) < 0 &&
      computePointPosition(mouseX, mouseY, v2.x, v2.y, v3.x, v3.y) < 0 &&
      computePointPosition(mouseX, mouseY, v3.x, v3.y, v4.x, v4.y) < 0 &&
      computePointPosition(mouseX, mouseY, v4.x, v4.y, v1.x, v1.y) < 0;
  }
  
  private float computePointPosition(float x, float y, float x0, float y0, float x1, float y1) {
    // see "solution 3" at http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
    return (y - y0) * (x1 - x0) - (x - x0) * (y1 - y0);
  }
  
  public void setQColor(color qColor) {
    this.qColor = qColor;
  }
  
}
