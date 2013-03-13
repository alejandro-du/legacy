import remixlab.proscene.*;

Scene scene;
Block b;

public void setup() {
  size(800, 500, P3D); // window size
  scene = new Scene(this); // create a Scene instance
  //scene.setAxisIsDrawn(false); // hide axis
  scene.setGridIsDrawn(false); // hide grid
  float l = 20;
  b = new Block(l, 0, 0, 0, color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)));
}

public void draw() {
  b.draw();
}

void keyTyped() {
  if(key == 'x') {
    b.rotateXPositive();
  }
  if(key == 'y') {
    b.rotateYPositive();
  }
}
