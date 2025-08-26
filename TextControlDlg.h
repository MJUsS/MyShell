#pragma once

// CTextControlDlg 대화 상자

class CTextControlDlg : public CDialogEx
{
// 생성입니다.
public:
	CTextControlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTCONTROL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedLoadCoordinates();
	DECLARE_MESSAGE_MAP()

private:
	// 좌표 구조체
	struct TextControlCoords {
		int x, y, width, height;
	};

	// 멤버 함수
	BOOL LoadCoordinatesFromFile(const CString& filename);
	void UpdateTextControlPosition(int controlID, const TextControlCoords& coords);

public:
	// 컨트롤 변수
	CStatic m_textControl1;
	CStatic m_textControl2;
	CStatic m_textControl3;
	CButton m_btnLoadCoords;
};