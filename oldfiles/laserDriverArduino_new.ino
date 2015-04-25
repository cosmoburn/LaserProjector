#include <laserDriver.h>

const int button_UP = 19,
          button_DOWN = 18,
          button_SEL = 17;

unsigned char wait = 0,
     l_paddle = 128,
     r_paddle = 128,
     S_paddle = 3,
     SETTING = 0;
     
int  A_ball = 0,
      heightAdjust = 0;


float  SX_ball = 1.5,
       SY_ball = 2.5,
       X_ball = 128.0,
       Y_ball = 128.0;
      

laserDriver LD;

void setup() 
{
  
  pinMode(13, OUTPUT);
  pinMode(button_UP, INPUT);
  pinMode(button_DOWN, INPUT);
  pinMode(button_SEL, OUTPUT);
  digitalWrite(13,HIGH);

}

void loop() {
 
  /* sets the paddle's y positions to the value read from pods */
 l_paddle = analogRead(4)/4;
 r_paddle = analogRead(5)/4;


  
/*  //GET PLAYER 1
  digitalWrite(button_SEL, HIGH);
  
  if ( !digitalRead(button_UP) ) {
    
    if (l_paddle>11)
      l_paddle-=S_paddle;
    else
      l_paddle=11;
    //Y_paddle-=3;
  
  } else if ( !digitalRead(button_DOWN) ) {
    
    if (l_paddle<244)
      l_paddle+=S_paddle;
    else
      l_paddle=244;
      
    //Y_paddle+=3;
      
  } else;
  
  //GET PLAYER 2
  digitalWrite(button_SEL, LOW);
  
  if ( !digitalRead(button_UP) ) {
    
    if (r_paddle>11)
      r_paddle-=S_paddle;
    else
      r_paddle=11;
    //Y_paddle-=3;
  
  } else if ( !digitalRead(button_DOWN) ) {
    
    if (r_paddle<244)
      r_paddle+=S_paddle;
    else
      r_paddle=244;
      
    //Y_paddle+=3;
      
  } else;
 */
   
  LD.lSet(0,heightAdjust);
  delayMicroseconds(1000);
  LD.lSet(255,heightAdjust);
  delayMicroseconds(1000);
  LD.lSet(128, heightAdjust);
  delayMicroseconds(1000);
  LD.lSet(128, 255-heightAdjust);
  delayMicroseconds(1000);
  LD.lSet(255,255-heightAdjust);
  delayMicroseconds(1000);
  LD.lSet(0,255-heightAdjust);
  delayMicroseconds(1000);

  LD.lRect(10, l_paddle, 8, 20);
  LD.lRect(245, r_paddle, 8, 20);

  if (X_ball>250 || X_ball<14)
    SX_ball *= -1;
  else;
  
  if (Y_ball>250 || Y_ball<4)
    SY_ball *= -1;
  else;
    
  X_ball += SX_ball;
  Y_ball += SY_ball;
  
  LD.lCircle(X_ball, Y_ball, 3);
}
