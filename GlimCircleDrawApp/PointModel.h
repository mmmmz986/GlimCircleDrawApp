#pragma once

/// <summary>
/// 점 모델 구조체
/// </summary>
struct PointModel
{
    int x = 0;
    int y = 0;

    PointModel() = default;

    PointModel(int x, int y)
        : x(x), y(y)
    {
    }
};