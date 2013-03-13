public class Pyramid {
  private Polygon[] polys;
  private int polyCount;
  
  public Pyramid(Camera camera, int fcolor, int scolor) {
     polys = new Polygon[] {
      new Polygon(new PVector[] {new PVector(100, 100, 0), new PVector(-100, 100, 0), new PVector(0, 0, 100)}, fcolor, scolor, camera),
      new Polygon(new PVector[] {new PVector(-100, -100, 0), new PVector(100, -100, 0), new PVector(0, 0, 100)}, fcolor, scolor, camera),
      new Polygon(new PVector[] {new PVector(100, -100, 0), new PVector(100, 100, 0), new PVector(0, 0, 100)}, fcolor, scolor, camera),
      new Polygon(new PVector[] {new PVector(-100, 100, 0), new PVector(-100, -100, 0), new PVector(0, 0, 100)}, fcolor, scolor, camera),
      new Polygon(new PVector[] {new PVector(100, 100, 0), new PVector(100, -100, 0), new PVector(-100, -100, 0), new PVector(-100, 100, 0)}, fcolor, scolor, camera)
    };
  }
  
  public void draw() {
    polyCount = 0;
    
    for(int i = 0; i < polys.length; i++) {
      polys[i].drawNormal(100);
      if(polys[i].draw()) {
        polyCount++;
      }
    }
  }
  
  public int getPolyCount() {
    return polyCount;
  }
}

