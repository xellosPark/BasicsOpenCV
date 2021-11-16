
// OpenCvDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenCv.h"
#include "OpenCvDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

#define CAM_VIEW_SIZE_FRAME_WIDTH   320
#define CAM_VIEW_SIZE_FRAME_HEIGHT  240

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
	CheckRadioButton(IDC_RADIO_R_0, IDC_RADIO_R_270, IDC_RADIO_R_0);
	

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
		cv::destroyAllWindows();
	}
}

void COpenCvDlg::OnBnClickedBtnMetCopy()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	Mat cv_Img1; // 이미지 정보를 담고 있는 객체.
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

		Mat cv_Img4 = cv_Img1.clone(); // 깊은 복사
		Mat cv_Img5; cv_Img1.copyTo(cv_Img5); // 깊은 복사

		cv_Img1.setTo(Scalar(0,255,255)); // yellow
		
		
		imshow("img1", cv_Img1); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		imshow("img2", cv_Img2); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		imshow("img3", cv_Img3); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		imshow("img4", cv_Img4); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		imshow("img5", cv_Img5); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
								 // waitKey(int delay)	 
		waitKey(); // 종료 키 대기
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
	Mat cv_Img1; // 이미지 정보를 담고 있는 객체.
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
		Mat cv_Img3 = cv_Img1(Rect(10, 10, 200, 200)).clone(); // 깊은 복사

		//~ NOT 연산자 색상 반전
		cv_Img2 = ~cv_Img2;


		
		imshow("image", cv_Img2); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		imshow("image2", cv_Img3); // "Image"라는 이름의 창에 이미지를 넣어 보여줌
		waitKey(); // 종료 키 대기
		cv::destroyAllWindows();
		
	}
}


