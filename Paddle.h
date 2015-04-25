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
		int GetXpos()const{return xPos;}
		int GetYpos()const{return yPos;}
	 	int GetDx()const{return dx;}
	 	int GetDy()const{return dy;}
	 	int GetWidth()const{return width;}
	 	int GetHeight()const{return height;}

	 	void UpdateY(int y){yPos=y;}

	 	void SetPosY(unsigned char y) { yPos = y;}

	 	/**
	 	*	@brief 
	 	*	
	 	*	@params	
	 	*/
	 	void Draw(	LaserDriver &LD )	{ LD.lRect(xPos, yPos, width, height); }

};

#endif