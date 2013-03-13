Algorithm currentAlgorithm;

void setup() {
  size(600, 400);
  //smooth();
  //strokeWeight(3);
  currentAlgorithm = new DDA();
  drawBackground();
}

void draw() {
}

void keyPressed() {
  switch(key) {
    case '1':
      currentAlgorithm = new DDA();
      drawBackground();
      break;
    case '2':
      currentAlgorithm = new Bresenham();
      drawBackground();
      break;
  }
}

void mousePressed() {
  currentAlgorithm.init(mouseX, mouseY);
}

void mouseDragged() {
  drawBackground();
  currentAlgorithm.draw(mouseX, mouseY);
}

void drawBackground() {
  background(0xF5C525);
  text("CONTROLES:\n1: DDA\n2: Bresenham", 5, 15);
  text(currentAlgorithm.getClass().getSimpleName(), 5, 380);
}

