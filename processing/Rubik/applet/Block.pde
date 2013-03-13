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
  private float rotationVel = 0.1;
  
  public Block(float size, float x, float y, float z, color color1, color color2, color color3, color color4, color color5, color color6) {
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
