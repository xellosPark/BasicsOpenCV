
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
	ON_BN_CLICKED(IDC_BTN_MET_COPY, &COpenCvDlg::OnBnClickedBtnMetCopy)
	ON_BN_CLICKED(IDC_BTN_MET_IMAGE_PART, &COpenCvDlg::OnBnClickedBtnMetImagePart)
	ON_BN_CLICKED(IDC_BTN_VIDOEO_LOAD2, &COpenCvDlg::OnBnClickedBtnVidoeoLoad2)
	ON_BN_CLICKED(IDC_BTN_VIDOEO_PLAY, &COpenCvDlg::OnBnClickedBtnVidoeoPlay)
	ON_BN_CLICKED(IDC_BTN_VIDOEO_SAVE, &COpenCvDlg::OnBnClickedBtnVidoeoSave)
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
		destroyAllWindows();
	}
}

void COpenCvDlg::OnBnClickedBtnMetCopy()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	Mat cv_Img1; // �̹��� ������ ��� �ִ� ��ü.
	if (fileDlg.DoModal() == IDOK)
	{

		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);
		
		cv_Img1 = imread(strPath, IMREAD_UNCHANGED);

		if (cv_Img1.empty()) {
			return;
		}

		Mat cv_Img2 = cv_Img1;
		Mat cv_Img3;
		cv_Img3 = cv_Img1;

		Mat cv_Img4 = cv_Img1.clone(); // ���� ����
		Mat cv_Img5; cv_Img1.copyTo(cv_Img5); // ���� ����

		cv_Img1.setTo(Scalar(0,255,255)); // yellow
		
		
		imshow("img1", cv_Img1); // "Image"��� �̸��� â�� �̹����� �־� ������
		imshow("img2", cv_Img2); // "Image"��� �̸��� â�� �̹����� �־� ������
		imshow("img3", cv_Img3); // "Image"��� �̸��� â�� �̹����� �־� ������
		imshow("img4", cv_Img4); // "Image"��� �̸��� â�� �̹����� �־� ������
		imshow("img5", cv_Img5); // "Image"��� �̸��� â�� �̹����� �־� ������
								 // waitKey(int delay)	 
		waitKey(); // ���� Ű ���
		destroyAllWindows();
	}
}

void COpenCvDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

}


void COpenCvDlg::OnBnClickedBtnMetImagePart()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	Mat cv_Img1; // �̹��� ������ ��� �ִ� ��ü.
	if (fileDlg.DoModal() == IDOK)
	{

		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);

		cv_Img1 = imread(strPath, IMREAD_UNCHANGED);
		if (cv_Img1.empty()){
			return;
		}

		
		Mat cv_Img2 = cv_Img1(Rect(10, 10, 200, 200));
		Mat cv_Img3 = cv_Img1(Rect(10, 10, 200, 200)).clone(); // ���� ����

		//~ NOT ������ ���� ����
		cv_Img2 = ~cv_Img2;


		
		imshow("image", cv_Img2); // "Image"��� �̸��� â�� �̹����� �־� ������
		imshow("image2", cv_Img3); // "Image"��� �̸��� â�� �̹����� �־� ������
		waitKey(); // ���� Ű ���
		destroyAllWindows();
		
	}
}


