#include "pch.h"
#include "MainModel.h"
#include <random>
#include <cmath>

MainModel::MainModel()
{
    Clear();
}

void MainModel::Clear()
{
    m_points.clear();
    m_circle.Clear();

    m_isCircleFromMultiPoints = false;
    m_isDragging = false;
    m_selectedIndex = INVALID_INDEX;
}

bool MainModel::AddPoint(int x, int y)
{
    if (m_points.size() >= static_cast<std::size_t>(MAX_POINT_COUNT))
        return false;

    m_points.push_back(PointModel(x, y));
    return true;
}

void MainModel::MovePoint(int index, int x, int y)
{
    if (index < 0 || index >= static_cast<int>(m_points.size()))
        return;

    m_points[index].x = x;
    m_points[index].y = y;
}

void MainModel::RandomMove(const CRect& boundary)
{
    if (m_points.size() < static_cast<std::size_t>(MAX_POINT_COUNT))
        return;

    static std::random_device rd; // 난수 시드 생성기
	static std::mt19937 gen(rd()); // 난수 생성기

    // 난수 분포 생성
    std::uniform_int_distribution<int> distX(boundary.left + 20, boundary.right - 20);
    std::uniform_int_distribution<int> distY(boundary.top + 20, boundary.bottom - 20);

    for (auto& point : m_points)
    {
		// 난수 생성 후 점 이동
        point.x = distX(gen); 
        point.y = distY(gen);
    }
}

int MainModel::FindPointIndex(int x, int y, int pointRadius) const
{
    for (int i = 0; i < static_cast<int>(m_points.size()); i++)
    {
        // 점과 클릭 위치의 점 사이의 거리 계산
        int dx = m_points[i].x - x;
        int dy = m_points[i].y - y;
        double distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= pointRadius)
            return i;
    }

    return INVALID_INDEX;
}

bool MainModel::IsPointFull() const
{
    return m_points.size() >= static_cast<std::size_t>(MAX_POINT_COUNT);
}

bool MainModel::CanDrawCircle() const
{
    return m_points.size() == static_cast<std::size_t>(MAX_POINT_COUNT);
}