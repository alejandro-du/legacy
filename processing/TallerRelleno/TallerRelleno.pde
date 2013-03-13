List<PVector> vectors = new ArrayList<PVector>();
ArrayList[] et;


void setup() {
  size(800, 480);
  smooth();
  vectors.add(new PVector(width / 2 - 80, height / 2 - 80));
  vectors.add(new PVector(width / 2 - 80, height / 2  + 80));
  vectors.add(new PVector(width / 2 + 80, height / 2 + 80));
  vectors.add(new PVector(width / 2 + 80, height / 2 - 80));
  vectors.add(new PVector(width / 2 + 0, height / 2 - 140));
}


void draw() {
  background(0);
  drawShape();
  
  fill(#222222);
  stroke(#555555);
  rect(0, 0, 155, 70);

  fill(#AAAAAA);
  text("CONTROLS:\nF - Fill the shape\nLeft click - Add vertex\nRight click - Delete shape", 10, 20);
}


void mousePressed() {
  if(mouseButton == LEFT) {
    vectors.add(new PVector(mouseX, mouseY));
  } else {
    vectors.clear();
  }
}


void keyPressed() {
  if(key == 'f' || key == 'F') {
    fillShape();
  }
}


void drawShape() {
  stroke(#00FF28);
  fill(#113311);
  beginShape();
  
  for(PVector v : vectors) {
    vertex(v.x, v.y);
  }
  endShape(CLOSE);
}


void fillShape() {
  buildEdgeTable();
}


void buildEdgeTable() {
  et = new ArrayList[height];
  
  for(int l = 0; l < et.length; l++) {
    for(int e = 1; e < vectors.size(); e++) {
      if((l > vectors.get(e - 1).y && l < vectors.get(e).y) || (l > vectors.get(e).y && l < vectors.get(e - 1).y)) {
      }
    }
  }
}

