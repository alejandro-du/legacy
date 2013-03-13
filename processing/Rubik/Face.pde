public class Face extends InteractiveFrame {
  
  List<Block> blocks;
  private PVector axis;
  
  public Face(Scene scene, List<Block> blocks, PVector axis) {
    super(scene);
    this.blocks = blocks;
    this.axis = axis;

    LocalConstraint c = new LocalConstraint();
    c.setRotationConstraintType(AxisPlaneConstraint.Type.AXIS);
    c.setRotationConstraintDirection(axis);
    setConstraint(c);
  }
  
  public void draw() {
    pushMatrix();
    setPosition(0, 0, 0);
    fixOrientation();
    applyTransformation();
    
    for(Block b : blocks) {
      b.draw();
    }
    
    popMatrix();
  }
  
  public void fixOrientation() {
    if(!isInInteraction()) {
      float angle = degrees(axis.x * rotation().eulerAngles().x + axis.y * rotation().eulerAngles().y + axis.z * rotation().eulerAngles().z);
      if(angle <= -45 && angle >= -135) {
        angle = 270;
      } else {
        angle = degrees(rotation().angle());
        if(angle >= 45 && angle < 135) {
          angle = 90;
        } else if(angle >= 135 && angle < 225) {
          angle = 180;
        } else if(angle >= 225 && angle < 315) {
          angle = 270;
        } else {
          angle = 0;
        }
      }
      
      angle = radians(angle);
      setRotation(new Quaternion(axis, angle));
    }
  }
  
  public void checkIfGrabsMouse(int x, int y, Camera camera) {
    
    setTranslation(0, 0, 0);
    for(Block b: blocks) {
      if(keepsGrabbingMouse || b.pointInsideBlock(x, y, camera, this)) {
        setGrabsMouse(true);
        return;
      }
    }
    
    setGrabsMouse(false);
  }

}
