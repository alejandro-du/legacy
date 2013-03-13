/**
 * Game.
 * by Alejandro Duarte (alejandro.d.a@gmail.com)
 * 
 * Press 'h' to display the global shortcuts in the console.
 * Press 'H' to display the current camera profile keyboard shortcuts
 * and mouse bindings in the console.
 */

import remixlab.proscene.*;

Scene scene;
Maze maze;

public void setup() {
  size(800, 500, P3D);
  scene = new Scene(this);
  maze = new Maze("maze1.txt");
}

public void draw() {
  maze.draw();
}

