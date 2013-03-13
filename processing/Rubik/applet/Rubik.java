import processing.core.*; 
import processing.xml.*; 

import remixlab.proscene.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class Rubik extends PApplet {



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

public void keyTyped() {
  if(key == 'x') {
    b.rotateXPositive();
  }
  if(key == 'y') {
    b.rotateYPositive();
  }
}
public class Block {
  
  private int NO_ROTATION = 0;
  private int POSITIVE_ROTATION = 1;
  private int NEGATIVE_ROTATION = -1;

  private Quad[] quads;
  private float x, y, z;
  private float xAngle = 0f;
  private float yAngle = 0f;
  private Float zAngle = 0f;
  private float xFinalAngle = 0f;
  private float yFinalAngle = 0f;
  private Float zFinalAngle = 0f;
  private int xRotationDirection = NO_ROTATION;
  private int yRotationDirection = NO_ROTATION;
  private Integer zRotationDirection = NO_ROTATION;
  private float rotationVel = 0.1f;
  
  public Block(float size, float x, float y, float z, int color1, int color2, int color3, int color4, int color5, int color6) {
    float l = size / 2;
    this.x = x;
    this.y = y;
    this.z = z;
    quads = new Quad[] {
      new Quad(new PVector[] {new PVector(l, -l, l), new PVector(l, l, l), new PVector(l, l, -l), new PVector(l, -l, -l)}, color1),
      new Quad(new PVector[] {new PVector(-l, -l, -l), new PVector(-l, l, -l), new PVector(-l, l, l), new PVector(-l, -l, l)}, color2),
      new Quad(new PVector[] {new PVector(-l, l, -l), new PVector(l, l, -l), new PVector(l, l, l), new PVector(-l, l, l)}, color3),
      new Quad(new PVector[] {new PVector(-l, -l, l), new PVector(l, -l, l), new PVector(l, -l, -l), new PVector(-l, -l, -l)}, color4),
      new Quad(new PVector[] {new PVector(-l, -l, l), new PVector(-l, l, l), new PVector(l, l, l), new PVector(l, -l, l)}, color5),
      new Quad(new PVector[] {new PVector(l, -l, -l), new PVector(l, l, -l), new PVector(-l, l, -l), new PVector(-l, -l, -l)}, color6)
    };
  }
  
  public void draw() {
    pushMatrix();
    
    if(isRotating()) {
      xAngle += rotationVel * xRotationDirection;
      yAngle += rotationVel * yRotationDirection;
      zAngle += rotationVel * zRotationDirection;
      xRotationDirection = updateRotationDirection(xAngle, xFinalAngle, xRotationDirection);
      yRotationDirection = updateRotationDirection(yAngle, yFinalAngle, yRotationDirection);
      zRotationDirection = updateRotationDirection(zAngle, zFinalAngle, zRotationDirection);
    }

    rotateX(xAngle);
    rotateY(yAngle);
    rotateZ(zAngle);
    translate(x, y, z);
    
    for(int i = 0; i < quads.length; i++) {
      quads[i].draw();
    }
    
    popMatrix();
  }
  
  public void translateBlock(float x, float y, float z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }
  
  public boolean isRotating() {
    return xRotationDirection != NO_ROTATION || yRotationDirection != NO_ROTATION || zRotationDirection != NO_ROTATION;
  }
  
  public void rotateXPositive() {
    if(!isRotating()) {
      xRotationDirection = POSITIVE_ROTATION;
      xFinalAngle = xAngle + PI / 2;
    }
  }
  
  public void rotateXNegative() {
    if(!isRotating()) {
      xRotationDirection = NEGATIVE_ROTATION;
      xFinalAngle = xAngle - PI / 2;
    }
  }
  
  public void rotateYPositive() {
    if(!isRotating()) {
      yRotationDirection = POSITIVE_ROTATION;
      yFinalAngle = yAngle + PI / 2;
    }
  }
  
  public void rotateYNegative() {
    if(!isRotating()) {
      yRotationDirection = NEGATIVE_ROTATION;
      yFinalAngle = yAngle - PI / 2;
    }
  }
  
  public void rotateZPositive() {
    if(!isRotating()) {
      zRotationDirection = POSITIVE_ROTATION;
      zFinalAngle = zAngle + PI / 2;
    }
  }
  
  public void rotateZNegative() {
    if(!isRotating()) {
      zRotationDirection = NEGATIVE_ROTATION;
      zFinalAngle = zAngle - PI / 2;
    }
  }
  
  private int updateRotationDirection(float angle, float finalAngle, int rotationDirection) {
    if((rotationDirection == POSITIVE_ROTATION && angle >= finalAngle) || (rotationDirection == NEGATIVE_ROTATION && angle <= finalAngle)) {
      normalizeRotationAngles();
      return NO_ROTATION;
    }
    
    return rotationDirection;
  }
  
  private void normalizeRotationAngles() {
    xAngle = getNormalizedRotationAngle(xAngle);
    yAngle = getNormalizedRotationAngle(yAngle);
    zAngle = getNormalizedRotationAngle(zAngle);
  }
  
  private float getNormalizedRotationAngle(float angle) {
    
    if(angle >= PI / 4 && angle < 3 * PI / 4) {
      return PI / 2;
    }
    if(angle >= 3 * PI / 4 && angle < 5 * PI / 4) {
      return PI;
    }
    if(angle >= 5 * PI / 4 && angle < 7 * PI / 4) {
      return 3 * PI / 2;
    }
    
    if(angle <= -PI / 4 && angle > -3 * PI / 4) {
      return 3 * PI / 2;
    }
    if(angle <= -3 * PI / 4 && angle > -5 * PI / 4) {
      return PI;
    }
    if(angle <= -5 * PI / 4 && angle > -7 * PI / 4) {
      return PI / 2;
    }
    
    return 0;
  }
  
}
public class Cube {
  
  private float size;
  private Block[][][] blocks;
  
  public Cube(float size) {
    this.size = size;
    float l = size / 3;
    blocks = new Block[3][3][3];
    
    for(int z = 0; z < 3; z++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          blocks[x][y][z] = new Block(l, 0, 0, 0, color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)));
          blocks[x][y][z].translateBlock(l * (x - 3f / 2f + 0.5f), l * (y - 3f / 2f + 0.5f), l * (z - 3f / 2f + 0.5f));
        }
      }
    }
  }
  
  public void draw() {
    for(int z = 0; z < 3; z++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          blocks[x][y][z].draw();
        }
      }
    }
  }
  
  public void rotateXPositive(int face) {
    
    Block[][] b = new Block[3][3];
    
    for(int z = 0; z < 3; z++) {
      for(int y = 0; y < 3; y++) {
        blocks[face][y][z].rotateXPositive();
        b[y][z] = blocks[face][y][z];
      }
    }
    
    for(int z = 0; z < 3; z++) {
      for(int y = 0; y < 3; y++) {
        blocks[face][y][z] = b[z][2 - y];
      }
    }
    
  }
  
  public void rotateYPositive(int face) {
    for(int z = 0; z < 3; z++) {
      for(int x = 0; x < 3; x++) {
        blocks[x][face][z].rotateYPositive();
      }
    }
  }
  
}
public class Quad {
  
