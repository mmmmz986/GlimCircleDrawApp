#include "pch.h"
#include "CircleRender.h"

void CircleRender::DrawCircle(
    CImage &img,
    int centerX,
    int centerY,
    int radius,
    bool isCircleFromMultiPoints,
    int color,
    int thickness)
{
    if (img.IsNull())
        return;

    if (radius <= 0 || radius > 1000)
        return;

    // set
	unsigned char* fm = static_cast<unsigned char*>(img.GetBits());
    int pitch = img.GetPitch();

    int startX = centerX - radius - thickness;
    int endX = centerX + radius + thickness;
	int startY = centerY - radius - thickness;
    int endY = centerY + radius + thickness;
	
    
    // draw
    for (int j = startY; j < endY; j++)
    {
        for (int i = startX; i < endX; i++)
        {
            if (i < 0 || i >= img.GetWidth() || j < 0 || j >= img.GetHeight())
                continue;

            bool draw = false;

            if (isCircleFromMultiPoints)
            {
                draw = isOnBoarderCircle(i, j, centerX, centerY, radius, thickness);
            }
            else
            {
                draw = isInCircle(i, j, centerX, centerY, radius);
            }

            if (draw)
            {
                fm[j * pitch + i] = static_cast<unsigned char>(color);
            }
        }
    }
}

bool CircleRender::isInCircle(int x, int y, int centerX, int centerY, int radius)
{
    double dx = x - centerX;
    double dy = y - centerY;
	double distance = dx * dx + dy * dy;

    return distance < radius * radius;
}

bool CircleRender::isOnBoarderCircle(int x, int y, int centerX, int centerY, int radius, int thickness)
{
    double dx = x - centerX;
    double dy = y - centerY;
    double distance = dx * dx + dy * dy;

	double inner = radius - thickness;
	double outer = radius + thickness;

    if(inner < 0)
    {
        inner = 0;
	}
    
	return distance >= inner * inner && distance <= outer * outer;
}