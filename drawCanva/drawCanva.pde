import processing.serial.*;
Serial port;
float count = 150;
PFont f;

void setup() {
  fullScreen();
  surface.setTitle("People Counter App");
  surface.setResizable(true);
  
  port = new Serial(this,"COM3",9600);
  port.bufferUntil('\n');
  
  f = createFont("Arial",200,true); 
}

void draw() {
  textFont(f);       
  fill(0);

  if (count > 0) {
    background(0,255,0);
    textAlign(CENTER);
    text("Posti rimanenti",width/2,250);
    textSize(700);
    text(int(count),width/2,900);
  }
  else {
    background(255,0,0);
    textAlign(CENTER);
    text("Posti esauriti!",width/2,250);
    textSize(700);
    text(int(count),width/2,900);
  }
  
}

void serialEvent(Serial port) {
  count = float(port.readStringUntil('\n'));
}
