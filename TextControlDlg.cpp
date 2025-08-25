#include "pch.h"
#include "TextControlDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <sstream>

// CTextControlDlg 대화 상자

IMPLEMENT_DYNAMIC(CTextControlDlg, CDialogEx)

CTextControlDlg::CTextControlDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TEXTCONTROL_DIALOG, pParent)
{
    // 좌표 초기화
    memset(m_coordinates, 0, sizeof(m_coordinates));
    memset(m_originalCoords, 0, sizeof(m_originalCoords));
}

CTextControlDlg::~CTextControlDlg()
{
}

void CTextControlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TEXT_CONTROL1, m_textControl1);
    DDX_Control(pDX, IDC_TEXT_CONTROL2, m_textControl2);
    DDX_Control(pDX, IDC_TEXT_CONTROL3, m_textControl3);
}

BEGIN_MESSAGE_MAP(CTextControlDlg, CDialogEx)
    ON_BN_CLICKED(IDC_LOAD_COORDINATES, &CTextControlDlg::OnBnClickedLoadCoordinates)
    ON_BN_CLICKED(IDC_RESET_POSITIONS, &CTextControlDlg::OnBnClickedResetPositions)
END_MESSAGE_MAP()

// CTextControlDlg 메시지 처리기

BOOL CTextControlDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 원본 좌표 저장
    CRect rect;
    
    if (m_textControl1.GetSafeHwnd())
    {
        m_textControl1.GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_originalCoords[0] = {rect.left, rect.top, rect.Width(), rect.Height()};
    }
    
    if (m_textControl2.GetSafeHwnd())
    {
        m_textControl2.GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_originalCoords[1] = {rect.left, rect.top, rect.Width(), rect.Height()};
    }
    
    if (m_textControl3.GetSafeHwnd())
    {
        m_textControl3.GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_originalCoords[2] = {rect.left, rect.top, rect.Width(), rect.Height()};
    }

    // 텍스트 컨트롤에 초기 텍스트 설정
    m_textControl1.SetWindowText(_T("텍스트 컨트롤 1"));
    m_textControl2.SetWindowText(_T("텍스트 컨트롤 2"));
    m_textControl3.SetWindowText(_T("텍스트 컨트롤 3"));

    return TRUE;
}

void CTextControlDlg::OnBnClickedLoadCoordinates()
{
    // 파일 선택 대화상자
    CFileDialog dlg(TRUE, _T("txt"), _T("coordinates.txt"),
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));

    if (dlg.DoModal() == IDOK)
    {
        CString filePath = dlg.GetPathName();
        
        if (LoadCoordinatesFromFile(filePath))
        {
            // 텍스트 컨트롤들의 위치 변경
            MoveTextControl(&m_textControl1, m_coordinates[0]);
            MoveTextControl(&m_textControl2, m_coordinates[1]);
            MoveTextControl(&m_textControl3, m_coordinates[2]);
            
            // 화면 갱신
            Invalidate();
            
            MessageBox(_T("좌표를 성공적으로 로드하여 적용했습니다."), _T("성공"), MB_OK | MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(_T("좌표 파일을 읽는데 실패했습니다."), _T("오류"), MB_OK | MB_ICONERROR);
        }
    }
}

void CTextControlDlg::OnBnClickedResetPositions()
{
    // 원본 위치로 복원
    MoveTextControl(&m_textControl1, m_originalCoords[0]);
    MoveTextControl(&m_textControl2, m_originalCoords[1]);
    MoveTextControl(&m_textControl3, m_originalCoords[2]);
    
    // 화면 갱신
    Invalidate();
    
    MessageBox(_T("텍스트 컨트롤들을 원래 위치로 복원했습니다."), _T("복원 완료"), MB_OK | MB_ICONINFORMATION);
}

BOOL CTextControlDlg::LoadCoordinatesFromFile(const CString& filePath)
{
    // C 스타일 파일 읽기 (C언어 스타일)
    FILE* file = nullptr;
    errno_t err = _tfopen_s(&file, filePath, _T("r"));
    
    if (err != 0 || file == nullptr)
    {
        return FALSE;
    }

    char line[256];
    int coordIndex = 0;
    
    while (fgets(line, sizeof(line), file) && coordIndex < 3)
    {
        // 주석 라인이나 빈 라인 건너뛰기
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r')
            continue;
            
        // 좌표 파싱 (x, y, width, height)
        int x, y, width, height;
        if (sscanf_s(line, "%d %d %d %d", &x, &y, &width, &height) == 4)
        {
            m_coordinates[coordIndex].x = x;
            m_coordinates[coordIndex].y = y;
            m_coordinates[coordIndex].width = width;
            m_coordinates[coordIndex].height = height;
            coordIndex++;
        }
    }
    
    fclose(file);
    
    // 3개의 좌표를 모두 읽었는지 확인
    return (coordIndex == 3);
}

void CTextControlDlg::MoveTextControl(CWnd* pControl, const Coordinates& coords)
{
    if (pControl && pControl->GetSafeHwnd())
    {
        // 컨트롤의 위치와 크기 변경
        pControl->MoveWindow(coords.x, coords.y, coords.width, coords.height, TRUE);
    }
}

// 대안적인 파일 읽기 방법 (더 순수한 C 스타일)
/*
BOOL CTextControlDlg::LoadCoordinatesFromFile_CStyle(const CString& filePath)
{
    // CString을 char*로 변환
    CT2A converter(filePath);
    char* fileName = converter;
    
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
        if (buffer[0] == '#' || buffer[0] == '\n')
            continue;
            
        // strtok을 사용한 파싱
        char* token = strtok(buffer, " \t\n");
        if (token == NULL) continue;
        
        int values[4];
        int valueIndex = 0;
        
        while (token != NULL && valueIndex < 4)
        {
            values[valueIndex] = atoi(token);
            valueIndex++;
            token = strtok(NULL, " \t\n");
        }
        
        if (valueIndex == 4)
        {
            m_coordinates[coordIndex].x = values[0];
            m_coordinates[coordIndex].y = values[1];
            m_coordinates[coordIndex].width = values[2];
            m_coordinates[coordIndex].height = values[3];
            coordIndex++;
        }
    }
    
    fclose(file);
    return (coordIndex == 3);
}
*/