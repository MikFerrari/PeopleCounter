import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class AutoTally extends PApplet {


Serial port;
float count = 160;
PFont f;

public void setup() {
  
  surface.setTitle("People Counter App");
  surface.setResizable(true);
  
  port = new Serial(this,"COM3",9600);
  port.bufferUntil('\n');
  
  f = createFont("Arial",200,true); 
}

public void draw() {
  textFont(f);       
  fill(0);

  if (count > 0) {
    background(0,255,0);
    textAlign(CENTER);
    text("Posti rimanenti",width/2,250);
    textSize(700);
    text(PApplet.parseInt(count),width/2,900);
  }
  else {
    background(255,0,0);
    textAlign(CENTER);
    text("Posti esauriti!",width/2,250);
    textSize(700);
    text(PApplet.parseInt(count),width/2,900);
  }
  
}

public void serialEvent(Serial port) {
  count = PApplet.parseFloat(port.readStringUntil('\n'));
}
  public void settings() {  fullScreen(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "AutoTally" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
