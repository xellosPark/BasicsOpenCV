
// OpenCvDlg.h : 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>

// COpenCvDlg 대화 상자
class COpenCvDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenCvDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:

	VideoCapture *captureLive;
	Mat mat_frame;
	CImage cimage_mfc;


	afx_msg void OnBnClickedBtnImageLoad();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnMetCopy();
	afx_msg void OnBnClickedBtnMetImagePart();
	afx_msg void OnBnClickedBtnVidoeoLoad2();
	afx_msg void OnBnClickedBtnVidoeoPlay();
	afx_msg void OnBnClickedBtnVidoeoSave();
	BOOL SetLiveView();
	afx_msg void OnBnClickedBtnLiveRecPlay();


	static UINT ThreadForCounting(LPVOID param);
	void CreateBitmapInfo(int w, int h, int bpp);
	void DrawImage(BITMAPINFO *bitInfo);
	BOOL m_bVidoRec = FALSE;
	BOOL m_isWorkingThread = FALSE;
	CWinThread* m_pThread = nullptr;
	afx_msg void OnBnClickedBtnLiveRecStop();

	LRESULT UpdateVidoRec(WPARAM wParam, LPARAM lParam);



};