void COpenCvDlg::OnBnClickedBtnVidoeoLoad2()
{
	//////////////////////////////////////////////////////////////////////////
	// ** VideoCaptureAPIs 열거형 상수 설명
	//CAP_ANY									- 자동 선택
	//CAP_V4L, CAP_V4L2							- V4L / V4L2(리눅스)
	//CAP_FIREWIRE, CAP_FIREWARE, CAP_IEEE1394	- IEEE 1394 드라이버
	//CAP_DSHOW									- 다이렉트쇼(DirectShow)
	//CAP_PVAPI									- PvAPI, Prosilica GigE SDK
	//CAP_OPENNI								- OpenNI
	//CAP_MSMF									- 마이크로소프트 미디어 파운데이션
	//CAP_GSTREAMER								- GStreamer
	//CAP__FFMPEG								- FFMPEG 라이브러리
	//CAP_IMAGES								- OpenCV에서 지원하는 일련의 영상파일(예시 "img_%02.jpg")
	//CAP_OPENCV_MJPEG							- OpenCV에 내장된 MotionJPEG 코덱

	// ** index: 카메라와 장치 사용 방식 지정번호로,
	//index = camera_id + domain_offset_i로 이루어져 있습니다. 만약 컴퓨터에 한대의 카메라만 연결되었으면, camera_id는 0입니다.
	//두대 이상의 카메라의 경우는, camera_id가 0부터 시작해서, 각 ID를 사용합니다.
	//domain_offset_id는, 카메라를 사용하는 방식을 표현하는 정수 값으로, VideoCaptureAPIs를 사용합니다.
	//보통은, 0(CAP_ANY)를 사용하니, index 값은 결국 camera_id와 같이 사용합니다.
	
	VideoCapture *cap = NULL;
	cap = new VideoCapture(0);

	if (cap->isOpened() == FALSE)
	{
		AfxMessageBox(_T("캠을 없습니다."));
		cap->release();
		return;
	}
	// 각각 너비와 높이
	//double로 가져오니, OpenCV에서 제공하는, 반올림 함수인 cvRound()를 사용해서 정수로 변환하면 됩니다.
	//int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	//int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	//웹캠 크기를  320x240으로 지정    	
	cap->set(CAP_PROP_FRAME_WIDTH, CAM_VIEW_SIZE_FRAME_WIDTH);
	cap->set(CAP_PROP_FRAME_HEIGHT, CAM_VIEW_SIZE_FRAME_HEIGHT);


	//int nSel = GetCheckedRadioButton(IDC_RADIO_R_0, IDC_RADIO_R_270);
	// 영상 반전 함수
	Mat frame, inversed;
	while (true)
	{ 
		*cap >> frame;
		// 해당 프레임 영상이 비어 있으면 빠져나감
		if ( frame.empty() )	
		{
			AfxMessageBox(_T("프레임 영상이 EMPTY 상태입니다."));
			cap->release();
			break;
		}

		// 영상 회전
		Point Center(CAM_VIEW_SIZE_FRAME_WIDTH / 2, CAM_VIEW_SIZE_FRAME_HEIGHT / 2);
		// getRotationMatrix2D( 중심점, 회전 각도, 크키 배울 )
		Mat metRotation = getRotationMatrix2D(Center, GetViewRot(), 1);
		cv::flip(frame, frame, 1); //0:정상 1:좌우 반전 -1:상하좌우 반전
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
	//VideoCaptureProperties	//설명
	//CAP_PROP_POS_MSEC			//비디오 파일에서 현재 위치(밀리초 단위)
	//CAP_PROP_POS_FRAMES		//현재 프레임 위치(0 - 기반)
	//CAP_PROP_POS_AVI_RATIO	//[0, 1]구간으로 표현한 동영상 프레임의 상대적 위치(0: 시작, 1 : 끝)
	//CAP_PROP_FRAME_WIDTH		//비디오 프레임의 가로 크기
	//CAP_PROP_FRAME_HEIGHT		//비디오 프레임의 세로 크기
	//CAP_PROP_FPS				//초당 프레임 수
	//CAP_PROP_FOURCC			//fourcc 코드(코덱을 표현하는 정수 값)
	//CAP_PROP_FRAME_COUNT		//비디오 파일의 전체 프레임 수
	//CAP_PROP_BRIGHTNESS		//(카메라에서 지원하는 경우) 밝기 조절
	//CAP_PROP_CONTRAST			//(카메라에서 지원하는 경우) 명암비 조절
	//CAP_PROP_SATURATION		//(카메라에서 지원하는 경우) 채도 조절
	//CAP_PROP_HUE				//(카메라에서 지원하는 경우) 색상 조절
	//CAP_PROP_GAIN				//(카메라에서 지원하는 경우) 감도 조절
	//CAP_PROP_EXPOSURE			//(카메라에서 지원하는 경우) 노출 조절
	//CAP_PROP_ZOOM				//(카메라에서 지원하는 경우) 줌 조절
	//CAP_PROP_FOCUS			//(카메라에서 지원하는 경우) 초점 조절



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
	// **(VideoWriter 객체 생성)
	//	- 파일을 쓰기 위한 스트림을 엽니다.
	//
	//	VideoWriter::VideoWriter(const String& filename, int fourcc, double fps,
	//		Size frameSize, bool isColor = true);
	//
	// bool VideoWriter::open(const String& filename, int fourcc, double fps,
	//	Size frameSize, bool isColor = true);
	//: 위와 같은 메서드로 되어있고, 생성자로 열거나, 혹은 open 메서드로 엽니다.
	//	file : 저장할 동영상 파일 이름
	//	fourcc : 동영상 압축 코덱을 표현하는 4 - 문자코드
	//	fps : 저장할 동영상의 초당 프레임 수
	//	frameSize : 동영상 프레임의 가로 및 세로 크기
	//	isColor : 이 값이 true이면 컬러 동영상으로 저장하고, false면, 그레이스케일입니다.이 플래그는 windows 에서만 동작합니다.
	//	반환값 : 성공시 true, 실패시 false

	//-fourcc : 동영상 파일로 저장시, 속성을 지정합니다. 4글자로 이루어져 있으며, 각각 파일 코덱, 압축방식, 색상 혹은 픽셀 포맷 등을 정의하는 정수값입니다.
	//이 정수 값은, static int VideoWriter::fourcc(char c1, char c2, char c3, char c4);


	//fourcc 코드 생성 방법	코덱 설명
	//	VideoWriter::fourcc('D', 'I', 'V', 'X')		-DivX MPEG - 4 코덱
	//	VideoWriter::fourcc('X', 'V', 'I', 'D')		-XVID MPEG - 4 코덱
	//	VideoWriter::fourcc('F', 'M', 'P', '4')		-FFMPEG MPEG4 코덱
	//	VideoWriter::fourcc('W', 'M', 'V', '2')		-Windows Media Video 8 코덱
	//	VideoWriter::fourcc('M', 'J', 'P', 'G')		-모션 JPEG 코덱
	//	VideoWriter::fourcc('Y', 'V', '1', '2')		-YUV 4:2 : 0 Planar(비압축)
	//	VideoWriter::fourcc('X', '2', '6', '4')		-H.264 / AVC 코덱
	//	VideoWriter::fourcc('A', 'V', 'C', '1')		-Advanced Video 코덱

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
	//mat_frame가 입력 이미지입니다. 
	captureLive->read(mat_frame);
	
	if (mat_frame.empty())
	{
		return FALSE;
	}
	
	//이곳에 OpenCV 함수들을 적용합니다.
	//여기에서는 그레이스케일 이미지로 변환합니다.
	//cvtColor(mat_frame, mat_frame, COLOR_BGR2GRAY);

	//화면에 보여주기 위한 처리입니다.
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
// 	//그레이스케일 인경우 팔레트가 필요
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
			AfxMessageBox(_T("프레임 영상이 EMPTY 상태입니다."));
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
