
// CELLGAMEDlg.h: 头文件
//

#pragma once
#include"GameMap.h"
#include"GameRule.h"

#define TIME 70

// CCELLGAMEDlg 对话框
class CCELLGAMEDlg : public CDialogEx
{
// 构造
public:
	CCELLGAMEDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CELLGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	
	GameMap *theMap;
	GameRule *theRule;
	HICON m_hIcon;
	int m_height;
	int m_wide;

	int cellH;
	int cellW;

	bool flag = true;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void DrawBackground(CDC* pDC, const CRect& rect);
	void DrawWhiteRect(CDC* pDC);
public:
//	int undateMap();
	void updateMap();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawRect();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
