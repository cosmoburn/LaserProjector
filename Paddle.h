#ifndef PADDLE_H
#define PADDLE_H

#include <LaserDriver.h>

/**
* @brief Paddle  
*
*/
class Paddle
{
	private:
		
		/* Dimmenssions and Position of paddle */
		int xPos;
		int yPos;
		int width;
		int height;

		int dy;
		int dx;

	public:

		Paddle(int x, int y, int w, int h): 
	 		xPos(x), 
	 		yPos(y),
	 		width(w),
	 		height(h),
	 		dx(0),
	 		dy(0) 
	 {
	 	//
	 }

		/* Getter methods */
		int getX()const{return xPos;}
		int getY()const{return yPos;}
	 	int getDx()const{return dx;}
	 	int getDy()const{return dy;}
	 	int getW()const{return width;}
	 	int getH()const{return height;}

	 	void update(int y){yPos=y;}

	 	void setY(unsigned char y) { yPos = y;}

	 	/**
	 	*	@brief 
	 	*	
	 	*	@params	
	 	*/
	 	void draw(	LaserDriver &LD )	{ LD.lRect(xPos, yPos, width, height); }

};

#endif