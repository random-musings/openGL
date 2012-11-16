

#ifndef COLOR_H
#define COLOR_H
class Color
{
	public:
	float red;
	float blue;
	float green;
	
	Color(float newRed,float newGreen, float newBlue)
		{setColors(newRed,newGreen,newBlue);}

	Color() 
		{setColors(0,0,0);}

	~Color()
		{}
	
	void	setColors(float newRed,float newGreen, float newBlue)
	{
		red = newRed;
		green = newGreen;
		blue = newBlue;
	}
};


#endif