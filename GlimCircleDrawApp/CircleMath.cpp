#include "pch.h"
#include "CircleMath.h"
#include <cmath>

bool CircleMath::Calculate(
    const PointModel& p1,
    const PointModel& p2,
    const PointModel& p3,
    CircleModel& outCircle)
{
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;
    double x3 = p3.x;
    double y3 = p3.y;

    // 원의 중심점
    double d = 2.0 * ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));

    if (std::abs(d) < 0.0000001)
    {
        return false;
    }

    double x = (((x1 * x1 + y1 * y1) * (y2 - y3)) + ((x2 * x2 + y2 * y2) * (y3 - y1)) + ((x3 * x3 + y3 * y3) * (y1 - y2)));
    double y = (((x1 * x1 + y1 * y1) * (x3 - x2)) + ((x2 * x2 + y2 * y2) * (x1 - x3)) + ((x3 * x3 + y3 * y3) * (x2 - x1)));

	double ux = x / d;
	double uy = y / d;

	// 원의 반지름
    double r = std::sqrt(((ux - x1) * (ux - x1)) + ((uy - y1) * (uy - y1)));

    outCircle.centerX = ux;
    outCircle.centerY = uy;
    outCircle.radius = r;

    return true;
}