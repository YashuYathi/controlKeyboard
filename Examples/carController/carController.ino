#include <controlKeyboard.h>

USBHost usb;
controlKeyboard keyboard(usb);
const int SIZE = 8;                   //Size of motors array
int motors[SIZE] = {9,8,7,6,5,4,3,2}; //Pins
//int H = HIGH, L = LOW; 

 // Constants for forward,backward,left,right and gears buttons
const int UP = 82, DOWN = 81, LEFT = 80, RIGHT = 79, STOP = 44, UPPER = 26, DOWNER = 22, MAX_GEAR = 6, PRESSED = 0, RELEASED =1;

// variables as indicators for F,B,L,R functions
int S = 0, F = 0, B = 0, FL = 0, FR = 0, BL = 0, BR = 0; 

// Press is for interrupt and speeder is for gear
int dly = 0, speeder = 0, speed = 15, min_speed = 15, max_speed[MAX_GEAR] = {40,80,120,180,220,255};

void setup_pinmode(){
  for(int i =0;i<SIZE;i++){
    pinMode(motors[i], OUTPUT);
  }
}

void initialize_pins(){
  for(int i =0;i<SIZE;i++){
      digitalWrite(motors[i], LOW);
  }
}

void forward() {
  Serial.println("-------------------Forward-------------------");
  Serial.println();
  Serial.print("Forward Speed: ");
  Serial.println(speeder);
  for(int i=0;i<SIZE;i = i+2){
    analogWrite(motors[i+1], 0);
    analogWrite(motors[i], speed);
  } 
  for(speed;speed<max_speed[speeder];speed = speed + 4){
    if(keyboard.onKeyPress(UP)){
      int ms = map(speed,0,100,0,255);
      int dly = 100 / ms;
      for(int i=0;i<SIZE;i = i+2){
        analogWrite(motors[i], speed);
      }    
      delay(dly);
    }
  }
  Serial.println("------------------END-Forward-------------------");
}

void backward() {
  Serial.println("-------------------Backward-------------------");
  Serial.println();  
  Serial.print("Backward Speed: ");
  Serial.println(speeder);
  for(int i=0;i<SIZE;i = i+2){
    analogWrite(motors[i], 0);
    analogWrite(motors[i+1], speed);
  }  
  for(speed;speed<max_speed[speeder];speed = speed + 4){
    if(keyboard.onKeyPress(DOWN)){    
      int ms = map(speed,0,100,0,255);
      int dly = 100 / ms;
      for(int i=0;i<SIZE;i = i+2){
        analogWrite(motors[i+1], speed);
      }    
      delay(dly);
    }
  }
  Serial.println("------------------END-Backward-------------------");
}

void forward_left(){
  Serial.println();
  Serial.println("-------------------Forward Left-------------------");
  
  analogWrite(motors[0], 0);
  analogWrite(motors[1], 0);
  for(int i =2;i<SIZE;i = i+2){
    analogWrite(motors[i], speed);
    analogWrite(motors[i+1], 0);
  }
  /*speeder = (speeder > 0)?speeder - 1: 0;
  for(speed;speed >= max_speed[speeder];speed = speed - 4){   
    if(keyboard.onKeyPress(LEFT)){ 
      int ms = map(speed,0,100,0,max_speed[speeder]);
      int dly = 100 / ms;
      for(int i =2;i<SIZE;i = i+2){
        analogWrite(motors[i], speed);
      }
      delay(dly);
    }
  }*/
  Serial.println("-------------------End Forward Left-------------------");
}

void forward_right(){
  Serial.println("-------------------Forward Right-------------------");
  analogWrite(motors[0],speed);
  analogWrite(motors[1],0);
  analogWrite(motors[2], 0);
  analogWrite(motors[3], 0);
  for(int i =4;i<SIZE;i = i+2){
    analogWrite(motors[i], speed);
    analogWrite(motors[i+1], 0);
  }
  /*
  speeder = (speeder > 0)?speeder - 1: 0;
  for(speed;speed >= max_speed[speeder];speed = speed - 4){   
    if(keyboard.onKeyPress(RIGHT)){ 
      int ms = map(speed,0,100,0,max_speed[speeder]);
      int dly = 100 / ms;
      analogWrite(motors[0], speed);
      for(int i =4;i<SIZE;i = i+2){
        analogWrite(motors[i], speed);
      }
      delay(dly);
    }
  }*/
  Serial.println("-------------------End Forward Right-------------------");
}