void COpenCvDlg::OnBnClickedBtnVidoeoLoad2()
{
	//////////////////////////////////////////////////////////////////////////
	// ** VideoCaptureAPIs ������ ��� ����
	//CAP_ANY									- �ڵ� ����
	//CAP_V4L, CAP_V4L2							- V4L / V4L2(������)
	//CAP_FIREWIRE, CAP_FIREWARE, CAP_IEEE1394	- IEEE 1394 ����̹�
	//CAP_DSHOW									- ���̷�Ʈ��(DirectShow)
	//CAP_PVAPI									- PvAPI, Prosilica GigE SDK
	//CAP_OPENNI								- OpenNI
	//CAP_MSMF									- ����ũ�μ���Ʈ �̵�� �Ŀ�̼�
	//CAP_GSTREAMER								- GStreamer
	//CAP__FFMPEG								- FFMPEG ���̺귯��
	//CAP_IMAGES								- OpenCV���� �����ϴ� �Ϸ��� ��������(���� "img_%02.jpg")
	//CAP_OPENCV_MJPEG							- OpenCV�� ����� MotionJPEG �ڵ�

	// ** index: ī�޶�� ��ġ ��� ��� ������ȣ��,
	//index = camera_id + domain_offset_i�� �̷���� �ֽ��ϴ�. ���� ��ǻ�Ϳ� �Ѵ��� ī�޶� ����Ǿ�����, camera_id�� 0�Դϴ�.
	//�δ� �̻��� ī�޶��� ����, camera_id�� 0���� �����ؼ�, �� ID�� ����մϴ�.
	//domain_offset_id��, ī�޶� ����ϴ� ����� ǥ���ϴ� ���� ������, VideoCaptureAPIs�� ����մϴ�.
	//������, 0(CAP_ANY)�� ����ϴ�, index ���� �ᱹ camera_id�� ���� ����մϴ�.
	

	VideoCapture cap(0);

	if (cap.isOpened() == FALSE)
	{
		AfxMessageBox(_T("ķ�� �����ϴ�."));
		return;
	}
	// ���� �ʺ�� ����
	//double�� ��������, OpenCV���� �����ϴ�, �ݿø� �Լ��� cvRound()�� ����ؼ� ������ ��ȯ�ϸ� �˴ϴ�.
	//int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	//int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	Mat frame, inversed;
	while (true)
	{ 
		cap >> frame;
		// �ش� ������ ������ ��� ������ ��������
		if ( frame.empty())	{ AfxMessageBox(_T("������ ������ EMPTY �����Դϴ�.")); break; }
		
		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		// ECS Key
		if ( waitKey(10) == 27){ break; }
	}
	destroyAllWindows();
}


void COpenCvDlg::OnBnClickedBtnVidoeoPlay()
{
	//////////////////////////////////////////////////////////////////////////
	//-propId
	//VideoCaptureProperties	//����
	//CAP_PROP_POS_MSEC			//���� ���Ͽ��� ���� ��ġ(�и��� ����)
	//CAP_PROP_POS_FRAMES		//���� ������ ��ġ(0 - ���)
	//CAP_PROP_POS_AVI_RATIO	//[0, 1]�������� ǥ���� ������ �������� ����� ��ġ(0: ����, 1 : ��)
	//CAP_PROP_FRAME_WIDTH		//���� �������� ���� ũ��
	//CAP_PROP_FRAME_HEIGHT		//���� �������� ���� ũ��
	//CAP_PROP_FPS				//�ʴ� ������ ��
	//CAP_PROP_FOURCC			//fourcc �ڵ�(�ڵ��� ǥ���ϴ� ���� ��)
	//CAP_PROP_FRAME_COUNT		//���� ������ ��ü ������ ��
	//CAP_PROP_BRIGHTNESS		//(ī�޶󿡼� �����ϴ� ���) ��� ����
	//CAP_PROP_CONTRAST			//(ī�޶󿡼� �����ϴ� ���) ��Ϻ� ����
	//CAP_PROP_SATURATION		//(ī�޶󿡼� �����ϴ� ���) ä�� ����
	//CAP_PROP_HUE				//(ī�޶󿡼� �����ϴ� ���) ���� ����
	//CAP_PROP_GAIN				//(ī�޶󿡼� �����ϴ� ���) ���� ����
	//CAP_PROP_EXPOSURE			//(ī�޶󿡼� �����ϴ� ���) ���� ����
	//CAP_PROP_ZOOM				//(ī�޶󿡼� �����ϴ� ���) �� ����
	//CAP_PROP_FOCUS			//(ī�޶󿡼� �����ϴ� ���) ���� ����



	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("Moving file(*.AVI, *.MP4, *.WMV) | *.AVI;*.MP4;*.WMV | All Files(*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);

		VideoCapture cap(strPath);

		if (!cap.isOpened()) {
			cerr << "Video open failed!" << endl;
			return;
		}
		// "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
		// "Frame height:" << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
		// "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

		double fps = cap.get(CAP_PROP_FPS);
		// "FPS: " << fps << endl;

		int delay = cvRound( 1000 / fps );

		Mat frame, inversed;

		while (true) {
			cap >> frame;
			if (frame.empty())
				break;
			inversed = ~frame;

			imshow("frame", frame);
			//imshow("inversed", inversed);

			if (waitKey(delay) == 27)
				break;
		}
		destroyAllWindows();
		


// 		CClientDC dc(this);
// 		CDC *pDC;
// 		CRect rect;
// 
// 		pDC = m_picCameraWide.GetDC();
// 		m_picCameraWide.GetClientRect(rect);
// 
// 		IplImage *m_PlayFrame;
// 		CvCapture *capture = cvCaptureFromFile(m_PlayFileName);
// 
// 		while (capture)
// 		{
// 			m_PlayFrame = cvQueryFrame(capture);
// 			m_cvvImage.CopyOf((IplImage *)m_PlayFrame);
// 			m_cvvImage.DrawToHDC(pDC->m_hDC, rect);
// 		}
//		cvReleaseCapture(&capture);
//		ReleaseDC(pDC);



	}
}


