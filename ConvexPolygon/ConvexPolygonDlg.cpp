
// ConvexPolygonDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ConvexPolygon.h"
#include "ConvexPolygonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int kMaxPointNum = 6;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CConvexPolygonDlg 对话框



CConvexPolygonDlg::CConvexPolygonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONVEXPOLYGON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvexPolygonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvexPolygonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_WM_LBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CConvexPolygonDlg 消息处理程序

BOOL CConvexPolygonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConvexPolygonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConvexPolygonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConvexPolygonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int nPointCnt = 0;
POINT PolygonPoint[kMaxPointNum + 1];

void CConvexPolygonDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CDialogEx::OnLButtonDown(nFlags, point);

  if (!ConvexPolygonCheck(point.x, point.y))
  {
    MessageBox(_T("这不是个凸多边形哦(* ￣︿￣)，请重新选择"), _T("叮"), MB_OK | MB_ICONERROR);
    return;
  }

  //CDC init
  CDC *pDC = GetDC();
  CPen pen(PS_SOLID, 2, RGB(51, 153, 254)); //a magic color
  pDC->SelectObject(&pen);

  nPointCnt++;
  PolygonPoint[nPointCnt].x = point.x;  PolygonPoint[nPointCnt].y = point.y;

  if (1 == nPointCnt)
  {
    pDC->SetPixel(point.x, point.y, RGB(51, 153, 254));
    pDC->MoveTo(point.x, point.y);
  }
  else
  {
    pDC->MoveTo(PolygonPoint[nPointCnt - 1].x, PolygonPoint[nPointCnt - 1].y);
    pDC->LineTo(point.x, point.y);
  }

  pen.DeleteObject();
  ReleaseDC(pDC);
}


void CConvexPolygonDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CDialogEx::OnRButtonDown(nFlags, point);

  if (nPointCnt < 3)
  {
    MessageBox(_T("还不可以闭合哦(* ￣︿￣)"), _T("叮"), MB_OK | MB_ICONERROR);
    return;
  }

  //CDC init
  CDC *pDC = GetDC();
  CPen pen(PS_SOLID, 2, RGB(51, 153, 254)); //a magic color
  pDC->SelectObject(&pen);

  pDC->MoveTo(PolygonPoint[nPointCnt].x, PolygonPoint[nPointCnt].y);
  pDC->LineTo(PolygonPoint[1].x, PolygonPoint[1].y);

  pen.DeleteObject();
  ReleaseDC(pDC);

  double fArea = ConvexPolygonArea();
  CString csArea;
  csArea.Format(_T("%.2lf"), fArea);
  MessageBox(_T("(～￣▽￣)～凸多边形面积： " + csArea), _T("叮"), MB_OK);
}

int nCheckSign = 0;

bool  ConvexPolygonCheck(int x, int y)
{
  POINT Point1, Point2, Point3;
  int nVectorCrossRes;

  if (nPointCnt < 2)
  {
    return true;
  }
  else if (2 == nPointCnt)
  {
    //check 3 point: this point(Point3), last point(Point2) and the last point of last(Point1)
    Point1 = PolygonPoint[nPointCnt - 1];
    Point2 = PolygonPoint[nPointCnt];
    Point3 = { x, y };
    nVectorCrossRes = (Point2.x - Point1.x)*(Point3.y - Point2.y) - (Point3.x - Point2.x)*(Point2.y - Point1.y);
    if (0 == nVectorCrossRes)
    {
      return false;
    }
    else if (nVectorCrossRes > 0)
    {
      nCheckSign = 1;
    }
    else
    {
      nCheckSign = -1;
    }
    return true;
  }

  //check 3 point: this point(Point3), last point(Point2) and the last point of last(Point1)
  Point1 = PolygonPoint[nPointCnt - 1];
  Point2 = PolygonPoint[nPointCnt];
  Point3 = { x, y };
  nVectorCrossRes = (Point2.x - Point1.x)*(Point3.y - Point2.y) - (Point3.x - Point2.x)*(Point2.y - Point1.y);
  if (!SameSign(nVectorCrossRes, nCheckSign))
  {
    return false;
  }
  
  //check 3 point: first point(Point3), this point(Point2) and last point(Point1)
  Point1 = PolygonPoint[nPointCnt];
  Point2 = { x, y };  
  Point3 = PolygonPoint[1];
  nVectorCrossRes = (Point2.x - Point1.x)*(Point3.y - Point2.y) - (Point3.x - Point2.x)*(Point2.y - Point1.y);
  if (!SameSign(nVectorCrossRes, nCheckSign))
  {
    return false;
  }

  //check 3 point: second point(Point3), first point(Point2) and this point(Point1)
  Point1 = { x, y };;
  Point2 = PolygonPoint[1];
  Point3 = PolygonPoint[2];
  nVectorCrossRes = (Point2.x - Point1.x)*(Point3.y - Point2.y) - (Point3.x - Point2.x)*(Point2.y - Point1.y);
  if (!SameSign(nVectorCrossRes, nCheckSign))
  {
    return false;
  }

  return true;
}

double ConvexPolygonArea()
{
  double fArea = 0.0;

  for (int i = 1; i <= nPointCnt; i++)
  {
    int j = i + 1;
    if (j > nPointCnt)
    {
      j %= nPointCnt;
    }
    fArea += PolygonPoint[i].x * PolygonPoint[j].y;
    fArea -= PolygonPoint[i].y * PolygonPoint[j].x;
  }
  fArea *= 0.5;
  return fabs(fArea);
}

bool  SameSign(int x, int y)
{
  if (x*y <= 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}