#pragma once

#include <memory>
#include <afxwin.h>

#include "MainModel.h"
#include "CircleRender.h"

class CGlimCircleDrawAppDlg;

/// <summary>
/// 메인 컨트롤러
/// </summary>
class MainController
{
public:
    MainController(CGlimCircleDrawAppDlg* pView);
    ~MainController();

public:
    void UpdateSettings(int pointRadius, int circleThickness);
    CString GetPointInfoText() const;

    int GetRandomCount() const;

    void OnLButtonDown(CPoint point);
    void OnMouseMove(CPoint point);
    void OnLButtonUp();

    void OnReset();
    bool OnRandomMove();
	void RandomMoveStep(const CRect& boundary);

    void Render(CImage& img);

    void RecalculateCircle();

private:
    void RequestRedraw();

public:
    /// 랜덤 이동 횟수
    int RandomMoveCount = 0;

private:
    /// 뷰(View)
    CGlimCircleDrawAppDlg* m_pView = nullptr;

    /// 모델(Data)
	MainModel m_model;

    /// 헬퍼(Render)
    std::unique_ptr<CircleRender> m_pRender;

    /// 작은 원(3 multi) 반지름
    int m_pointRadius = DEFAULT_POINT_RADIUS;
	/// 큰 원 두께
    int m_circleThickness = DEFAULT_CIRCLE_THICKNESS;
};