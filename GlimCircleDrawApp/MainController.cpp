#include "pch.h"
#include "MainController.h"
#include "GlimCircleDrawAppDlg.h"
#include "CircleMath.h"
#include "RandomMoveThread.h"

MainController::MainController(CGlimCircleDrawAppDlg* pView)
    : m_pView(pView)
{
    m_pRender = std::make_unique<CircleRender>();
}

MainController::~MainController()
{
}

void MainController::UpdateSettings(int pointRadius, int circleThickness)
{
    if (pointRadius > 0)
    {
        m_pointRadius = pointRadius;
    }

    if (circleThickness > 0)
    {
        m_circleThickness = circleThickness;
    }
}

CString MainController::GetPointInfoText() const
{
    CString text;
    
    for (int i = 0; i < static_cast<int>(m_model.m_points.size()); i++)
    {
        CString line;

        line.Format(_T("Point %d : (%d, %d)\r\n"),
            i + 1,
            m_model.m_points[i].x,
            m_model.m_points[i].y);

		text += line;
    }

    return text;
}

int MainController::GetRandomCount() const
{
	return RandomMoveCount;
}

void MainController::OnLButtonDown(CPoint point)
{
    int selectedIndex = m_model.FindPointIndex(point.x, point.y, m_pointRadius);

    if (selectedIndex != INVALID_INDEX)
    {
        m_model.m_selectedIndex = selectedIndex;
        m_model.m_isDragging = true;
        return;
    }

    if (!m_model.IsPointFull())
    {
        m_model.AddPoint(point.x, point.y);
        RecalculateCircle();
        RequestRedraw();
    }
}

void MainController::OnMouseMove(CPoint point)
{
    if (!m_model.m_isDragging)
        return;

    if (m_model.m_selectedIndex == INVALID_INDEX)
        return;

    m_model.MovePoint(m_model.m_selectedIndex, point.x, point.y);

    RecalculateCircle();
    RequestRedraw();
}

void MainController::OnLButtonUp()
{
    m_model.m_isDragging = false;
    m_model.m_selectedIndex = INVALID_INDEX;
}

void MainController::OnReset()
{
    m_model.Clear();
    RandomMoveCount = 0;
    RequestRedraw();
}

bool MainController::OnRandomMove()
{
    if (m_pView != nullptr) {
        if (!m_model.CanDrawCircle())
            return false;
    }

    AfxBeginThread(RandomMoveThreadProc, this);
    
	return true;
}

void MainController::RandomMoveStep(const CRect& boundary)
{
    m_model.RandomMove(boundary);

    RecalculateCircle();

    RequestRedraw();
}

void MainController::Render(CImage& img)
{
	if (img.IsNull())
        return;

    // Circle from point
    for (const auto& point : m_model.m_points)
    {
        m_pRender->DrawCircle(
            img,
            point.x, // point centerX
            point.y, // point centerY
            m_pointRadius,
            false, //isCircleFromMultiPoints
            COLOR_BLACK);
    }

	// Circle from 3 points
    if (m_model.m_isCircleFromMultiPoints)
    {
        m_pRender->DrawCircle(
            img,
            static_cast<int>(m_model.m_circle.centerX),
            static_cast<int>(m_model.m_circle.centerY),
            static_cast<int>(m_model.m_circle.radius),
            m_model.m_isCircleFromMultiPoints,
            COLOR_GRAY,
            m_circleThickness);
    }
}

void MainController::RecalculateCircle()
{
    if (!m_model.CanDrawCircle())
    {
        m_model.m_isCircleFromMultiPoints = false;
        return;
    }

    m_model.m_isCircleFromMultiPoints = CircleMath::Calculate(
        m_model.m_points[0],
        m_model.m_points[1],
        m_model.m_points[2],
        m_model.m_circle);
}

void MainController::RequestRedraw()
{
    if (m_pView != nullptr)
    {
        m_pView->Invalidate(FALSE);
    }
}