final int translationIncrement = 5;
final float rotatationIncrement = 0.1;
final float scaleFactor = 0.1;

final int MODE_DRAW = 1;
final int MODE_TRANSFORM = -1;

int mode = MODE_DRAW;

int dx, dy;
float b, sx, sy, b2, s2;

Vector2 s, st;
Vector2 r, rt;
Vector2 center;
List<Vector2> shapeVectors = new ArrayList<Vector2>();
List<Vector2> transformedVectors = new ArrayList<Vector2>();

Matrix3x3 cm = new Matrix3x3();
Matrix3x3 tm = new Matrix3x3();
Matrix3x3 rm = new Matrix3x3();
Matrix3x3 sm = new Matrix3x3();
Matrix3x3 r2m = new Matrix3x3();
Matrix3x3 s2m = new Matrix3x3();


void resetTransforms() {
  dx = 0;
  dy = 0;
  b = 0f;
  sx = 1;
  sy = 1;
  b2 = 0f;
  s2 = 1;
}


void setup() {
  size(800, 480);
  smooth();
  shapeVectors.add(new Vector2(-20, -20));
  shapeVectors.add(new Vector2(-20, 20));
  shapeVectors.add(new Vector2(20, 20));
  shapeVectors.add(new Vector2(20, -20));
  shapeVectors.add(new Vector2(0, -40));
  s = new Vector2(-50, 20);
  r = new Vector2(90, - 60);
  resetTransforms();
}


void draw() {
  background(0);

  transformShape();
  drawShape();
  
  fill(#CC0000);
  ellipse(rt.getX(), rt.getY(), 4, 4);
  fill(#0000CC);
  ellipse(st.getX(), st.getY(), 4, 4);
  fill(#00CC00);
  ellipse(center.getX(), center.getY(), 4, 4);

  fill(#222222);
  stroke(#555555);
  rect(0, height - 25, width, 24);

  if(mode == MODE_DRAW) {
    line(width / 2, 0, width / 2, height - 25);
    line(0, height / 2, width, height / 2);
    rect(0, 0, 275, 85);
    fill(#AAAAAA);
    text("M: Cambiar a modo de transformación\nClick izq: Dibujar vértice\nClick der: Eliminar todos los vértices\nShift+Click izq: Ubicar punto de rotación 2\nShift+Click der: Ubicar punto de escalamiento 2", 10, 20);
    text("Modo de dibujo - " + shapeVectors.size() + " vértices, Punto rotación 2: " + r.getX() + ", " + r.getY() + ", Punto escalamiento 2: " + s.getX() + ", " + s.getY(), 5, height - 8);
  } else if(mode == MODE_TRANSFORM) {
    rect(0, 0, 185, 125);
    fill(#AAAAAA);
    text("M: Cambiar a modo de dibujo\nX, Shift+X: Translación en X\nY, Shift+Y: Translación en Y\nR, Shift+R: Rotación\nQ, Shift+Q: Escalamiento en X\nW, Shift+W: Escalamiento en Y\nS, Shift+S: Escalamiento 2\nT, Shift+T: Rotación 2", 10, 20);
    text("Modo de transformación - Translación: " + dx + ", " + dy + ", Rotación: " + b + ", Rotación 2: " + b2 + ", Escalamiento: " + sx + ", " + sy + ", Escalamiento 2: " + s2, 5, height - 8);
  }
}


void mousePressed() {
  if(mode == MODE_DRAW) {
    if(keyPressed) {
      if(keyCode == SHIFT) {
        if(mouseButton == LEFT) {
          r = new Vector2(mouseX - width / 2, mouseY - height / 2);
        } else {
          s = new Vector2(mouseX - width / 2, mouseY - height / 2);
        }
      }
    }
    else {
      if(mouseButton == LEFT) {
        shapeVectors.add(new Vector2(mouseX - width / 2, mouseY - height / 2));
      } else {
        shapeVectors.clear();
      }
    }
  }
}


void keyPressed() {
  switch(key) {
    case 'm':
    case 'M':
      mode *= -1;
      resetTransforms();
      break;
  }
  
  if(mode == MODE_TRANSFORM) {
    switch(key) {
      case 'x':
        dx += translationIncrement;
        break;
      case 'X':
        dx -= translationIncrement;
        break;
      case 'y':
        dy += translationIncrement;
        break;
      case 'Y':
        dy -= translationIncrement;
        break;
      case 'r':
        b += rotatationIncrement;
        break;
      case 'R':
        b -= rotatationIncrement;
        break;
      case 'q':
        sx += scaleFactor;
        break;
      case 'Q':
        sx -= scaleFactor;
        break;
      case 'w':
        sy += scaleFactor;
        break;
      case 'W':
        sy -= scaleFactor;
        break;
      case 't':
        b2 += rotatationIncrement;
        break;
      case 'T':
        b2 -= rotatationIncrement;
        break;
      case 's':
        s2 += rotatationIncrement;
        break;
      case 'S':
        s2 -= rotatationIncrement;
        break;
    }
  }
}


void drawShape() {
  stroke(#00FF28);
  fill(#113311);
  beginShape();
  
  for(Vector2 v : transformedVectors) {
    vertex(v.getX(), v.getY());
  }
  endShape(CLOSE);
}


void transformShape() {
  sm.setupScaleMatrix(sx, sy);
  rm.setupRotationMatrix(b);
  tm.setupTranslationMatrix(dx, dy);
  s2m.setupScaleMatrix(s2, s2, s.getX(), s.getY());
  r2m.setupRotationMatrix(b2, r.getX(), r.getY());
  cm.setupTranslationMatrix(width / 2, height / 2);
  
  Matrix3x3 m = cm.product(r2m.product(s2m.product(tm.product(rm.product(sm)))));
  transformedVectors.clear();
  
  for(Vector2 v : shapeVectors) {
    transformedVectors.add(m.product(v));
  }
  center = m.product(new Vector2(0, 0));
  st = cm.product(r2m.product(new Vector2(s.getX(), s.getY())));
  rt = cm.product(new Vector2(r.getX(), r.getY()));
  
}