void backward_left(){
  Serial.println("-------------------Backward Left-------------------");
  analogWrite(motors[0], 0);
  analogWrite(motors[1], 0);
  for(int i =2;i<SIZE;i = i+2){
    analogWrite(motors[i], 0);
    analogWrite(motors[i+1], speed);
  }
  /* speeder = (speeder > 0)?speeder - 1: 0;
  for(speed;speed >= max_speed[speeder];speed = speed - 4){   
    if(keyboard.onKeyPress(LEFT)){ 
      int ms = map(speed,0,100,0,max_speed[speeder]);
      int dly = 100 / ms;
      for(int i =2;i<SIZE;i = i+2){
        analogWrite(motors[i+1], speed);
      }
      delay(dly);
    }
  }*/
  Serial.print("-------------------End Backward Left-------------------");
}

void backward_right(){
  Serial.println("-------------------Backward Right-------------------");
  analogWrite(motors[0], 0);
  analogWrite(motors[1], speed);
  analogWrite(motors[2], 0);
  analogWrite(motors[3], 0);
  for(int i =4;i<SIZE;i = i+2){
    analogWrite(motors[i], 0);
    analogWrite(motors[i+1], speed);
  }
  /*
  speeder = (speeder > 0)?speeder - 1: 0;
  for(speed;speed >= max_speed[speeder];speed = speed - 4){   
    if(keyboard.onKeyPress(RIGHT)){ 
      int ms = map(speed,0,100,0,max_speed[speeder]);
      int dly = 100 / ms;
      analogWrite(motors[1], speed);
      for(int i =4;i<SIZE;i = i+2){
        analogWrite(motors[i+1], speed);
      }
      delay(dly);
    }
  }*/
}


//to STOP smoothly
void stop_this() { 
  int s = min_speed - 1; 
  if(F ==1 ){
    Serial.println("<<-------------------Stoping Forward------------------->>");
    while(speed>=s){      
      if(keyboard.onKeyRelease(UP)){ 
        int ms = map(speed,0,100,0,max_speed[speeder]);
        int dly = 500 / ms;
        for(int i =0;i<SIZE;i = i+2){
          analogWrite(motors[i], speed);
        }
        delay(dly);
      }
      speed = speed - 1;
    }
    Serial.println("-------------------Forward Stopped-------------------");
  }
  if(B ==1){
    Serial.println("<<-------------------Stoping Backward------------------->>");
    while(speed>=s){      
      if(keyboard.onKeyRelease(DOWN)){ 
        int ms = map(speed,0,100,0,max_speed[speeder]);
        int dly = 500 / ms;
        for(int i =0;i<SIZE;i = i+2){
          analogWrite(motors[i+1], speed);
        }
        delay(dly);
      }
      speed = speed - 1;
    } 
    Serial.println("-------------------Backward Stopped-------------------");
  }
  for(int i =0;i<SIZE;i++){
    analogWrite(motors[i], 0);
  }
  F = 0;
  B = 0;
  FL = 0;
  FR = 0;
  BL = 0;
  BR = 0;
  speeder = 0;
  speed = 15;
  keyboard.setDefault(UP);
  keyboard.setDefault(DOWN);
  keyboard.setDefault(LEFT);
  keyboard.setDefault(RIGHT);
}

//to STOP suddenly
void break_this(){
  keyboard.setDefault(UP);
  keyboard.setDefault(DOWN);
  keyboard.setDefault(LEFT);
  keyboard.setDefault(RIGHT);
  keyboard.setDefault(UPPER);
  keyboard.setDefault(DOWNER);
  F = 0;
  B = 0;
  FL = 0;
  FR = 0;
  BL = 0;
  BR = 0;
  speeder = 0;
  speed = 15;
  Serial.println("!!!-------------------Sudden STOP-------------------!!!");
  for(int i =0;i<SIZE;i++){
    analogWrite(motors[i], 0);
  }
  keyboard.setDefault(STOP);
}

void setup() {
  setup_pinmode();
  initialize_pins(); 
  
  Serial.begin(9600);
  Serial.println("Program started");
}

