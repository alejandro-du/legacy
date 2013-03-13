Viewport viewport = null;
List<Line> lines = new ArrayList<Line>();
List<Line> clippedLines = new ArrayList<Line>();
static final int INTERACTIVE_VIEWPORT_SIZE_INCREMENT = 5;
static final int AUTOMATIC_VIEWPORT_SIZE_MIN_LOOP = 10;
static final int AUTOMATIC_VIEWPORT_SIZE_MAX_LOOP = 50;
static final int INITIAL_LINE_COUNT = 100;
static final int MIN_AUTOMATIC_LINE_COUNT = 0;
static final int MAX_AUTOMATIC_LINE_COUNT = 500;
static final int INTERACTIVE_MODE = 1;
static final int AUTOMATIC_MODE = -1;
int l, r, t, b, lc = 0, rc = 0, tc = 0, bc = 0, clipped_count, discarded_count, accepted_count;
boolean adding = true;
int mode = INTERACTIVE_MODE;

public void setup()
{
  size(800, 480);
  int padding = 150;
  viewport = new Viewport(padding, width - padding, padding, height - padding);
  lines.clear();

  for(int i = 0; i < INITIAL_LINE_COUNT; i++) {
    addRandomLine();
  }
}

public void draw() {
  background(0);
  clippedLines.clear();
  Line clippedLine = null;
  clipped_count = 0;
  discarded_count = 0;
  accepted_count = 0;
  
  for(Line line : lines) {
    clippedLine = viewport.clip(line);
    
    if(clippedLine != null) {
      clippedLines.add(clippedLine);
      if(clippedLine == line) {
        accepted_count++;
      } else {
        clipped_count++;
      }
    } else {
      discarded_count++;
    }
  }

  stroke(#000065);
  for(Line line : lines) {
    line.draw();
  }
  
  stroke(#3F3FFF);
  for(Line line : clippedLines) {
    line.draw();
  }
  
  stroke(#E01010);
  viewport.draw();
  stroke(#AAAAAA);
  fill(#333333, 180);
  rect(0, height - 20, width, 20);
  fill(#AAAAAA);
  text("Modo " + (mode == INTERACTIVE_MODE ? "interactivo" : "automático") + " - Total: " + lines.size() + ", Cortadas: " + clipped_count + ", Descartadas: " + discarded_count + ", Aceptadas: " + accepted_count, 5, height - 5);
  fill(#333333, 180);
  
  if(mode == INTERACTIVE_MODE) {
    rect(0, 0, 193, 115);
    fill(#AAAAAA);
    text("M: Cambiar a modo automático\n+: Agregar línea aleatoria\n-: Eliminar líneas\nL, Shift+L: Mover arista izq\nR, Shift+R: Mover arista derecha\nT, Shift+T: Mover arista superior\nB, Shift+B: Mover arista inferior\n", 10, 20);
  } else if(mode == AUTOMATIC_MODE) {
    rect(0, 0, 185, 30);
    fill(#AAAAAA);
    text("M: Cambiar a modo interactivo", 10, 20);

    rc--;
    if(rc <= 0) {
      rc = (int) random(AUTOMATIC_VIEWPORT_SIZE_MIN_LOOP, AUTOMATIC_VIEWPORT_SIZE_MAX_LOOP);
      r = (int) random(-2, 2);
    }
    lc--;
    if(lc <= 0) {
      lc = (int) random(AUTOMATIC_VIEWPORT_SIZE_MIN_LOOP, AUTOMATIC_VIEWPORT_SIZE_MAX_LOOP);
      l = (int) random(-2, 2);
    }
    tc--;
    if(tc <= 0) {
      tc = (int) random(AUTOMATIC_VIEWPORT_SIZE_MIN_LOOP, AUTOMATIC_VIEWPORT_SIZE_MAX_LOOP);
      t = (int) random(-2, 2);
    }
    bc--;
    if(bc <= 0) {
      bc = (int) random(AUTOMATIC_VIEWPORT_SIZE_MIN_LOOP, AUTOMATIC_VIEWPORT_SIZE_MAX_LOOP);
      b = (int) random(-2, 2);
    }
    if(viewport.getBottom() - viewport.getTop() <= 50) {
      b = 1;
      t = -1;
    }
    if(viewport.getRight() - viewport.getLeft() <= 50) {
      r = 1;
      l = -1;
    }
    
    viewport.setBounds(viewport.getLeft() + l, viewport.getRight() + r, viewport.getTop() + t, viewport.getBottom() + b);
    
    if(adding) {
      addRandomLine();
      if(lines.size() > MAX_AUTOMATIC_LINE_COUNT) {
        adding = false;
      }
    } else {
      lines.remove(0);
      if(lines.size() == MIN_AUTOMATIC_LINE_COUNT) {
        adding = true;
      }
    }
  }
  
}

public void addRandomLine() {
  lines.add(new Line((int) random(width), (int) random(height), (int) random(width), (int) random(height)));
}

public void keyPressed() {
  if(key == 'm' || key == 'M') {
    mode *= -1;
  }
  
  if(mode == INTERACTIVE_MODE) {
    switch(key) {
      case '+':
        addRandomLine();
        break;
      case '-':
        lines.clear();
        break;
      case 'l':
        viewport.setBounds(viewport.getLeft() - INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getRight(), viewport.getTop(), viewport.getBottom());
        break;
      case 'L':
        viewport.setBounds(viewport.getLeft() + INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getRight(), viewport.getTop(), viewport.getBottom());
        break;
      case 'r':
        viewport.setBounds(viewport.getLeft(), viewport.getRight() + INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getTop(), viewport.getBottom());
        break;
      case 'R':
        viewport.setBounds(viewport.getLeft(), viewport.getRight() - INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getTop(), viewport.getBottom());
        break;
      case 't':
        viewport.setBounds(viewport.getLeft(), viewport.getRight(), viewport.getTop() - INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getBottom());
        break;
      case 'T':
        viewport.setBounds(viewport.getLeft(), viewport.getRight(), viewport.getTop() + INTERACTIVE_VIEWPORT_SIZE_INCREMENT, viewport.getBottom());
        break;
      case 'b':
        viewport.setBounds(viewport.getLeft(), viewport.getRight(), viewport.getTop(), viewport.getBottom() + INTERACTIVE_VIEWPORT_SIZE_INCREMENT);
        break;
      case 'B':
        viewport.setBounds(viewport.getLeft(), viewport.getRight(), viewport.getTop(), viewport.getBottom() - INTERACTIVE_VIEWPORT_SIZE_INCREMENT);
        break;
    }
  }
}
