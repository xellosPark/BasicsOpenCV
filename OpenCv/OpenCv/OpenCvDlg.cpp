
// OpenCvDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "OpenCv.h"
#include "OpenCvDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

#define CAM_VIEW_SIZE_FRAME_WIDTH   320
#define CAM_VIEW_SIZE_FRAME_HEIGHT  240

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
#define MESSAGE_VIDOEO_REC	WM_USER


COpenCvDlg::COpenCvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	SetViewRot(0);
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
	ON_BN_CLICKED(IDC_BTN_LIVE_REC_PLAY, &COpenCvDlg::OnBnClickedBtnLiveRecPlay)
	ON_BN_CLICKED(IDC_BTN_LIVE_REC_STOP, &COpenCvDlg::OnBnClickedBtnLiveRecStop)
	ON_MESSAGE(MESSAGE_VIDOEO_REC, &COpenCvDlg::UpdateVidoRec)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_R_0, IDC_RADIO_R_270, &COpenCvDlg::OnBnClickedRadioViewRotation)
	ON_BN_CLICKED(IDC_BNT_TEST, &COpenCvDlg::OnBnClickedBntTest)
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
	CheckRadioButton(IDC_RADIO_R_0, IDC_RADIO_R_270, IDC_RADIO_R_0);
	

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
		cv::destroyAllWindows();
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
		cv::destroyAllWindows();
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
		cv::destroyAllWindows();
		
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
	
	VideoCapture *cap = NULL;
	cap = new VideoCapture(0);

	if (cap->isOpened() == FALSE)
	{
		AfxMessageBox(_T("ķ�� �����ϴ�."));
		cap->release();
		return;
	}
	// ���� �ʺ�� ����
	//double�� ��������, OpenCV���� �����ϴ�, �ݿø� �Լ��� cvRound()�� ����ؼ� ������ ��ȯ�ϸ� �˴ϴ�.
	//int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	//int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	//��ķ ũ�⸦  320x240���� ����    	
	cap->set(CAP_PROP_FRAME_WIDTH, CAM_VIEW_SIZE_FRAME_WIDTH);
	cap->set(CAP_PROP_FRAME_HEIGHT, CAM_VIEW_SIZE_FRAME_HEIGHT);


	//int nSel = GetCheckedRadioButton(IDC_RADIO_R_0, IDC_RADIO_R_270);
	// ���� ���� �Լ�
	Mat frame, inversed;
	while (true)
	{ 
		*cap >> frame;
		// �ش� ������ ������ ��� ������ ��������
		if ( frame.empty() )	
		{
			AfxMessageBox(_T("������ ������ EMPTY �����Դϴ�."));
			cap->release();
			break;
		}

		// ���� ȸ��
		Point Center(CAM_VIEW_SIZE_FRAME_WIDTH / 2, CAM_VIEW_SIZE_FRAME_HEIGHT / 2);
		// getRotationMatrix2D( �߽���, ȸ�� ����, ũŰ ��� )
		Mat metRotation = getRotationMatrix2D(Center, GetViewRot(), 1);
		cv::flip(frame, frame, 1); //0:���� 1:�¿� ���� -1:�����¿� ����
		warpAffine(frame, frame, metRotation, frame.size());
		inversed = ~frame;

		imshow("frame", frame);
		//imshow("inversed", inversed);

		// ECS Key
		if ( waitKey(10) == 27)
		{
			cap->release();
			break; 
		}
	}
	cv::destroyAllWindows();
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
		cv::destroyAllWindows();
		


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
	while (true)
	{
		cap >> frame;
		if ( frame.empty() )
			break;

		inversed = ~frame;
		//outputVideo << inversed;
		outputVideo << frame;

		imshow("frame", frame);
		//imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	cv::destroyAllWindows();
}

