#pragma once

/// <summary>
/// 원 모델 구조체
/// </summary>
struct CircleModel
{
    double centerX = 0.0;
    double centerY = 0.0;
    double radius = 0.0;

    /// 원 모델 초기화
    void Clear()
    {
        centerX = 0.0;
        centerY = 0.0;
        radius = 0.0;
    }
};