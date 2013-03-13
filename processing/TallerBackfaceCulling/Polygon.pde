public class Polygon {
  private PVector[] vertices;
  private int fcolor;
  private int scolor;
  private Camera camera;
  
  public Polygon(PVector[] vertices, int fcolor, int scolor, Camera camera) {
    if(vertices == null || vertices.length < 3) {
      throw new RuntimeException("vertices array must be a non-null array with 3 o more elements.");
    }
    this.vertices = vertices;
    this.fcolor = fcolor;
    this.scolor = scolor;
    this.camera = camera;
  }
  
  public boolean draw() {
    if(isBackface()) {
      return false;
    }
    
    fill(fcolor);
    stroke(scolor);
    drawPolygon();
    return true;
  }
  
  private void drawPolygon() {
    strokeWeight(3);
    beginShape();
    for(int i = 0; i < vertices.length; i++) {
      vertex(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    endShape(CLOSE);
  }
  
  public PVector getNormal() {
    PVector normal = PVector.sub(vertices[0], vertices[1]).cross(PVector.sub(vertices[0], vertices[2]));
    normal.normalize();
    return normal;
  }
  
  public void drawNormal(int length) {
    PVector normal = getNormal();
    normal.mult(length);
    stroke(scolor);
    strokeWeight(4);
    line(0, 0, 0, normal.x, normal.y, normal.z);
  }
  
  public boolean isBackface2() { // doesn't work with orthographic projection
    PVector n = PVector.sub(camera.position(), vertices[0]);
    return getNormal().dot(n) <= 0;
  }
  
  public boolean isBackface() {
    PVector v1 = PVector.sub(camera.projectedCoordinatesOf(vertices[0]), camera.projectedCoordinatesOf(vertices[1]));
    PVector v2 = PVector.sub(camera.projectedCoordinatesOf(vertices[1]), camera.projectedCoordinatesOf(vertices[2]));
    return v1.cross(v2).z <= 0;
  }
}