void loop() {
  usb.Task();
   //Key Released
   Serial.println();
   Serial.println();
  if(keyboard.onKeyRelease(STOP)){
    Serial.println("STOP key is Released");
    S = 0;
    keyboard.setDefault(STOP);
  }
  else if(keyboard.onKeyRelease(UPPER) || keyboard.onKeyRelease(DOWNER)){
    Serial.println("UPPER key or DOWNER key are Released");
    keyboard.setDefault(UPPER);
    keyboard.setDefault(DOWNER);
  }
  else if((F == 1 && keyboard.onKeyRelease(LEFT)) || (F == 1 && keyboard.onKeyRelease(RIGHT))){
    Serial.println("Only FORWARD");
    B = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    keyboard.setDefault(LEFT);
    keyboard.setDefault(RIGHT);
    forward();
  }
  else if((B== 1 && keyboard.onKeyRelease(LEFT)) || (B == 1 && keyboard.onKeyRelease(RIGHT))){
    Serial.println("Only Backward");
    F = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    /* speeder = (speeder<MAX_GEAR)? speeder + 1: MAX_GEAR; 
    for(speed;speed<max_speed[speeder];speed = speed + 4){   
      if(keyboard.onKeyPress(LEFT)){ 
        int ms = map(speed,0,100,0,max_speed[speeder]);
        int dly = 100 / ms;
        for(int i =0;i<SIZE;i = i+2){
          analogWrite(motors[i+1], speed);
        }
        delay(dly);
      } 
    } */
    keyboard.setDefault(LEFT);
    keyboard.setDefault(RIGHT);
    backward();
  }
  else if(keyboard.onKeyRelease(UP) || keyboard.onKeyRelease(DOWN)){
    Serial.println("UP or DOWN key are Released");
    stop_this();
  }
  else if ((F==0 && B==0 ) && (keyboard.onKeyRelease(LEFT) || keyboard.onKeyRelease(RIGHT))) {
    //Serial.println("UP or DOWN and LEFT or RIGHT key Released");
    //stop_this();
  }

  //Checking Key, is Pressed
  else if(keyboard.onKeyPress(STOP)){
    //Serial.println("STOP key Pressed");
    S = 1;
    break_this();
  }
  else if(F == 1 && keyboard.onKeyPress(UPPER)){
    Serial.println("Forward UPPER key is Pressed");
    speeder = (speeder<MAX_GEAR)? speeder + 1: MAX_GEAR;    
    F = 1;
    B = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    Serial.println("<<----------------------Forward Speed Increased");
    forward();
  }
  else if(F == 1 && keyboard.onKeyPress(DOWNER)){
    Serial.println("Forward DOWNER key is Pressed");
    speeder = (speeder>0)? speeder - 1: 0;    
    F = 1;
    B = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0; 
    for(speed;speed >= max_speed[speeder];speed = speed - 4){ 
      if(keyboard.onKeyPress(UP)){   
        int ms = map(speed,0,100,0,max_speed[speeder]);
        int dly = 100 / ms;
        for(int i =0;i<SIZE;i = i+2){
          analogWrite(motors[i], speed);
        }
        delay(dly);
      }
    }
    Serial.println("<<-----------------------Forward Speed Reduced");
    forward();
  }
  else if(F == 1 && keyboard.onKeyPress(LEFT)){
    Serial.println("<--------Forward LEFT");
    B = 0;
    FL = 1;
    FR = 0;
    BL = 0;
    BR = 0;
    forward_left();
  }
  else if(F == 1 && keyboard.onKeyPress(RIGHT)){
    Serial.println("Forward RIGHT-------->");
    B = 0;
    FL = 0;
    FR = 1;
    BL = 0;
    BR = 0;
    forward_right();
  }
  else if(S!=1 && keyboard.onKeyPress(UP)){  
    Serial.println("UP key is Pressed");  
    F = 1;
    B = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    forward();
  }
  else if(B == 1 && keyboard.onKeyPress(UPPER)){
    Serial.println("Backward UPPER key is Pressed");
    speeder = (speeder<MAX_GEAR)? speeder + 1: MAX_GEAR; 
    F = 0;
    B = 1;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    Serial.println("<<-----------------------Backward Speed Increased");
    backward();
  }
  else if(B == 1 && keyboard.onKeyPress(DOWNER)){
    Serial.println("Backward DOWNER key is Pressed");
    speeder = (speeder>0)? speeder - 1: 0;
    F = 0;
    B = 1;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    for(int i =0;i<SIZE;i = i+2){
      analogWrite(motors[i], 0);
    }  
    for(speed;speed >= max_speed[speeder];speed = speed - 4){
      if(keyboard.onKeyPress(DOWN)){    
        int ms = map(speed,0,100,0,max_speed[speeder]);
        int dly = 100 / ms;
        for(int i =0;i<SIZE;i = i+2){
          analogWrite(motors[i+1], speed);
        }
        delay(dly);
      }
    }
    Serial.println("<<-----------------------Backward Speed Reduced");
    backward();
  }
  else if(B== 1 && keyboard.onKeyPress(LEFT)){
    Serial.println("<--------Backward LEFT");
    F = 0;
    FL = 0;
    FR = 0;
    BL = 1;
    BR = 0;
    backward_left();
  }
  else if(B == 1 && keyboard.onKeyPress(RIGHT)){
    Serial.println("Backward RIGHT-------->");
    F = 0;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 1;
    backward_right();
  }
  else if(S!=1 && keyboard.onKeyPress(DOWN)){   
    Serial.println("DOWN key is Pressed"); 
    F = 0;
    B = 1;
    FL = 0;
    FR = 0;
    BL = 0;
    BR = 0;
    backward();
  }
  else if ((F==0 || B==0 ) && (keyboard.onKeyPress(LEFT) || keyboard.onKeyPress(RIGHT))) {
    Serial.println("LEFT and/or RIGHT key are Pressed");
    stop_this();
  }  
}
