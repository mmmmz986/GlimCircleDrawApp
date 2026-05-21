#pragma once

/// <summary>
/// 원 그리기 클래스
/// </summary>
class CircleRender
{
public:
    /// <summary>
	/// 이미지 객체에 원을 그리는 함수입니다.
    /// </summary>
    /// <param name="img"> : CImage 참조 객체</param>
    /// <param name="centerX"> : 중앙 X 좌표</param>
    /// <param name="centerY"> : 중앙 Y 좌표</param>
    /// <param name="radius"> : 반지름</param>
    /// <param name="isCircleFromMultiPoints"> : 3 points 로 그리는 원 인지</param>
    /// <param name="color"> : 색깔(Gray or Black)</param>
    /// <param name="thickness"> : 선 두께</param>
    void DrawCircle(CImage &img, int centerX, int centerY, int radius, bool isCircleFromMultiPoints, int color, int thickness = 1);

private:
    /// <summary>
	/// 원이 내부인지 판별하는 함수입니다.
    /// </summary>
    /// <param name="x"> : 현재 x 좌표</param>
    /// <param name="y"> : 현재 y 좌표</param>
    /// <param name="centerX"> : 중앙 X 좌표</param>
    /// <param name="centerY"> : 중앙 Y 좌표</param>
    /// <param name="radius"> : 반지름</param>
    /// <returns> : 판별 결과</returns>
    bool isInCircle(int x, int y, int centerX, int centerY, int radius);

	/// <summary>
	/// 원이 선의 경계에 있는지 판별하는 함수입니다.
	/// </summary>
	/// <param name="x"> : 현재 x 좌표</param>
	/// <param name="y"> : 현재 y 좌표</param>
	/// <param name="centerX"> : 중앙 x 좌표</param>
	/// <param name="centerY"> : 중앙 y 좌표</param>
	/// <param name="radius"> : 반지름</param>
	/// <param name="thickness"> : 선 두께</param>
	/// <returns> : 판별 결과</returns>
	bool isOnBoarderCircle(int x, int y, int centerX, int centerY, int radius, int thickness);
};