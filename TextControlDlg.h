#pragma once
#include "afxdialogex.h"

// CTextControlDlg 대화 상자

class CTextControlDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CTextControlDlg)

public:
    CTextControlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
    virtual ~CTextControlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TEXTCONTROL_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()

public:
    // 텍스트 컨트롤 변수들
    CStatic m_textControl1;
    CStatic m_textControl2;
    CStatic m_textControl3;

    // 함수들
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedLoadCoordinates();
    afx_msg void OnBnClickedResetPositions();

private:
    // 좌표 구조체
    struct Coordinates {
        int x, y, width, height;
    };

    // 파일에서 좌표를 읽는 함수
    BOOL LoadCoordinatesFromFile(const CString& filePath);
    
    // 텍스트 컨트롤의 위치를 변경하는 함수
    void MoveTextControl(CWnd* pControl, const Coordinates& coords);
    
    // 좌표 배열
    Coordinates m_coordinates[3];
    
    // 원본 좌표 저장 (리셋용)
    Coordinates m_originalCoords[3];
};