  private PVector[] v;
  private int qColor;
  
  public Quad(PVector[] v, int qColor) {
    this.v = v;
    this.qColor = qColor;
  }
  
  public void draw() {
    pushStyle();
    stroke(10);
    strokeWeight(4);
    fill(qColor);
    
    beginShape();
    
    for(int i = 0; i < v.length; i++) {
      vertex(v[i].x, v[i].y, v[i].z);
    }
    
    endShape(CLOSE);
    popStyle();
  }
  
  private boolean pointInsideQuad(Camera camera) {
    PVector v1 = camera.projectedCoordinatesOf(v[0]);
    PVector v2 = camera.projectedCoordinatesOf(v[1]);
    PVector v3 = camera.projectedCoordinatesOf(v[2]);
    PVector v4 = camera.projectedCoordinatesOf(v[3]);
    
    return
      computePointPosition(mouseX, mouseY, v1.x, v1.y, v2.x, v2.y) < 0 &&
      computePointPosition(mouseX, mouseY, v2.x, v2.y, v3.x, v3.y) < 0 &&
      computePointPosition(mouseX, mouseY, v3.x, v3.y, v4.x, v4.y) < 0 &&
      computePointPosition(mouseX, mouseY, v4.x, v4.y, v1.x, v1.y) < 0;
  }
  
  private float computePointPosition(float x, float y, float x0, float y0, float x1, float y1) {
    // see "solution 3" at http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
    return (y - y0) * (x1 - x0) - (x - x0) * (y1 - y0);
  }
  
  public void setQColor(int qColor) {
    this.qColor = qColor;
  }
  
}
  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#DFDFDF", "Rubik" });
  }
}
