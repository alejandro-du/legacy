public class Maze {
  
  private char[][] data;
  
  public Maze(String fileName) {
    loadMaze(fileName);
  }
  
  public void loadMaze(String fileName) {
    BufferedReader reader = createReader(fileName);
    List<String> list = new ArrayList<String>();
    String l;
    
    try {
      while((l = reader.readLine()) != null) {
        list.add(l);
      }
    } catch(IOException e) {
      e.printStackTrace();
      return;
    }
    
    data = new char[list.size()][];
    
    for(int i = 0; i < list.size(); i++) {
      data[i] = list.get(i).toCharArray();
    }
  }
  
  public void draw() {
    float height = 200f / data.length;
    sphereDetail((int) height);
    
    for(int y = 0; y < data.length; y++) {
      float width = 200f / data[y].length;
      
      for(int x = 0; x < data[y].length; x++) {
        pushMatrix();
        pushStyle();
        translate(-200 / 2 + width / 2, -200 / 2 + height / 2); // center of maze = center of world
        translate(x * width, y * height, 0);
        
        if(data[y][x] == '1') {
          box(width, height, width);
        } else if(data[y][x] == '.') {
          sphere(height / 5);
        }
        
        popStyle();
        popMatrix();
      }
    }
  }
}

