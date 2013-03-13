Shape currentShape;

void setup() {
  size(600, 400);
  smooth();
  strokeWeight(3);
  drawBackground();
  currentShape = new Point();
}

void draw() {
}

void keyPressed() {
  switch(key) {
    case '1':
      currentShape = new Point();
      break;
    case '2':
      currentShape = new Line();
      break;
    case '3':
      currentShape = new Ellipse();
      break;
    case '4':
      currentShape = new Circle();
      break;
    case '5':
      currentShape = new Rectangle();
      break;
    case '6':
      currentShape = new Square();
      break;
    case '7':
      currentShape = new Triangle();
      break;
  }
}

void mousePressed() {
  currentShape.init(mouseX, mouseY);
}

void mouseDragged() {
  drawBackground();
  currentShape.draw(mouseX, mouseY);
}

void drawBackground() {
  background(0xF5C525);
  text("CONTROLES:\n1: Punto\n2: Línea\n3: Elipse\n4: Círculo\n5: Rectángulo\n6: Cuadrado\n7: Triángulo", 5, 15);
}

