#include "pch.h"
#include "framework.h"
#include "TextControlDlg.h"
#include "afxdialogex.h"

// C 언어 표준 라이브러리 포함
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 좌표 구조체 정의 (C 언어 스타일)
typedef struct {
    int x;
    int y;
    int width;
    int height;
} TextControlCoords;

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

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 텍스트 컨트롤에 초기 텍스트 설정
	m_textControl1.SetWindowText(_T("Text Control 1"));
	m_textControl2.SetWindowText(_T("Text Control 2"));
	m_textControl3.SetWindowText(_T("Text Control 3"));

	return TRUE;
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

void CTextControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

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
		if (LoadCoordinatesFromFile_CStyle(filePath))
		{
			MessageBox(_T("좌표가 성공적으로 로드되었습니다."), _T("성공"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(_T("좌표 파일을 읽는데 실패했습니다."), _T("오류"), MB_OK | MB_ICONERROR);
		}
	}
}

// 순수 C 언어 스타일 파일 읽기 함수
BOOL CTextControlDlg::LoadCoordinatesFromFile_CStyle(const CString& filename)
{
	// CString을 ANSI 문자열로 변환
	CT2A converter(filename);
	char* filePath = converter;
	
	// C 언어 스타일 파일 열기
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filePath, "r");
	
	if (err != 0 || file == NULL)
	{
		return FALSE;
	}

	char line[512];        // 라인 버퍼
	char* token;           // 토큰 포인터
	char* context = NULL;  // strtok_s 컨텍스트
	int controlIndex = 0;
	TextControlCoords coords;
	
	// 파일에서 한 줄씩 읽기 (C 언어 방식)
	while (fgets(line, sizeof(line), file) != NULL && controlIndex < 3)
	{
		// 줄 끝의 개행 문자 제거
		size_t len = strlen(line);
		if (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
		{
			line[len-1] = '\0';
			if (len > 1 && line[len-2] == '\r')
				line[len-2] = '\0';
		}
		
		// 주석 라인이나 빈 라인 건너뛰기
		if (line[0] == '#' || line[0] == '\0' || strlen(line) == 0)
		{
			continue;
		}

		// C 언어 방식 1: sscanf_s를 사용한 파싱
		int x, y, width, height;
		if (sscanf_s(line, "%d %d %d %d", &x, &y, &width, &height) == 4)
		{
			coords.x = x;
			coords.y = y;
			coords.width = width;
			coords.height = height;
			
			// 텍스트 컨트롤 위치 업데이트
			UpdateTextControlPosition_CStyle(controlIndex, &coords);
			controlIndex++;
		}
		else
		{
			// C 언어 방식 2: strtok_s를 사용한 파싱 (대안적 방법)
			int values[4];
			int valueIndex = 0;
			
			token = strtok_s(line, " \t", &context);
			while (token != NULL && valueIndex < 4)
			{
				values[valueIndex] = atoi(token);
				valueIndex++;
				token = strtok_s(NULL, " \t", &context);
			}
			
			if (valueIndex == 4)
			{
				coords.x = values[0];
				coords.y = values[1];
				coords.width = values[2];
				coords.height = values[3];
				
				UpdateTextControlPosition_CStyle(controlIndex, &coords);
				controlIndex++;
			}
		}
	}

	fclose(file);
	return (controlIndex > 0);
}

// 순수 C 언어 스타일 컨트롤 위치 업데이트 함수
void CTextControlDlg::UpdateTextControlPosition_CStyle(int controlIndex, const TextControlCoords* coords)
{
	if (coords == NULL)
		return;
		
	CWnd* pControl = NULL;
	
	// C 언어 스타일 switch 문
	switch (controlIndex)
	{
	case 0:
		pControl = GetDlgItem(IDC_TEXT_CONTROL1);
		break;
	case 1:
		pControl = GetDlgItem(IDC_TEXT_CONTROL2);
		break;
	case 2:
		pControl = GetDlgItem(IDC_TEXT_CONTROL3);
		break;
	default:
		return;
	}
	
	if (pControl != NULL && pControl->GetSafeHwnd() != NULL)
	{
		// 컨트롤의 위치와 크기 변경
		pControl->SetWindowPos(NULL, 
			coords->x, coords->y, 
			coords->width, coords->height,
			SWP_NOZORDER | SWP_SHOWWINDOW);

		// 다이얼로그 새로 그리기
		Invalidate();
		UpdateWindow();
	}
}

// 대안적인 순수 C 언어 파일 읽기 함수 (더 기본적인 방식)
BOOL CTextControlDlg::LoadCoordinatesFromFile_BasicC(const CString& filename)
{
	// CString을 char*로 변환
	CT2A converter(filename);
	char* fileName = converter;
	
	// 더 기본적인 C 언어 파일 열기
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return FALSE;
	}

	int coordIndex = 0;
	char buffer[256];
	
	while (fgets(buffer, sizeof(buffer), file) != NULL && coordIndex < 3)
	{
		// 주석이나 빈 줄 건너뛰기
		if (buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '\r')
			continue;
			
		// 수동 파싱 (더 기본적인 C 방식)
		char* ptr = buffer;
		int values[4];
		int valueCount = 0;
		
		// 공백으로 구분된 숫자들을 수동으로 파싱
		while (*ptr != '\0' && valueCount < 4)
		{
			// 공백 건너뛰기
			while (*ptr == ' ' || *ptr == '\t')
				ptr++;
				
			if (*ptr == '\0')
				break;
				
			// 숫자 읽기
			values[valueCount] = 0;
			while (*ptr >= '0' && *ptr <= '9')
			{
				values[valueCount] = values[valueCount] * 10 + (*ptr - '0');
				ptr++;
			}
			valueCount++;
			
			// 다음 공백까지 이동
			while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n')
				ptr++;
		}
		
		if (valueCount == 4)
		{
			TextControlCoords coords;
			coords.x = values[0];
			coords.y = values[1];
			coords.width = values[2];
			coords.height = values[3];
			
			UpdateTextControlPosition_CStyle(coordIndex, &coords);
			coordIndex++;
		}
	}
	
	fclose(file);
	return (coordIndex > 0);
}