BOOL COpenCvDlg::SetLiveView()
{
	//mat_frame�� �Է� �̹����Դϴ�. 
	captureLive->read(mat_frame);
	
	if (mat_frame.empty())
	{
		return FALSE;
	}
	
	//�̰��� OpenCV �Լ����� �����մϴ�.
	//���⿡���� �׷��̽����� �̹����� ��ȯ�մϴ�.
	//cvtColor(mat_frame, mat_frame, COLOR_BGR2GRAY);

	//ȭ�鿡 �����ֱ� ���� ó���Դϴ�.
	int bpp = 8 * mat_frame.elemSize();
// 	assert((bpp == 8 || bpp == 24 || bpp == 32));
// 
// 	int padding = 0;
// 	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
// 	if (bpp < 32)
// 		padding = 4 - (mat_frame.cols % 4);
// 
// 	if (padding == 4)
// 		padding = 0;
// 
// 	int border = 0;
// 	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
// 	if (bpp < 32)
// 	{
// 		border = 4 - (mat_frame.cols % 4);
// 	}
// 
// 	Mat mat_temp;
// 	if (border > 0 || mat_frame.isContinuous() == false)
// 	{
// 		// Adding needed columns on the right (max 3 px)
// 		cv::copyMakeBorder(mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
// 	}
// 	else
// 	{
// 		mat_temp = mat_frame;
// 	}		

	CreateBitmapInfo(mat_frame.cols, mat_frame.rows, bpp);

// 	CStatic *p_Picture = (CStatic *)GetDlgItem(IDC_PICTURE_LIVE);
// 	RECT r;
// 	p_Picture->GetClientRect(&r);
// 	//m_picture.GetClientRect(&r);
// 	cv::Size winSize(r.right, r.bottom);
// 	cimage_mfc.Create(winSize.width, winSize.height, 24);
// 
// 
// 	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
// 	bitInfo->bmiHeader.biBitCount = bpp;
// 	bitInfo->bmiHeader.biWidth = mat_temp.cols;
// 	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
// 	bitInfo->bmiHeader.biPlanes = 1;
// 
// 	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
// 	bitInfo->bmiHeader.biCompression = BI_RGB;
// 	bitInfo->bmiHeader.biClrImportant = 0;
// 	bitInfo->bmiHeader.biClrUsed = 0;
// 	bitInfo->bmiHeader.biSizeImage = 0;
// 	bitInfo->bmiHeader.biXPelsPerMeter = 0;
// 	bitInfo->bmiHeader.biYPelsPerMeter = 0;
// 
// 
// 	//�׷��̽����� �ΰ�� �ȷ�Ʈ�� �ʿ�
// 	if (bpp == 8)
// 	{
// 		RGBQUAD* palette = bitInfo->bmiColors;
// 		for (int i = 0; i < 256; i++)
// 		{
// 			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
// 			palette[i].rgbReserved = 0;
// 		}
// 	}
// 
// 	// Image is bigger or smaller than into destination rectangle
// 	// we use stretch in full rect
// 	if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height)
// 	{
// 		// source and destination have same size
// 		// transfer memory block
// 		// NOTE: the padding border will be shown here. Anyway it will be max 3px width
// 
// 		SetDIBitsToDevice(cimage_mfc.GetDC(),
// 			//destination rectangle
// 			0, 0, winSize.width, winSize.height,
// 			0, 0, 0, mat_temp.rows,
// 			mat_temp.data, bitInfo, DIB_RGB_COLORS);
// 	}
// 	else
// 	{
// 		// destination rectangle
// 		int destx = 0, desty = 0;
// 		int destw = winSize.width;
// 		int desth = winSize.height;
// 
// 		// rectangle defined on source bitmap
// 		// using imgWidth instead of mat_temp.cols will ignore the padding border
// 		int imgx = 0, imgy = 0;
// 		int imgWidth = mat_temp.cols - border;
// 		int imgHeight = mat_temp.rows;
// 
// 		StretchDIBits(cimage_mfc.GetDC(),
// 			destx, desty, destw, desth,
// 			imgx, imgy, imgWidth, imgHeight,
// 			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
// 	}
// 	
// 	HDC dc = ::GetDC(p_Picture->m_hWnd);
// 	cimage_mfc.BitBlt(dc, 0, 0);
// 
// 	::ReleaseDC(p_Picture->m_hWnd, dc);
// 	cimage_mfc.ReleaseDC();
// 	cimage_mfc.Destroy();

	return TRUE;
}


