
// ConvexPolygonDlg.h: 头文件
//

#pragma once


// CConvexPolygonDlg 对话框
class CConvexPolygonDlg : public CDialogEx
{
// 构造
public:
	CConvexPolygonDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVEXPOLYGON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

bool  ConvexPolygonCheck(int x, int y);
bool  SameSign(int x, int y);
double ConvexPolygonArea();