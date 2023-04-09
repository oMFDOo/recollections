import processing.opengl.*;
import processing.serial.*;

Serial Port;
float[] val = new float[5];
float rotX, rotY, rotZ, transX, transY, scaleFactor;
float prevX, prevY, prevZ;

void setup() {
  String portName = Serial.list()[1];
  Port = new Serial(this, portName, 9600);
  Port.bufferUntil('\n');

  rotX = rotY = rotZ = 0;
  prevX = prevY = prevZ = 0;
  
  size(1000, 500, P3D);
  //size(1024, 768, P3D);
  noStroke();
}

void draw() {

  lights();
  
  translate(width/2, height/2, -height/2);
  background(0);
  
  rotateX(rotX * -1);
  rotateY(rotY);
  rotateZ(rotZ);
  
  pushMatrix();
  fill(0, 255, 50);
  box(width/3, height/5,  height/5);
  popMatrix();

  pushMatrix();
  fill(255, 255, 0);
  box(width/12, height/5, height);
  popMatrix();
  
  pushMatrix();
  translate(0, 0, -height/2);
  fill(255, 255, 0);
  box(width/5, height/5, height/5);
  popMatrix();

  pushMatrix();
  translate(0, -width/14, -height/2);
  fill(255, 255, 0);
  box(height/7, width/14, height/5);
  popMatrix();

}

int cnt = 0;

void serialEvent(Serial port) {
  String input = port.readStringUntil('\n');
  println(input);
  if (input.charAt(0) == 's') {
    cnt = 0;
  } 
  else {
    val[cnt] = float(input);
    if (cnt >= 2) {
      rotX += radians(prevX - val[1]);
      rotY += radians(prevY - val[2]);
      rotZ += radians(prevZ - val[0]);
      
      println("rotX : " + rotX);
      println("rotY : " + rotY);
      println("rotZ : " + rotZ);
      println();
      
      prevX = val[1];
      prevY = val[2];
      prevZ = val[0];
    }
    cnt++;
  }
}

void mouseDragged() {

  rotY -= (mouseX - pmouseX) * 0.01;
  rotX -= (mouseY - pmouseY) * 0.01;
}