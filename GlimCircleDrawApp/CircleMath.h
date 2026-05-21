#pragma once

#include "PointModel.h"
#include "CircleModel.h"

class CircleMath
{
public:
    /// <summary>
    /// 행렬식 기반 세 점으로부터 원의 중심 및 반지름을 구하는 함수입니다.
    /// </summary>
    /// <param name="p1"> : 첫 번째 점</param>
    /// <param name="p2"> : 두 번째 점</param>
    /// <param name="p3"> : 세 번째 점</param>
    /// <param name="outCircle"> : 원</param>
    /// <returns> : 판별 결과</returns>
    static bool Calculate(
        const PointModel& p1,
        const PointModel& p2,
        const PointModel& p3,
        CircleModel& outCircle);
};