void COpenCvDlg::OnBnClickedBtnLiveRecPlay()
{
	// Rec start
	if (m_bVidoRec == FALSE)
	{
		captureLive = new VideoCapture(0);
		if (!captureLive->isOpened())
		{
			AfxMessageBox(_T("������ ������ EMPTY �����Դϴ�."));
			return;
		}

		int w = cvRound(captureLive->get(CAP_PROP_FRAME_WIDTH));
		int h = cvRound(captureLive->get(CAP_PROP_FRAME_HEIGHT));


		m_bVidoRec = TRUE;
		m_isWorkingThread = TRUE;
		m_pThread = AfxBeginThread(ThreadForCounting, this);
	}
}

UINT COpenCvDlg::ThreadForCounting(LPVOID param)
{
	COpenCvDlg* pMain = (COpenCvDlg*)param;

	while (pMain->m_isWorkingThread)
	{
		Sleep(30);
		pMain->SendMessage(MESSAGE_VIDOEO_REC, NULL, NULL);
	}

	return 0;
}

LRESULT COpenCvDlg::UpdateVidoRec(WPARAM wParam, LPARAM lParam)
{
	if (m_bVidoRec == FALSE)
	{
		return 0L;
	}

	SetLiveView();
	return 0L;
}


void COpenCvDlg::OnBnClickedBtnLiveRecStop()
{
	if (m_bVidoRec == FALSE)
	{
		return;
	}
	m_bVidoRec = FALSE;
	m_isWorkingThread = FALSE;
	WaitForSingleObject(m_pThread->m_hThread, 5);

	if (captureLive != nullptr)
	{
		delete captureLive;
		captureLive = nullptr;
	}
}

void COpenCvDlg::CreateBitmapInfo(int w, int h, int bpp)
{

	BITMAPINFO* bitInfo = nullptr;

	if (bpp == 8)
		bitInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		bitInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			bitInfo->bmiColors[i].rgbBlue = (BYTE)i;
			bitInfo->bmiColors[i].rgbGreen = (BYTE)i;
			bitInfo->bmiColors[i].rgbRed = (BYTE)i;
			bitInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	bitInfo->bmiHeader.biWidth = w;
	bitInfo->bmiHeader.biHeight = -h;

	DrawImage(bitInfo);

	if (bitInfo != NULL)
	{
		delete[]bitInfo;
		bitInfo = NULL;
	}
}

void COpenCvDlg::DrawImage(BITMAPINFO *bitInfo)
{
	CClientDC dc(GetDlgItem(IDC_PICTURE_LIVE));

	CRect rect;
	GetDlgItem(IDC_PICTURE_LIVE)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, mat_frame.cols, mat_frame.rows, mat_frame.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);

}

void COpenCvDlg::OnBnClickedRadioViewRotation(UINT nID)
{
	int iRotType = nID - IDC_RADIO_R_0;
	int iRotRulet(0);
	switch (iRotType)
	{
	case 0: SetViewRot(0);   break;
	case 1: SetViewRot(90);  break;
	case 2: SetViewRot(180); break;
	case 3: SetViewRot(270); break;
	default:SetViewRot(0);   break;
	}

}

void COpenCvDlg::UdateDataPictureBackground()
{
	
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_PICTURE_MUNU);
	CDC* pDC = staticSize->GetWindowDC();
	COLORREF filColor = RGB(218, 217, 255);
	CPen*	pOldPen, NewPen;
	CBrush* pOldBrush, NewBrush(filColor);

	pOldBrush = pDC->SelectObject(&NewBrush);
	NewPen.CreatePen(PS_SOLID, 5, RGB(192, 0, 0));
	pOldPen = pDC->SelectObject(&NewPen);


	CRect rect;
	int iWidth = 0;
	int iHeight = 0;


	staticSize->GetClientRect(rect);
	iWidth = rect.Width();
	iHeight = rect.Height();

	pDC->FillRect(rect, &NewBrush);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);


	NewPen.DeleteObject();
	NewBrush.DeleteObject();

	ReleaseDC(pDC);
}



void COpenCvDlg::OnBnClickedBntTest()
{
	UdateDataPictureBackground();
}
