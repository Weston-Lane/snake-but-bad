#include "raylib.h"

class Background
{
public:
	Texture2D texture;

	Vector2 pos{};

	int xPos{};

	int speed{};

	Background()
	{

	}

	Background(Texture2D tex)
	{
		texture=tex;
		
	}

	void updateBackground(double DT)
	{
		
		xPos -= speed * DT;

		if (xPos <= -texture.width * 2)
		{
			xPos = 0.0;
		}
	}
};

//class Midground:public Background
//{
//public:
//	int speed{ -40 };
//
//	Midground(Texture2D tex)
//	{
//		texture = tex;
//	}
//
//};
//class Midground2 :public Background
//{
//public:
//	int speed{ -60 };
//
//	Midground2(Texture2D tex)
//	{
//		texture = tex;
//	}
//};
//
//class Foreground : public Background
//{
//public:
//	int speed{ -80 };
//
//	Foreground(Texture2D tex)
//	{
//		texture = tex;
//	}
//};
