import remixlab.proscene.*;

Scene scene;
Pyramid p;

public void setup() {
  size(800, 500, P3D);
  scene = new Scene(this);
  scene.setAxisIsDrawn(false);
  p = new Pyramid(scene.camera(), #4444BB, #44EE44);
}

public void draw() {
  PVector l = PVector.sub(
    new PVector(scene.camera().at().x, scene.camera().at().y, scene.camera().at().z),
    new PVector(scene.camera().position().x, scene.camera().position().y, scene.camera().position().z)
  );

  lights();
  ambientLight(0,0,0);
  directionalLight(128, 128, 128, l.x, l.y, l.z);

  p.draw();
  drawText();
}

public void drawText() {
  textMode(SCREEN);
  fill(#BBBBBB);
  textFont(createFont("FFScala", 14));
  text("" + p.getPolyCount() + " polygons rendered.", 5, height - 20);
}

