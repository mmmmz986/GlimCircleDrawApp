
// GlimCircleDrawAppDlg.h: 헤더 파일
//

#pragma once

#include <memory>
#include "MainController.h"

// CGlimCircleDrawAppDlg 대화 상자
class CGlimCircleDrawAppDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimCircleDrawAppDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMCIRCLEDRAWAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CImage m_image;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonRandomMove();

	void InitializeForView();
	void UpdateSettingsForController();
	void UpdatePointinfoForView();
	void RandomMoveUpdateForView();

	DECLARE_MESSAGE_MAP()

private:
	std::unique_ptr<MainController> m_pController; // Controller
};
