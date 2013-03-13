import remixlab.proscene.*;

Scene scene;
List<Block> blocks = new ArrayList<Block>();
Face f;

public void setup() {
  size(800, 500, P3D); // window size
  scene = new Scene(this); // create a Scene instance
  //scene.setAxisIsDrawn(false); // hide axis
  scene.setGridIsDrawn(false); // hide grid
  float l = 30;
  blocks.add(new Block(scene, 0, 0, 0, l));
  blocks.add(new Block(scene, l, 0, 0, l));
  f = new Face(scene, blocks, new PVector(0, 0, 1));
}

public void draw() {
  f.draw();
}

