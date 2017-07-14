#pragma once


// CAutoMoveNaviDialog dialog

class CAutoMoveNaviDialog : public CDialog
{
	DECLARE_DYNAMIC(CAutoMoveNaviDialog)

#define DRAW_OFFSET 50  //为了美观

public:
	CAutoMoveNaviDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoMoveNaviDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOMOVENAVIDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  static DWORD WINAPI DisplayingThreadFunc(LPVOID pParam);
  afx_msg void OnPaint();

  CDC *m_pDCMem;
  CRect m_RC;


};