void COpenCvDlg::OnBnClickedBtnVidoeoSave()
{
	// **(VideoWriter ��ü ����)
	//	- ������ ���� ���� ��Ʈ���� ���ϴ�.
	//
	//	VideoWriter::VideoWriter(const String& filename, int fourcc, double fps,
	//		Size frameSize, bool isColor = true);
	//
	// bool VideoWriter::open(const String& filename, int fourcc, double fps,
	//	Size frameSize, bool isColor = true);
	//: ���� ���� �޼���� �Ǿ��ְ�, �����ڷ� ���ų�, Ȥ�� open �޼���� ���ϴ�.
	//	file : ������ ������ ���� �̸�
	//	fourcc : ������ ���� �ڵ��� ǥ���ϴ� 4 - �����ڵ�
	//	fps : ������ �������� �ʴ� ������ ��
	//	frameSize : ������ �������� ���� �� ���� ũ��
	//	isColor : �� ���� true�̸� �÷� ���������� �����ϰ�, false��, �׷��̽������Դϴ�.�� �÷��״� windows ������ �����մϴ�.
	//	��ȯ�� : ������ true, ���н� false

	//-fourcc : ������ ���Ϸ� �����, �Ӽ��� �����մϴ�. 4���ڷ� �̷���� ������, ���� ���� �ڵ�, ������, ���� Ȥ�� �ȼ� ���� ���� �����ϴ� �������Դϴ�.
	//�� ���� ����, static int VideoWriter::fourcc(char c1, char c2, char c3, char c4);


	//fourcc �ڵ� ���� ���	�ڵ� ����
	//	VideoWriter::fourcc('D', 'I', 'V', 'X')		-DivX MPEG - 4 �ڵ�
	//	VideoWriter::fourcc('X', 'V', 'I', 'D')		-XVID MPEG - 4 �ڵ�
	//	VideoWriter::fourcc('F', 'M', 'P', '4')		-FFMPEG MPEG4 �ڵ�
	//	VideoWriter::fourcc('W', 'M', 'V', '2')		-Windows Media Video 8 �ڵ�
	//	VideoWriter::fourcc('M', 'J', 'P', 'G')		-��� JPEG �ڵ�
	//	VideoWriter::fourcc('Y', 'V', '1', '2')		-YUV 4:2 : 0 Planar(�����)
	//	VideoWriter::fourcc('X', '2', '6', '4')		-H.264 / AVC �ڵ�
	//	VideoWriter::fourcc('A', 'V', 'C', '1')		-Advanced Video �ڵ�

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	double fps = cap.get(CAP_PROP_FPS);
	//int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
	int delay = cvRound(1000 / fps);

	//OpenCV VideoWriter setting
	//codec info
	//https://thebook.io/006939/ch04/01/04-02/

	//VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));
	VideoWriter outputVideo("output.avi", fourcc, 15, Size(w, h));

	if ( outputVideo.isOpened() == FALSE) {
		AfxMessageBox(_T("File open failed!"));
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		//outputVideo << inversed;
		outputVideo << frame;

		imshow("frame", frame);
		//imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}
