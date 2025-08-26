#include "pch.h"
#include "framework.h"
#include "TextControlDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <sstream>

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


// CTextControlDlg 대화 상자

CTextControlDlg::CTextControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEXTCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTextControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_CONTROL1, m_textControl1);
	DDX_Control(pDX, IDC_TEXT_CONTROL2, m_textControl2);
	DDX_Control(pDX, IDC_TEXT_CONTROL3, m_textControl3);
	DDX_Control(pDX, IDC_BTN_LOAD_COORDS, m_btnLoadCoords);
}

BEGIN_MESSAGE_MAP(CTextControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD_COORDS, &CTextControlDlg::OnBnClickedLoadCoordinates)
END_MESSAGE_MAP()


// CTextControlDlg 메시지 처리기

BOOL CTextControlDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	// 텍스트 컨트롤에 초기 텍스트 설정
	m_textControl1.SetWindowText(_T("Text Control 1"));
	m_textControl2.SetWindowText(_T("Text Control 2"));
	m_textControl3.SetWindowText(_T("Text Control 3"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTextControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTextControlDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTextControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 좌표 로드 버튼 클릭 이벤트 핸들러
void CTextControlDlg::OnBnClickedLoadCoordinates()
{
	// 파일 선택 대화상자
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("텍스트 파일 (*.txt)|*.txt|모든 파일 (*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();
		if (LoadCoordinatesFromFile(filePath))
		{
			MessageBox(_T("좌표가 성공적으로 로드되었습니다."), _T("성공"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(_T("좌표 파일을 읽는데 실패했습니다."), _T("오류"), MB_OK | MB_ICONERROR);
		}
	}
}

// 파일에서 좌표를 읽어오는 함수
BOOL CTextControlDlg::LoadCoordinatesFromFile(const CString& filename)
{
	std::ifstream file;
	file.open(CStringA(filename));

	if (!file.is_open())
	{
		return FALSE;
	}

	std::string line;
	int controlIndex = 0;
	
	// 파일에서 한 줄씩 읽기
	while (std::getline(file, line) && controlIndex < 3)
	{
		// 주석 라인이나 빈 라인 건너뛰기
		if (line.empty() || line[0] == '#')
		{
			continue;
		}

		// 좌표 파싱
		std::istringstream iss(line);
		TextControlCoords coords;
		
		if (iss >> coords.x >> coords.y >> coords.width >> coords.height)
		{
			// 각 텍스트 컨트롤의 위치 업데이트
			switch (controlIndex)
			{
			case 0:
				UpdateTextControlPosition(IDC_TEXT_CONTROL1, coords);
				break;
			case 1:
				UpdateTextControlPosition(IDC_TEXT_CONTROL2, coords);
				break;
			case 2:
				UpdateTextControlPosition(IDC_TEXT_CONTROL3, coords);
				break;
			}
			controlIndex++;
		}
	}

	file.close();
	return (controlIndex > 0); // 최소 하나의 좌표는 로드되어야 함
}

// 텍스트 컨트롤의 위치를 업데이트하는 함수
void CTextControlDlg::UpdateTextControlPosition(int controlID, const TextControlCoords& coords)
{
	CWnd* pControl = GetDlgItem(controlID);
	if (pControl != nullptr)
	{
		// 컨트롤의 위치와 크기 변경
		pControl->SetWindowPos(nullptr, 
			coords.x, coords.y, 
			coords.width, coords.height,
			SWP_NOZORDER | SWP_SHOWWINDOW);

		// 다이얼로그 새로 그리기
		Invalidate();
		UpdateWindow();
	}
}