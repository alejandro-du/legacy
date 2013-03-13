public class Block extends remixlab.proscene.Frame {
  
  private Quad[] quads;
  
  public Block(Scene scene, float x, float y, float z, float size) {
    setPosition(x, y , z);
    float l = size / 2;
    
    quads = new Quad[] {
      new Quad(new PVector[] {new PVector(l, -l, l), new PVector(l, l, l), new PVector(l, l, -l), new PVector(l, -l, -l)}),
      new Quad(new PVector[] {new PVector(-l, -l, -l), new PVector(-l, l, -l), new PVector(-l, l, l), new PVector(-l, -l, l)}),
      new Quad(new PVector[] {new PVector(-l, l, -l), new PVector(l, l, -l), new PVector(l, l, l), new PVector(-l, l, l)}),
      new Quad(new PVector[] {new PVector(-l, -l, l), new PVector(l, -l, l), new PVector(l, -l, -l), new PVector(-l, -l, -l)}),
      new Quad(new PVector[] {new PVector(-l, -l, l), new PVector(-l, l, l), new PVector(l, l, l), new PVector(l, -l, l)}),
      new Quad(new PVector[] {new PVector(l, -l, -l), new PVector(l, l, -l), new PVector(-l, l, -l), new PVector(-l, -l, -l)})
    };
  }
  
  public void draw() {
    pushMatrix();
    applyTransformation(scene.pg3d);
    
    for(int i = 0; i < quads.length; i++) {
      quads[i].draw();
    }

    popMatrix();
  }
  
  public boolean pointInsideBlock(int x, int y, Camera camera, remixlab.proscene.Frame frame) {
    //applyTransformation(scene.pg3d);
    for(int i = 0; i < quads.length; i++) {
      if(quads[i].pointInsideQuad(x, y, camera, new remixlab.proscene.Frame[] {this, frame})) {
        return true;
      }
    }
    return false;
  }
  
}
