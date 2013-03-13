public class Cube {
  
/*  private float size;
  private Block[][][] blocks;
  
  public Cube(float size) {
    this.size = size;
    float l = size / 3;
    blocks = new Block[3][3][3];
    
    for(int z = 0; z < 3; z++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          blocks[x][y][z] = new Block(l, 0, 0, 0, color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)), color(random(255), random(255), random(255)));
          blocks[x][y][z].translateBlock(l * (x - 3f / 2f + 0.5), l * (y - 3f / 2f + 0.5), l * (z - 3f / 2f + 0.5));
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
*/  
}
