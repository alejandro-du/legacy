public class Quad extends remixlab.proscene.Frame {
  
  private PVector[] v;
  private color qColor;
  
  public Quad(PVector[] v) {
    this.v = v;
    this.qColor = color(random(255), random(255), random(255));
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
  
  private boolean pointInsideQuad(int x, int y, Camera camera, remixlab.proscene.Frame[] frames) {
    
    PVector[] tv = new PVector[4];
    
    for(int i = 0; i < tv.length; i++) {
      tv[i] = v[i];
      
      for(int j = 0; j < frames.length; j++) {
        tv[i] = frames[j].inverseCoordinatesOf(tv[i]);
      }
      
      //tv[i] = frames[1].inverseCoordinatesOf(tv[i]);
      
      tv[i] = camera.projectedCoordinatesOf(tv[i]);
    }
    
    return
      computePointPosition(x, y, tv[0].x, tv[0].y, tv[1].x, tv[1].y) < 0 &&
      computePointPosition(x, y, tv[1].x, tv[1].y, tv[2].x, tv[2].y) < 0 &&
      computePointPosition(x, y, tv[2].x, tv[2].y, tv[3].x, tv[3].y) < 0 &&
      computePointPosition(x, y, tv[3].x, tv[3].y, tv[0].x, tv[0].y) < 0;
  }
  
  private float computePointPosition(float x, float y, float x0, float y0, float x1, float y1) {
    // see "solution 3" at http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
    return (y - y0) * (x1 - x0) - (x - x0) * (y1 - y0);
  }
  
  public void setQColor(color qColor) {
    this.qColor = qColor;
  }
  
}
