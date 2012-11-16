

#ifndef COLOR_H
#define COLOR_H
class Color
{
	public:
	float red;
	float blue;
	float green;
	float transparency;
	
	Color(float newRed,float newGreen, float newBlue,float newTranslucency)
		{setColors(newRed,newGreen,newBlue,newTranslucency);}

	Color() 
		{setColors(0,0,0,1);}

	~Color()
		{}
	
	void	setColors(float newRed,float newGreen, float newBlue,float newTranslucency)
	{
		red = newRed;
		green = newGreen;
		blue = newBlue;
		transparency = newTranslucency;
		
	}
};


#endif