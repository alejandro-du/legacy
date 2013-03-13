/**
 * Scramble.
 * by Alejandro Duarte (alejandro.d.a@gmail.com)
 * 
 * Press 'h' to display the global shortcuts in the console.
 * Press 'H' to display the current camera profile keyboard shortcuts
 * and mouse bindings in the console.
 */

import remixlab.proscene.*;

Scene scene;
Board board;

public void setup() {
  size(800, 500, P3D); // window size
  scene = new Scene(this); // create a Scene instance
  scene.setAxisIsDrawn(false); // hide axis
  scene.setGridIsDrawn(false); // hide grid
  board = new Board(3, scene, null); // create a new 3x3 board
  scene.camera().setPosition(new PVector(-20, 100, 230)); // move the camera
  scene.camera().lookAt(new PVector(0, 0, 0)); // make the camera look at the center of the board
}

public void draw() {
  PVector pos = new PVector(scene.camera().at().x, scene.camera().at().y, scene.camera().at().z);
  PVector at = new PVector(scene.camera().position().x, scene.camera().position().y, scene.camera().position().z);
  PVector lightDirection = PVector.sub(pos, at);
  
  // create some lights to make the board look cool
  lights(); // lights on
  directionalLight(50, 50, 50, lightDirection.x, lightDirection.y, lightDirection.z);
  spotLight(150, 150, 150, pos.x, pos.y, pos.z, 0, 0, -1, 1, 20);
  spotLight(100, 100, 100, pos.x, pos.y, pos.z, 0, 0, 1, 1, 20);
  
  board.draw();
  drawText();
}

public void drawText() {
  textMode(SCREEN); // screen coordinates for text output
  fill(#BBBBBB);
  textFont(createFont("FFScala", 14));
  text("" + board.getMoves() + " moves.", 5, height - 20);
  text("Press 'S' to scramble, 'O' to order, 'M' to change mode, '+' to increase size, '-' to decrease size.", 5, height - 5);
  textFont(createFont("FFScala", 30));
  fill(#EEEEEE);
  text(board.isOrdered() && board.getMoves() > 0 ? "COMPLETED!" : "", 5, 28);
  textMode(MODEL); // back to model coordinates for text output
}

public void keyTyped() {
  if(key == 's' || key == 'S') {
    board.scramble();
  } else if(key == 'o' || key == 'O') {
    board.order();
  } else if(key == 'm' || key == 'M') {
    // switch between image mode and numbers mode
    if(board.getImage() == null) {
      board.setImage(loadImage("image.png"));
    } else {
      board.setImage(null);
    }
    board.order();
  } else if(key == '+') {
    if(board.getSize() < 5) { // limt size to 5 patches due to display issues
      board.setSize(board.getSize() + 1);
    }
  } else if(key == '-') {
    if(board.getSize() > 3) { // a 2x2 board is not very interesting
      board.setSize(board.getSize() - 1);
    }
  }
}
