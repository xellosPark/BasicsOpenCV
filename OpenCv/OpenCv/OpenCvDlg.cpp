
// OpenCvDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenCv.h"
#include "OpenCvDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace cv;
using namespace std;


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


// COpenCvDlg 대화 상자



COpenCvDlg::COpenCvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenCvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE_LOAD, &COpenCvDlg::OnBnClickedBtnImageLoad)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// COpenCvDlg 메시지 처리기

BOOL COpenCvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	//ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenCvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COpenCvDlg::OnPaint()
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
HCURSOR COpenCvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCvDlg::OnBnClickedBtnImageLoad()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	Mat cv_matImg; // 이미지 정보를 담고 있는 객체.
	if (fileDlg.DoModal() == IDOK)
	{

		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);
		//[2021/10/27/ UBS.PDJ] imread 함수에서 DLL Debug 발생시 Dll 해당 ProJect 폴더에 삽입 필요

// 		cv2.IMREAD_UNCHANGED : 원본 사용
// 		cv2.IMREAD_GRAYSCALE :  1 채널, 그레이스케일 적용
// 		cv2.IMREAD_COLOR :		3 채널, BGR 이미지 사용
// 		cv2.IMREAD_ANYDEPTH :	이미지에 따라 정밀도를 16 / 32비트 또는 8비트로 사용
// 		cv2.IMREAD_ANYCOLOR :	가능한 3 채널, 색상 이미지로 사용
// 		cv2.IMREAD_REDUCED_GRAYSCALE_2 : 1 채널, 1 / 2 크기, 그레이스케일 적용
// 		cv2.IMREAD_REDUCED_GRAYSCALE_4 : 1 채널, 1 / 4 크기, 그레이스케일 적용
// 		cv2.IMREAD_REDUCED_GRAYSCALE_8 : 1 채널, 1 / 8 크기, 그레이스케일 적용
// 		cv2.IMREAD_REDUCED_COLOR_2 : 3 채널, 1 / 2 크기, BGR 이미지 사용
// 		cv2.IMREAD_REDUCED_COLOR_4 : 3 채널, 1 / 4 크기, BGR 이미지 사용
// 		cv2.IMREAD_REDUCED_COLOR_8 : 3 채널, 1 / 8 크기, BGR 이미지 사용

		//imread(불러올 영상 파일 이름, 영상 파일 불러오기 옵션) return 불러온 영상 데이터
		cv_matImg = imread(strPath, IMREAD_UNCHANGED);

		if ( cv_matImg.empty() ) {
			return;
		}

		// Mat 객체에 저정되어 있는 영상을 데이터를 파일로 저장
		// JPEG 압축률 95%로 지정
// 		vector<int> vParams;
// 		vParams.emplace_back(IMWRITE_JPEG_CHROMA_QUALITY);
// 		vParams.emplace_back(95);
//		//imwrite(저정할 영상 파일 이름, 저장할 데이터(Mat 객처), 저정할 영상 파일 형식에 의존적인 파라미터(플러그 & 값) = 정상적으로 저정하면 true, 실패하면 false를 반환)
// 		imwrite(strPath,cv_matImg, vParams);

//		//namedWindow( 영상 출력 창 상단에 출력되는 창 고유 이름, 문자열로 창을 구분)
//		// WINDOW_NORMAL : 원본 이미지 크기로 윈도우를 생성하되 사용자가 크기를 조절할 수 있음
//		// WINDOW_AUTOSIZE : 원본 이미지 크기로 고정해 윈도우를 생성
		namedWindow("image",WINDOW_NORMAL); // 이미지를 보여주기 위한 빈 창
		imshow("image", cv_matImg); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		// waitKey(int delay)	 
		waitKey(); // 종료 키 대기
	}
}


void COpenCvDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	waitKey(); // 종료 키 대기
	Point_
	Size_
}
