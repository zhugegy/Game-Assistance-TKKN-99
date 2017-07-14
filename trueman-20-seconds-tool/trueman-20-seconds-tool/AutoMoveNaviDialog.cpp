// AutoMoveNaviDialog.cpp : implementation file
//

#include "stdafx.h"
#include "trueman-20-seconds-tool.h"
#include "AutoMoveNaviDialog.h"
#include "afxdialogex.h"

#include "Trueman20SecondsCheats.h"

// CAutoMoveNaviDialog dialog

IMPLEMENT_DYNAMIC(CAutoMoveNaviDialog, CDialog)

CAutoMoveNaviDialog::CAutoMoveNaviDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AUTOMOVENAVIDIALOG, pParent)
{

}

CAutoMoveNaviDialog::~CAutoMoveNaviDialog()
{
}

void CAutoMoveNaviDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoMoveNaviDialog, CDialog)
  ON_WM_PAINT()
END_MESSAGE_MAP()


// CAutoMoveNaviDialog message handlers



BOOL CAutoMoveNaviDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here




  CPaintDC dc(this);
  HWND hWnd = this->GetSafeHwnd();
  this->GetClientRect(&m_RC);

  m_pDCMem = new CDC;
  m_pDCMem->CreateCompatibleDC(&dc);

  CBitmap *pBitmap = new CBitmap;
  pBitmap->CreateCompatibleBitmap(&dc, m_RC.Width(), m_RC.Height());

  m_pDCMem->SelectObject(*pBitmap);

  CreateThread(NULL, 0, CAutoMoveNaviDialog::DisplayingThreadFunc, (LPVOID)this, 0, NULL);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI CAutoMoveNaviDialog::DisplayingThreadFunc(LPVOID pParam)
{
  CAutoMoveNaviDialog *pThis = (CAutoMoveNaviDialog *)pParam;

 /* pDC->BitBlt(0, 0, rc.Width(), rc.Height(), pMemDC, 0, 0, SRCCOPY);*/

  while (true)
  {
    pThis->InvalidateRect(NULL, FALSE);
    //Sleep(1000);
  }


  return 0;
}

void CAutoMoveNaviDialog::OnPaint()
{
  CPaintDC dc(this); // device context for painting
                     // TODO: Add your message handler code here
                     // Do not call CDialog::OnPaint() for painting messages
  CBrush brushAmmo;
  CBrush brushBackground;
  CBrush brushPlane;
  CBrush brushDest;

  brushAmmo.CreateSolidBrush(RGB(255, 0, 0));
  brushBackground.CreateSolidBrush(RGB(0, 0, 0));
  brushPlane.CreateSolidBrush(RGB(0, 255, 0));
  brushDest.CreateSolidBrush(RGB(0, 255, 255));

  //Çå¿Õ»­²¼
  m_pDCMem->FillSolidRect(&m_RC, dc.GetBkColor());
  POINT ptTmp;
  ptTmp.x = 0 + DRAW_OFFSET;
  ptTmp.y = 0 + DRAW_OFFSET;

  POINT ptTmpEnd;
  ptTmpEnd.x = MATRIX_X + DRAW_OFFSET;
  ptTmpEnd.y = MATRIX_Y + DRAW_OFFSET;

  m_pDCMem->SelectObject(&brushBackground);
  m_pDCMem->Rectangle(CRect(ptTmp, ptTmpEnd));

  m_pDCMem->SelectObject(&brushAmmo);

  for (int i = 0; i < Trueman20SecondsCheats::m_nCurrentAmmoNum; i++)
  {
    ptTmp.x = Trueman20SecondsCheats::m_ptAmmoPos[i].x - RENDER_THRESHOLD_FOR_AUTO_MOVE + DRAW_OFFSET;
    ptTmp.y = Trueman20SecondsCheats::m_ptAmmoPos[i].y - RENDER_THRESHOLD_FOR_AUTO_MOVE + DRAW_OFFSET;
 
    ptTmpEnd.x = Trueman20SecondsCheats::m_ptAmmoPos[i].x + RENDER_THRESHOLD_FOR_AUTO_MOVE + DRAW_OFFSET;
    ptTmpEnd.y = Trueman20SecondsCheats::m_ptAmmoPos[i].y + RENDER_THRESHOLD_FOR_AUTO_MOVE + DRAW_OFFSET;


    m_pDCMem->Ellipse(CRect(ptTmp, ptTmpEnd));
  }


  m_pDCMem->SelectObject(&brushPlane);
  ptTmp.x = Trueman20SecondsCheats::m_nPlaneCurrentPosX - 4 + DRAW_OFFSET;
  ptTmp.y = Trueman20SecondsCheats::m_nPlaneCurrentPosY - 4 + DRAW_OFFSET;

  ptTmpEnd.x = Trueman20SecondsCheats::m_nPlaneCurrentPosX + 4 + DRAW_OFFSET;
  ptTmpEnd.y = Trueman20SecondsCheats::m_nPlaneCurrentPosY + 4 + DRAW_OFFSET;

  m_pDCMem->Rectangle(CRect(ptTmp, ptTmpEnd));

  m_pDCMem->SelectObject(&brushDest);
  ptTmp.x = Trueman20SecondsCheats::m_nCurrentDestPosX - 6 + DRAW_OFFSET;
  ptTmp.y = Trueman20SecondsCheats::m_nCurrentDestPosY - 6 + DRAW_OFFSET;

  ptTmpEnd.x = Trueman20SecondsCheats::m_nCurrentDestPosX + 6 + DRAW_OFFSET;
  ptTmpEnd.y = Trueman20SecondsCheats::m_nCurrentDestPosY + 6 + DRAW_OFFSET;

  m_pDCMem->Rectangle(CRect(ptTmp, ptTmpEnd));

  dc.BitBlt(0, 0, m_RC.Width(), m_RC.Height(), m_pDCMem, 0, 0, SRCCOPY);

}
