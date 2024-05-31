
// CELLGAMEDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CELLGAME.h"
#include "CELLGAMEDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCELLGAMEDlg 对话框



CCELLGAMEDlg::CCELLGAMEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CELLGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCELLGAMEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCELLGAMEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCELLGAMEDlg 消息处理程序

BOOL CCELLGAMEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, 0);
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

	theMap = new GameMap();
	theRule = new GameRule(theMap);
	CRect   rect;
	GetClientRect(&rect);
	m_height = rect.Height();
	m_wide = rect.Width();

	cellH = m_height / (HEIGHT - 2);
	cellW = m_wide / (WIDE - 2);

	SetTimer(1, TIME, nullptr);

	SetWindowPos(NULL, 0, 0, cellW * (WIDE - 1), cellH * (HEIGHT - 1), SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCELLGAMEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCELLGAMEDlg::OnPaint()
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
		CPaintDC dc(this); // 用于绘制的设备上下文

		// 获取客户区矩形
		CRect rect;
		GetClientRect(&rect);

		// 创建内存DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		// 创建兼容的位图，并选择到内存DC中
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		// 绘制背景
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP_BLACKBACKGROUND);

		BITMAP bmpInfo;
		bmpBackground.GetBitmap(&bmpInfo);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		memDC.StretchBlt(0, 0, m_wide, m_height, &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		dcMem.SelectObject(pbmpOld);

		// 绘制白色矩形
		/*CBrush whiteBrush(RGB(255, 255, 255));
		CRect m_whiteRect;
		for (int i = 1; i < HEIGHT - 1; i++) {
			for (int j = 1; j < WIDE - 1; j++) {
				m_whiteRect.SetRect(cellW * (j - 1), cellH * (i - 1), cellW * j, cellH * i);
				if (theMap->isAlive(i, j)) {
					memDC.FillRect(&m_whiteRect, &whiteBrush);
				}
			}
		}*/


		// 绘制网格
		CPen pen(PS_SOLID, 1, RGB(255, 0, 255));
		CPen* pOldPen = memDC.SelectObject(&pen);
		for (int i = 1; i < HEIGHT - 1; ++i)
		{
			memDC.MoveTo(0, i * cellH);
			memDC.LineTo(m_wide, i * cellH);
		}
		for (int i = 1; i < WIDE - 1; ++i)
		{
			memDC.MoveTo(i * cellW, 0);
			memDC.LineTo(i * cellW, m_height);
		}
		memDC.SelectObject(pOldPen);

		// 将内存DC的内容复制到窗口的设备上下文中
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		// 清理
		memDC.SelectObject(pOldBitmap);

		DrawRect();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCELLGAMEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCELLGAMEDlg::updateMap()
{

	theRule->updateMap();
	theRule->submitMap(theMap);
	DrawRect();


	// TODO: 在此处添加实现代码.
}




void CCELLGAMEDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1&&flag)
	{
		// 定时器过期，调用 updateMap() 函数
		updateMap();

	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCELLGAMEDlg::DrawRect()
{
	CDC* pDC = GetDC();
	CRect m_Rect;
	CBrush whiteBrush(RGB(255, 255, 255)); // 白色画刷
	CBrush blackBrush(RGB(0, 0, 0));
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDE - 1; j++) {
			m_Rect.SetRect(cellW * (j - 1) + 1, cellH * (i - 1) + 1, cellW * j - 1, cellH * i - 1);
			// 绘制矩形
			if (theMap->isAlive(i, j)) pDC->SelectObject(&whiteBrush);
			else pDC->SelectObject(&blackBrush);
			pDC->Rectangle(&m_Rect);
		}
	}
	// 释放设备上下文
	ReleaseDC(pDC);
}


void CCELLGAMEDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int row = point.y / cellH + 1;
	int column = point.x / cellW + 1;
	if(row>HEIGHT-2||column>WIDE-2)return CDialogEx::OnLButtonUp(nFlags, point);
	CDC* pDC = GetDC();
	CRect m_Rect;
	CBrush whiteBrush(RGB(255, 255, 255)); // 白色画刷
	CBrush blackBrush(RGB(0, 0, 0));
	m_Rect.SetRect(cellW * (column - 1) + 1, cellH * (row - 1) + 1, cellW * column - 1, cellH * row - 1);
	if (theRule->changeCellAlive(row, column)) pDC->SelectObject(&whiteBrush);
	else pDC->SelectObject(&blackBrush);
	pDC->Rectangle(&m_Rect);
	ReleaseDC(pDC);
}


void CCELLGAMEDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	flag = !flag;

	CDialogEx::OnRButtonDblClk(nFlags, point);
}


void CCELLGAMEDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CDialogEx::OnLButtonDown(nFlags, point);
}
