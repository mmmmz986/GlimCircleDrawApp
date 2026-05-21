#pragma once

#include <vector>
#include <afxwin.h>
#include "PointModel.h"
#include "CircleModel.h"
#include "Define.h"

/// <summary>
/// 메인 모델 : 하위 모델(점, 원)을 포함하여 프로그램 데이터의 전체 상태를 관리하는 의도로 설계되었습니다.
/// </summary>
class MainModel
{
public:
    MainModel();

public:
	void Clear(); // 모델 초기화

	/// <summary>
	/// 추가된 인덱스의 좌표를 추가합니다.
	/// </summary>
	/// <param name="x">: 추가된 인덱스의 x 좌표</param>
	/// <param name="y">: 추가된 인덱스의 y 좌표</param>
	/// <returns>좌표 추가에 성공하면 true, 실패하면 false를 반환합니다.</returns>
	bool AddPoint(int x, int y);

	/// <summary>
	/// 인덱스와 새로운 좌표를 사용하여 좌표로 이동합니다.
	/// </summary>
	/// <param name="index">: 이동할 점의 인덱스</param>
	/// <param name="x">: 이동할 점의 좌표</param>
	/// <param name="y">: 이동할 점의 좌표</param>
	void MovePoint(int index, int x, int y);

	/// <summary>
	/// 경계 범위 내에서 무작위로 좌표를 이동합니다.
	/// </summary>
	/// <param name="boundary">: 지정할 경계 사각형</param>
	void RandomMove(const CRect& boundary);

	/// <summary>
	/// 전달받은 현재 좌표와 저장하고 있는 좌표의 거리와 전달받은 반지름을 사용하여 해당 좌표의 인덱스를 찾습니다.
	/// </summary>
	/// <param name="x">: 현재 x 좌표</param>
	/// <param name="y">: 현재 y 좌표</param>
	/// <param name="pointRadius">: 현재 설정한 반지름</param>
	/// <returns>: 찾은 점의 인덱스</returns>
	int FindPointIndex(int x, int y, int pointRadius) const;

	/// 점이 최대 개수인지(점이 3개 이상인지)
    bool IsPointFull() const;
	/// 원을 그릴 수 있는지(점이 3개가 되었는지)
	bool CanDrawCircle() const;

public:
	std::vector<PointModel> m_points; // 점 모델들
	CircleModel m_circle; // 원 모델

	bool m_isCircleFromMultiPoints = false; // 원이 유효한지
	bool m_isDragging = false; // 드래그 중인지

	int m_selectedIndex = INVALID_INDEX; // 선택된 점의 인덱스 (디폴트 > INVALID_INDEX)
};