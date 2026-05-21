
// GlimCircleDrawAppDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimCircleDrawApp.h"
#include "GlimCircleDrawAppDlg.h"
#include "afxdialogex.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimCircleDrawAppDlg 대화 상자



CGlimCircleDrawAppDlg::CGlimCircleDrawAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMCIRCLEDRAWAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pController = std::make_unique<MainController>(this); // 컨트롤러 객체 생성
}

void CGlimCircleDrawAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGlimCircleDrawAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()

	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGlimCircleDrawAppDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM_MOVE, &CGlimCircleDrawAppDlg::OnBnClickedButtonRandomMove)
END_MESSAGE_MAP()


// CGlimCircleDrawAppDlg 메시지 처리기

BOOL CGlimCircleDrawAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO : 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemInt(IDC_EDIT_POINT_RADIUS, 10); // 초기 점 반지름 설정
	SetDlgItemInt(IDC_EDIT_CIRCLE_THICKNESS, 2); // 초기 원 두께 설정

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimCircleDrawAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimCircleDrawAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		UpdateSettingsForController(); // 컨트롤러 정보 설정

		InitializeForView(); // 화면 초기화(White)

		if ((!m_image.IsNull()) && (m_pController != nullptr))
		{
			m_pController->Render(m_image); // 렌더링
		}

		m_image.Draw(dc, 0, 0); // 캔버스에 그리기

		UpdatePointinfoForView(); // 점 정보 UI 업데이트
		RandomMoveUpdateForView(); // 랜덤 이동 정보 UI 업데이트
	}
}

void CGlimCircleDrawAppDlg::InitializeForView()
{
	CRect rect;
	int nBpp = 8;
	GetClientRect(&rect);

	// 처음(nullptr)인 경우에만 CImage 생성
	if (m_image.IsNull()) {
		m_image.Create(rect.Width(), rect.Height(), nBpp);
	}
	
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = static_cast<BYTE>(i);
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* pBits = static_cast<unsigned char*>(m_image.GetBits());

	for (int y = 0; y < rect.Height(); y++) {
		for (int x = 0; x < rect.Width(); x++) {
			pBits[y * nPitch + x] = 255; // white
		}
	}
}

BOOL CGlimCircleDrawAppDlg::OnEraseBkgnd(CDC* pDC)
{
	// 배경 지우기 처리 -> 깜박임 감소
	return TRUE;
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimCircleDrawAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlimCircleDrawAppDlg::UpdateSettingsForController()
{
	if (m_pController == nullptr)
		return;

	int pointRadius = GetDlgItemInt(IDC_EDIT_POINT_RADIUS);
	int thickness = GetDlgItemInt(IDC_EDIT_CIRCLE_THICKNESS);

	m_pController->UpdateSettings(pointRadius, thickness);
}

void CGlimCircleDrawAppDlg::UpdatePointinfoForView()
{
	if (m_pController == nullptr)
		return;

	CString text;
	text = m_pController->GetPointInfoText();

	SetDlgItemText(IDC_STATIC_POINT_INFO, text);
}

void CGlimCircleDrawAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pController)
		m_pController->OnLButtonDown(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGlimCircleDrawAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pController)
		m_pController->OnMouseMove(point);

	CDialogEx::OnMouseMove(nFlags, point);
}

void CGlimCircleDrawAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pController)
		m_pController->OnLButtonUp();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGlimCircleDrawAppDlg::OnBnClickedButtonReset()
{
	if (m_pController)
		m_pController->OnReset();

	GetDlgItem(IDC_BUTTON_RANDOM_MOVE)->EnableWindow(TRUE);
}

void CGlimCircleDrawAppDlg::OnBnClickedButtonRandomMove()
{
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RANDOM_MOVE)->EnableWindow(FALSE);

	bool isStarted = false;
	if (m_pController) {
		isStarted = m_pController->OnRandomMove();
	}

	if (isStarted) {
		return;
	}
	else {
		MessageBox(_T("원을 그려주세요 !"), _T("정보"), MB_OK | MB_ICONINFORMATION);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RANDOM_MOVE)->EnableWindow(TRUE);
	}
}

void CGlimCircleDrawAppDlg::RandomMoveUpdateForView()
{
	if(m_pController == nullptr)
		return;

	int current = m_pController->GetRandomCount();
	int total = RANDOM_MOVE_REPEAT;

	CString text;

	text.Format(_T("랜덤 이동 : %d / %d"), current, total);

	SetDlgItemText(IDC_STATIC_RANDOM_COUNT, text);

	if(current >= total) // 랜덤 이동 종료
	{
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RANDOM_MOVE)->EnableWindow(TRUE);

		Sleep(1000);

		text.Format(_T("랜덤 이동 완료 !"));

		SetDlgItemText(IDC_STATIC_RANDOM_COUNT, text);
	}
}