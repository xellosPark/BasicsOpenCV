
// OpenCvDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// COpenCvDlg ��ȭ ����



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


// COpenCvDlg �޽��� ó����

BOOL COpenCvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	//ShowWindow(SW_MINIMIZE);

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COpenCvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COpenCvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCvDlg::OnBnClickedBtnImageLoad()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	Mat cv_matImg; // �̹��� ������ ��� �ִ� ��ü.
	if (fileDlg.DoModal() == IDOK)
	{

		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);
		//[2021/10/27/ UBS.PDJ] imread �Լ����� DLL Debug �߻��� Dll �ش� ProJect ������ ���� �ʿ�

// 		cv2.IMREAD_UNCHANGED : ���� ���
// 		cv2.IMREAD_GRAYSCALE :  1 ä��, �׷��̽����� ����
// 		cv2.IMREAD_COLOR :		3 ä��, BGR �̹��� ���
// 		cv2.IMREAD_ANYDEPTH :	�̹����� ���� ���е��� 16 / 32��Ʈ �Ǵ� 8��Ʈ�� ���
// 		cv2.IMREAD_ANYCOLOR :	������ 3 ä��, ���� �̹����� ���
// 		cv2.IMREAD_REDUCED_GRAYSCALE_2 : 1 ä��, 1 / 2 ũ��, �׷��̽����� ����
// 		cv2.IMREAD_REDUCED_GRAYSCALE_4 : 1 ä��, 1 / 4 ũ��, �׷��̽����� ����
// 		cv2.IMREAD_REDUCED_GRAYSCALE_8 : 1 ä��, 1 / 8 ũ��, �׷��̽����� ����
// 		cv2.IMREAD_REDUCED_COLOR_2 : 3 ä��, 1 / 2 ũ��, BGR �̹��� ���
// 		cv2.IMREAD_REDUCED_COLOR_4 : 3 ä��, 1 / 4 ũ��, BGR �̹��� ���
// 		cv2.IMREAD_REDUCED_COLOR_8 : 3 ä��, 1 / 8 ũ��, BGR �̹��� ���

		//imread(�ҷ��� ���� ���� �̸�, ���� ���� �ҷ����� �ɼ�) return �ҷ��� ���� ������
		cv_matImg = imread(strPath, IMREAD_UNCHANGED);

		if ( cv_matImg.empty() ) {
			return;
		}

		// Mat ��ü�� �����Ǿ� �ִ� ������ �����͸� ���Ϸ� ����
		// JPEG ����� 95%�� ����
// 		vector<int> vParams;
// 		vParams.emplace_back(IMWRITE_JPEG_CHROMA_QUALITY);
// 		vParams.emplace_back(95);
//		//imwrite(������ ���� ���� �̸�, ������ ������(Mat ��ó), ������ ���� ���� ���Ŀ� �������� �Ķ����(�÷��� & ��) = ���������� �����ϸ� true, �����ϸ� false�� ��ȯ)
// 		imwrite(strPath,cv_matImg, vParams);

//		//namedWindow( ���� ��� â ��ܿ� ��µǴ� â ���� �̸�, ���ڿ��� â�� ����)
//		// WINDOW_NORMAL : ���� �̹��� ũ��� �����츦 �����ϵ� ����ڰ� ũ�⸦ ������ �� ����
//		// WINDOW_AUTOSIZE : ���� �̹��� ũ��� ������ �����츦 ����
		namedWindow("image",WINDOW_NORMAL); // �̹����� �����ֱ� ���� �� â
		imshow("image", cv_matImg); // "Image"��� �̸��� â�� �̹����� �־� ������
		// waitKey(int delay)	 
		waitKey(); // ���� Ű ���
	}
}


void COpenCvDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	waitKey(); // ���� Ű ���
	Point_
	Size_
}
