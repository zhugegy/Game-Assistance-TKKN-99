
// trueman-20-seconds-toolDlg.h : header file
//

#pragma once
#include "AutoMoveNaviDialog.h"

// Ctrueman20secondstoolDlg dialog
class Ctrueman20secondstoolDlg : public CDialogEx
{
// Construction
public:
	Ctrueman20secondstoolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRUEMAN20SECONDSTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButton1();
  afx_msg void OnBnClickedButton2();
  afx_msg void OnBnClickedButton3();
  afx_msg void OnBnClickedButton4();
  afx_msg void OnBnClickedButton5();
  afx_msg void OnBnClickedOk();

private:
  CAutoMoveNaviDialog *m_pAutoMoveNaviDlg;


};
