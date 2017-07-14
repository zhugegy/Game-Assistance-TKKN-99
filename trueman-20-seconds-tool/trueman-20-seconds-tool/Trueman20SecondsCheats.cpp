#include "stdafx.h"
#include "Trueman20SecondsCheats.h"
#include "SingleInstanceMacro.h"

bool Trueman20SecondsCheats::m_bIsNowCheating = false;
HANDLE Trueman20SecondsCheats::m_hCheatingThread = NULL;
HANDLE Trueman20SecondsCheats::m_hGameProcess = INVALID_HANDLE_VALUE;
char Trueman20SecondsCheats::m_chMatrix[MATRIX_Y][MATRIX_X] = { 0 };
char Trueman20SecondsCheats::m_chMatrixEx[MATRIX_Y][MATRIX_X] = { 0 };
// CGYEasyStack Trueman20SecondsCheats::m_PathStack;
// CGYAStarNavi * Trueman20SecondsCheats::m_pGYAStarNavi = NULL;

int Trueman20SecondsCheats::m_nPlaneCurrentPosX = 0;
int Trueman20SecondsCheats::m_nPlaneCurrentPosY = 0;

int Trueman20SecondsCheats::m_nCurrentDestPosX = 0;
int Trueman20SecondsCheats::m_nCurrentDestPosY = 0;

//CRITICAL_SECTION Trueman20SecondsCheats::m_cs;
/*
   | 0 | 7 | 6 |
   | 1 |   | 5 |
   | 2 | 3 | 4 |
*/

int Trueman20SecondsCheats::m_nDestPosXList[8] =
{
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_A,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_A,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_A,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_B,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_X * AUTO_MOVE_DEST_THRESHOLD_B
};

int Trueman20SecondsCheats::m_nDestPosYList[8] = 
{
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_A,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_B,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_C,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_B,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_A,
  MATRIX_Y * AUTO_MOVE_DEST_THRESHOLD_A
};

HWND g_hWnd;

int g_currentDirectionV = 100;
int g_desiredDirectionV = 100;

int g_currentDirectionH = 100;
int g_desiredDirectionH = 100;

POINT Trueman20SecondsCheats::m_ptAmmoPos[100];
int Trueman20SecondsCheats::m_nCurrentAmmoNum = 0;
int Trueman20SecondsCheats::m_nAutoMoveDirection = 1;



Trueman20SecondsCheats::Trueman20SecondsCheats()
{
}


Trueman20SecondsCheats::~Trueman20SecondsCheats()
{
}

// DWORD WINAPI Trueman20SecondsCheats::CheatingControlUpThreadFunc(LPVOID pParam)
// {
//   //为了效率，不提供参数，直接按键
//   /*switch (switch_on)
//   {
//   default:
//    break;
//   }*/
//   while (true)
//   {
//     //WaitForSingleObject(g_hEventUp, INFINITE);
// 
//     if (g_hEventUp == TRUE)
//     {
//       ::PostMessage(g_hWnd, WM_KEYDOWN, VK_UP, (LPARAM)0);
//       //Sleep(100);
//       Sleep(10);
//     }
// 
// 
//   }
// }


DWORD WINAPI Trueman20SecondsCheats::CheatingThreadFunc(LPVOID pParam)
{
  int nCheatingType = (int)pParam;

  if (Trueman20SecondsCheats::m_hGameProcess == INVALID_HANDLE_VALUE)
  {
    Trueman20SecondsCheats::GetGameProcessHandle();
  }

  while (true)
  {
    switch (nCheatingType)
    {
    case Trueman20SecondsCheats::INVULNERABILITY:
      Trueman20SecondsCheats::Invulnerability();
      break;
    case Trueman20SecondsCheats::FLASH_MOVE:
      Trueman20SecondsCheats::FlashMove();
      break;
    case Trueman20SecondsCheats::SHIELD:
      Trueman20SecondsCheats::Shield();
      break;
    case Trueman20SecondsCheats::AUTO_MOVE:
//       CreateThread(NULL, 0, Trueman20SecondsCheats::CheatingControlUpThreadFunc, 0, 0, NULL);
//       ResetEvent(g_hEventUp);
//       ResetEvent(g_hEventLeft);
      Trueman20SecondsCheats::AutoMove();
      break;
    default:
      break;
    }

  }

  return 0;
}

int Trueman20SecondsCheats::GetGameProcessHandle()
{
  g_hWnd = ::FindWindow(NULL, _T("摿孭"));

  if (g_hWnd == NULL)
  {
    return -1;
  }

  DWORD dwPid = 0;
  DWORD dwTid = GetWindowThreadProcessId(g_hWnd, &dwPid);

  BOOL bRet = FALSE;

  if (dwPid != 0)
  {
    m_hGameProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

    if (m_hGameProcess == NULL)
    {
      return -1;
    }
  }
  else
  {
    return -1;
  }

  return 0;
}

//无敌
int Trueman20SecondsCheats::Invulnerability()
{
  BYTE btCode = 0xeb;
  UINT nWritedBytes = 0;
  bool bRet = false;

  while (Trueman20SecondsCheats::m_bIsNowCheating == true)
  {
    bRet = WriteProcessMemory(m_hGameProcess,
      (LPVOID)0x00403616,
      &btCode,
      sizeof(BYTE),
      (unsigned long *)&nWritedBytes);

    Sleep(100);
  }

  btCode = 0x74;
  bRet = WriteProcessMemory(m_hGameProcess,
    (LPVOID)0x00403616,
    &btCode,
    sizeof(BYTE),
    (unsigned long *)&nWritedBytes);

  return 0;
}

//闪现
int Trueman20SecondsCheats::FlashMove()
{
  char szBuffer[10];

  UINT nReadedBytes = 0;
  UINT nWritedBytes = 0;
  bool bRet = false;
  PosInfo *pTmp = NULL;
  int nPosX = 0;
  int nPosY = 0;

  while (true)
  {
    
    UpdateMatrix();

    bRet = ReadProcessMemory(m_hGameProcess,
      (LPCVOID)0x00406D6C,
      &szBuffer,
      8,
      (unsigned long *)&nReadedBytes);

    pTmp = (PosInfo *)szBuffer;
    nPosX = pTmp->PosX;
    nPosY = pTmp->PosY;
    AdjustPosition(nPosX, nPosY);

    if (IsDangerousForFlashMove(nPosX, nPosY))
    {
      while (true)
      {
        int nTmpPosX = rand() % MATRIX_X;
        int nTmpPosY = rand() % MATRIX_Y;

        if (nTmpPosX < 20 || nTmpPosX > MATRIX_X - 20 || nTmpPosY < 20 || nTmpPosY > MATRIX_Y - 20)
        {
          continue;
        }

        //UpdateMatrix();

        if (IsDangerousForFlashMove(nTmpPosX, nTmpPosY) == false)
        {
          bRet = WriteProcessMemory(m_hGameProcess,
            (LPVOID)0x00406D6C,
            &nTmpPosX,
            sizeof(int),
            (unsigned long *)&nWritedBytes);

          nTmpPosY = MATRIX_Y - nTmpPosY;

          bRet = WriteProcessMemory(m_hGameProcess,
            (LPVOID)0x00406D70,
            &nTmpPosY,
            sizeof(int),
            (unsigned long *)&nWritedBytes);

          break;
        }
      }
    }

    //Sleep(10);
  }

  return 0;
}

//自动寻路
int Trueman20SecondsCheats::AutoMove()
{
  char szBuffer[10];
  UINT nReadedBytes = 0;
  UINT nWritedBytes = 0;
  bool bRet = false;
  PosInfo *pTmp = NULL;
  int nPosX = 0;
  int nPosY = 0;
  int nInitAmmoNum = AMMO_NUMBER_LOCK;
  INPUT ip;   // Set up a generic keyboard event.
  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0;   // hardware scan code for key
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;

  //初始化炮弹数量
  bRet = WriteProcessMemory(m_hGameProcess,
    (LPVOID)0x0040469E,
    &nInitAmmoNum,
    sizeof(int),
    (unsigned long *)&nWritedBytes);

  while (true)
  {
    LockAmmoNum(AMMO_NUMBER_LOCK);

    //更新渲染后的地图
    //UpdateMatrixEx();
    UpdateMatrix();

    bRet = ReadProcessMemory(m_hGameProcess,
      (LPCVOID)0x00406D6C,
      &szBuffer,
      8,
      (unsigned long *)&nReadedBytes);

    pTmp = (PosInfo *)szBuffer;
    nPosX = pTmp->PosX;
    nPosY = pTmp->PosY;
    AdjustPosition(nPosX, nPosY);

    //更新这个变量，给AutoNaviDlg使用
    m_nPlaneCurrentPosX = nPosX;
    m_nPlaneCurrentPosY = nPosY;

    /*坐标系
       1
    -1 0 1
      -1
    */
  if (IsDangerous(nPosX, nPosY) == true)
  {
    GetEmergeDest(nPosX, nPosY, m_nCurrentDestPosX, m_nCurrentDestPosY);
  }
  else
  {
    AutoMoveFindDest(nPosX, nPosY, m_nCurrentDestPosX, m_nCurrentDestPosY);
  }

  if (nPosX > m_nCurrentDestPosX)
  {
    g_desiredDirectionH = -1;
  }
  else if (nPosX < m_nCurrentDestPosX)
  {
    g_desiredDirectionH = 1;
  }
  else
  {
    g_desiredDirectionH = 0;
  }

  if (nPosY > m_nCurrentDestPosY)
  {
    g_desiredDirectionV = 1;
  }
  else if (nPosY < m_nCurrentDestPosY)
  {
    g_desiredDirectionV = -1;
  }
  else
  {
    g_desiredDirectionV = 0;
  }

  if (g_currentDirectionH != g_desiredDirectionH)
  {
    switch (g_currentDirectionH)
    {
    case -1:
      ip.ki.wVk = 0x25;
      break;
    case 0:
      ip.ki.wVk = 0x48;
      break;
    case 1:
      ip.ki.wVk = 0x27;
      break;
    default:
      break;
    }

    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
    g_currentDirectionH = g_desiredDirectionH;
  }

  switch (g_currentDirectionH)
  {
  case -1:
    ip.ki.wVk = 0x25;
    break;
  case 0:
    ip.ki.wVk = 0x48;
    break;
  case 1:
    ip.ki.wVk = 0x27;
    break;
  default:
    break;
  }  
 
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));
  
  if (g_currentDirectionV != g_desiredDirectionV)
  {
    switch (g_currentDirectionV)
    {
    case -1:
      ip.ki.wVk = 0x28;
      break;
    case 0:
      ip.ki.wVk = 0x56;
      break;
    case 1:
      ip.ki.wVk = 0x26;
      break;
    default:
      break;
    }

    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
    g_currentDirectionV = g_desiredDirectionV;
  }

  switch (g_currentDirectionV)
  {
  case -1:
    ip.ki.wVk = 0x28;
    break;
  case 0:
    ip.ki.wVk = 0x56;
    break;
  case 1:
    ip.ki.wVk = 0x26;
    break;
  default:
    break;
  }

  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));

  Sleep(2);
 }

  return 0;
}


// char szBuffer2[200];
// int nPosXAmmo;
// int nPosYAmmo;
// 
// 
// bRet = ReadProcessMemory(m_hGameProcess,
// (LPCVOID)0x00406E10,
// &szBuffer2,
// 30,
// (unsigned long *)&nReadedBytes);
// 
// for (int i = 0; i < 1; i++)
// {
//   pTmp = (PosInfo *)(szBuffer2 + i * 15);
//   nPosXAmmo = ((pTmp->PosX) >> 6) - 4;
//   nPosYAmmo = ((pTmp->PosY) >> 6) - 4;
//   AdjustPosition(nPosXAmmo, nPosYAmmo);
// 
//   TRACE(_T("炮弹 %d X: %d Y: %d"), i, nPosXAmmo, nPosYAmmo);
// }
// 
// bRet = ReadProcessMemory(m_hGameProcess,
// (LPCVOID)0x00406D6C,
// &szBuffer,
// 8,
// (unsigned long *)&nReadedBytes);
// 
// pTmp = (PosInfo *)szBuffer;
// nPosX = pTmp->PosX;
// nPosY = pTmp->PosY;
// AdjustPosition(nPosX, nPosY);
// 
// 
// 
// TRACE(_T("X: %d Y: %d"), nPosX, nPosY);
// TRACE(_T("差值X: %d Y: %d"), nPosXAmmo - nPosX, nPosYAmmo - nPosY);

int Trueman20SecondsCheats::GetEmergeDest(int nPosX, int nPosY, int & nDestPosX, int & nDestPosY)
{
  int nPotentialPosX = 0;
  int nPotentialPosY = 0;


  nPotentialPosX = nPosX - EMERGENCY_NAVI_DISTANCE;
  nPotentialPosY = nPosY - EMERGENCY_NAVI_DISTANCE;
  if (nPotentialPosX >= AUTO_MOVE_BORDER_RESRTICTION && nPotentialPosY >= AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
    //TRACE(_T("紧急寻路：左上"));

    return 0;
  }

  nPotentialPosX = nPosX + EMERGENCY_NAVI_DISTANCE;
  nPotentialPosY = nPosY + EMERGENCY_NAVI_DISTANCE;
  if (nPotentialPosX < MATRIX_X - AUTO_MOVE_BORDER_RESRTICTION && nPotentialPosY < MATRIX_Y - AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
   // TRACE(_T("紧急寻路：右下"));

    return 0;
  }

  nPotentialPosX = nPosX - EMERGENCY_NAVI_DISTANCE;
  nPotentialPosY = nPosY + EMERGENCY_NAVI_DISTANCE;
  if (nPotentialPosX >= AUTO_MOVE_BORDER_RESRTICTION && nPotentialPosY < MATRIX_Y - AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
   // TRACE(_T("紧急寻路：左下"));

    return 0;
  }

  nPotentialPosX = nPosX + EMERGENCY_NAVI_DISTANCE;
  nPotentialPosY = nPosY - EMERGENCY_NAVI_DISTANCE;
  if (nPotentialPosX < MATRIX_X - AUTO_MOVE_BORDER_RESRTICTION && nPotentialPosY >= AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
 //   TRACE(_T("紧急寻路：右上"));

    return 0;
  }


  nPotentialPosX = nPosX;
  nPotentialPosY = nPosY - EMERGENCY_NAVI_DISTANCE * 2;
  if (nPotentialPosY >= AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
    TRACE(_T("紧急寻路：正上"));

    return 0;
  }

  nPotentialPosX = nPosX;
  nPotentialPosY = nPosY + EMERGENCY_NAVI_DISTANCE * 2;
  if (nPotentialPosY < MATRIX_Y - AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
    TRACE(_T("紧急寻路：正下"));

    return 0;
  }

  nPotentialPosX = nPosX - EMERGENCY_NAVI_DISTANCE * 2;
  nPotentialPosY = nPosY;
  if (nPotentialPosX >= AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
    TRACE(_T("紧急寻路：正左"));

    return 0;
  }

  nPotentialPosX = nPosX + EMERGENCY_NAVI_DISTANCE * 2;
  nPotentialPosY = nPosY;
  if (nPotentialPosX < MATRIX_X - AUTO_MOVE_BORDER_RESRTICTION && IsDangerous(nPotentialPosX, nPotentialPosY) == false)
  {
    nDestPosX = nPotentialPosX;
    nDestPosY = nPotentialPosY;
    TRACE(_T("紧急寻路：正右"));

    return 0;
  }

  nDestPosX = (rand() % (MATRIX_X - 30)) + 10;
  nDestPosY = (rand() % (MATRIX_Y - 30)) + 10;

  TRACE(_T("紧急寻路失败，随机目标"));

  return 0;
}

int Trueman20SecondsCheats::AutoMoveFindDest(int nPosX, int nPosY,
  int &nDestPosX, int &nDestPosY)
{
  int nPotentialPosX = 0;
  int nPotentialPosY = 0;

  int nAreaNum = 0;
  int nMinDistance = abs(nPosX - m_nDestPosXList[0]) + abs(nPosY - m_nDestPosYList[0]);
  
  for (int i = 1; i < 8; i++)
  {
    int nDistance = abs(nPosX - m_nDestPosXList[i]) + abs(nPosY - m_nDestPosYList[i]);
    
    if (nDistance < nMinDistance)
    {
      nMinDistance = nDistance;
      nAreaNum = i;
    }
  }

  int nDestAreaNum = AutoMoveFindDestArea(nAreaNum);

  if (nDestAreaNum != -1)
  {
    nDestPosX = m_nDestPosXList[nDestAreaNum];
    nDestPosY = m_nDestPosYList[nDestAreaNum];
  }
  else
  {
    TRACE(_T("没有合适的目标区域"));
    nDestPosX = (rand() % (MATRIX_X - 30)) + 30;
    nDestPosY = (rand() % (MATRIX_Y - 30)) + 30;
  }

  return 0;
}

int Trueman20SecondsCheats::AutoMoveFindDestArea(int nAreaNum)
{
  nAreaNum += m_nAutoMoveDirection;

  if (nAreaNum == 8)
  {
    nAreaNum = 0;
  }

  if (nAreaNum == -1)
  {
    nAreaNum = 7;
  }

  if (GetAreaAmmoNumForAutoMove(m_nDestPosXList[nAreaNum], m_nDestPosYList[nAreaNum]) < AUTO_MOVE_DEST_AREA_AMMO_NUM_THRESHOLD)
  {
    return nAreaNum;
  }
  else
  {
    m_nAutoMoveDirection *= -1;

    TRACE(_T("方向反转"));

    nAreaNum += m_nAutoMoveDirection * 2;

    if (nAreaNum == -1)
    {
      nAreaNum = 7;
    }

    if (nAreaNum == -2)
    {
      nAreaNum = 6;
    }

    if (nAreaNum == 8)
    {
      nAreaNum = 0;
    }

    if (nAreaNum == 9)
    {
      nAreaNum = 1;
    }

    return nAreaNum;
  }

  return -1;
}

//锁定炮弹数量
int Trueman20SecondsCheats::LockAmmoNum(int nAmmoNum)
{
  //BYTE btCode = 0xeb;
  UINT nWritedBytes = 0;
  bool bRet = false;


  bRet = WriteProcessMemory(m_hGameProcess,
    (LPVOID)0x00406DA8,
    &nAmmoNum,
    sizeof(int),
    (unsigned long *)&nWritedBytes);

  return 0;
}

//护盾
int Trueman20SecondsCheats::Shield()
{
  char szBuffer[(8 + 7) * 0x32 * 10];

  UINT nReadedBytes = 0;
  UINT nWritedBytes = 0;
  bool bRet = false;
  PosInfo *pTmp = NULL;
  int nPlanePosX = 0;
  int nPlanePosY = 0;

  int nAmmoNumber = 0;
  int nAmmoPosX = 0;
  int nAmmoPosY = 0;

  while (true)
  {
    //获取飞机坐标
    bRet = ReadProcessMemory(m_hGameProcess,
      (LPCVOID)0x00406D6C,
      &szBuffer,
      8,
      (unsigned long *)&nReadedBytes);

    pTmp = (PosInfo *)szBuffer;
    nPlanePosX = pTmp->PosX;
    nPlanePosY = pTmp->PosY;
    AdjustPosition(nPlanePosX, nPlanePosY);

    //获取炮弹坐标
    bRet = ReadProcessMemory(m_hGameProcess,
      (LPCVOID)0x00406DA8,
      &nAmmoNumber,
      sizeof(int),
      (unsigned long *)&nReadedBytes);

    bRet = ReadProcessMemory(m_hGameProcess,
      (LPCVOID)0x00406E10,
      &szBuffer,
      nAmmoNumber * 15,
      (unsigned long *)&nReadedBytes);

    for (int i = 0; i < nAmmoNumber; i++)
    {
      pTmp = (PosInfo *)(szBuffer + i * 15);
      nAmmoPosX = ((pTmp->PosX) >> 6) - 4;
      nAmmoPosY = ((pTmp->PosY) >> 6) - 4;
      AdjustPosition(nAmmoPosX, nAmmoPosY);

      if (abs(nAmmoPosX - nPlanePosX) + abs(nAmmoPosY - nPlanePosY) < SHIELD_RATIO_FOR_SHIELD)
      {
        do 
        {
          nAmmoPosX = rand() % MATRIX_X;
          nAmmoPosY = rand() % MATRIX_Y;
        } while 
          (abs(nAmmoPosX - nPlanePosX) + abs(nAmmoPosY - nPlanePosY) < SHIELD_RATIO_FOR_SHIELD);

        nAmmoPosX = nAmmoPosX + 4;
        nAmmoPosX = nAmmoPosX << 6;  //移位操作不可逆，不知道是否能够成功

        nAmmoPosY = MATRIX_Y - nAmmoPosY;
        nAmmoPosY = nAmmoPosY + 4;
        nAmmoPosY = nPlanePosY << 6;
        
        bRet = WriteProcessMemory(m_hGameProcess,
          (LPVOID)(0x00406E10 + ((8 + 7) * i)),
          &nAmmoPosX,
          sizeof(int),
          (unsigned long *)&nWritedBytes);

        bRet = WriteProcessMemory(m_hGameProcess,
          (LPVOID)(0x00406E10 + ((8 + 7) * i) + 4),
          &nAmmoPosY,
          sizeof(int),
          (unsigned long *)&nWritedBytes);
      }

    }

  }

  return 0;
}

bool Trueman20SecondsCheats::IsDangerous(int nPosX, int nPosY)
{
  for (int i = nPosY - 11; i < nPosY + 3; i++)
  {
    for (int j = nPosX + 0; j < nPosX + 15; j++)
    {
      if (
        /*i < 0 || i > MATRIX_Y - 1 || j < 0 || j > MATRIX_X - 1 ||*/ m_chMatrix[i][j] == 1 
        /*|| (i - nPosY)*(i - nPosY) + (j - nPosX)*(j - nPosX) > DANGER_THRESHOLD * DANGER_THRESHOLD*/)
      {
        return true;
      }

//      if (m_chMatrixEx[i][j] == 1)
//       if (m_chMatrixEx[i][j] == 1)
//       {
//         return true;
//       }
    }
  }

  return false;
}

bool Trueman20SecondsCheats::IsDangerousForFlashMove(int nPosX, int nPosY)
{
  for (int i = nPosY - DANGER_THRESHOLD_FOR_FLASH_MOVE; i < nPosY + DANGER_THRESHOLD_FOR_FLASH_MOVE; i++)
  {
    for (int j = nPosX - DANGER_THRESHOLD_FOR_FLASH_MOVE; j < nPosX + DANGER_THRESHOLD_FOR_FLASH_MOVE; j++)
    {
      if ( /* (i-nPosY)*(i-nPosY) + (j-nPosX)*(j-nPosX) > DANGER_THRESHOLD * DANGER_THRESHOLD*/
        i < 0 || i > MATRIX_Y - 1 || j < 0 || j > MATRIX_X - 1 || m_chMatrix[i][j] == 0)
      {
        continue;
      }

      return true;

    }
  }

  return false;
}

int Trueman20SecondsCheats::GetAreaAmmoNumForAutoMove(int nPosX, int nPosY)
{
  int nAmmoCount = 0;
  for (int i = nPosY - MATRIX_Y * CAL_AMMO_DENSITY_RATIO; 
           i < nPosY + MATRIX_Y * CAL_AMMO_DENSITY_RATIO; i++)
  {
    for (int j = nPosX - MATRIX_X * CAL_AMMO_DENSITY_RATIO; 
             j < nPosX + MATRIX_X * CAL_AMMO_DENSITY_RATIO; j++)
    {
      if (i < 0 || i > MATRIX_Y - 1 || j < 0 || j > MATRIX_X - 1)
      {
        continue;
      }

      if (m_chMatrix[i][j] == 1)
      {
        nAmmoCount++;
      }
    }
  }

  return nAmmoCount;
}

int Trueman20SecondsCheats::AdjustPosition(int &nPosX, int &nPosY)
{
  if (nPosX < 0)
  {
    nPosX = 0;
  }

  if (nPosY <= 0)
  {
    nPosY = 1;  //240 - 0 = 240 -> 越界
  }

  if (nPosX >= MATRIX_X)
  {
    nPosX = MATRIX_X - 1;
  }

  if (nPosY >= MATRIX_Y)
  {
    nPosY = MATRIX_Y - 1;
  }

  nPosY = MATRIX_Y - nPosY;

  return 0;
}


int Trueman20SecondsCheats::UpdateMatrix()
{
  char szBuffer[(8 + 7) * 0x32 * 10];

  UINT nReadedBytes = 0;
  bool bRet = false;
  PosInfo *pTmp = NULL;
  int nPosX = 0;
  int nPosY = 0;

  memset(m_chMatrix, 0, sizeof(m_chMatrix));

  bRet = ReadProcessMemory(m_hGameProcess,
    (LPCVOID)0x00406DA8,
    &m_nCurrentAmmoNum,
    sizeof(int),
    (unsigned long *)&nReadedBytes);

  bRet = ReadProcessMemory(m_hGameProcess,
    (LPCVOID)0x00406E10,
    &szBuffer,
    m_nCurrentAmmoNum * 15,
    (unsigned long *)&nReadedBytes);

  for (int i = 0; i < m_nCurrentAmmoNum; i++)
  {
    pTmp = (PosInfo *)(szBuffer + i * 15);
    nPosX = ((pTmp->PosX) >> 6) - 4;
    nPosY = ((pTmp->PosY) >> 6) - 4;
    AdjustPosition(nPosX, nPosY);
    
    m_ptAmmoPos[i].x = nPosX;
    m_ptAmmoPos[i].y = nPosY;

    m_chMatrix[nPosY][nPosX] = 1;

  }

  return 0;
}

int Trueman20SecondsCheats::UpdateMatrixEx()
{
  char szBuffer[(8 + 7) * 0x32 * 10];

  UINT nReadedBytes = 0;
  bool bRet = false;
  PosInfo *pTmp = NULL;
  int nPosX = 0;
  int nPosY = 0;

  bRet = ReadProcessMemory(m_hGameProcess,
    (LPCVOID)0x00406DA8,
    &m_nCurrentAmmoNum,
    sizeof(int),
    (unsigned long *)&nReadedBytes);

  bRet = ReadProcessMemory(m_hGameProcess,
    (LPCVOID)0x00406E10,
    &szBuffer,
    m_nCurrentAmmoNum * 15,
    (unsigned long *)&nReadedBytes);

  for (int i = 0; i < m_nCurrentAmmoNum; i++)
  {
    pTmp = (PosInfo *)(szBuffer + i * 15);
    nPosX = ((pTmp->PosX) >> 6) - 4;
    nPosY = ((pTmp->PosY) >> 6) - 4;
    AdjustPosition(nPosX, nPosY);

    m_ptAmmoPos[i].x = nPosX;
    m_ptAmmoPos[i].y = nPosY;
  }


  memset(m_chMatrixEx, 0, sizeof(m_chMatrix));

  for (int i = 0; i < m_nCurrentAmmoNum; i++)
  {
    int AmmoPosX = m_ptAmmoPos[i].x;
    int AmmoPosY = m_ptAmmoPos[i].y;

    for (int m = AmmoPosY - RENDER_THRESHOLD_FOR_AUTO_MOVE; m < AmmoPosY + RENDER_THRESHOLD_FOR_AUTO_MOVE; m++)
    {
      for (int n = AmmoPosX - RENDER_THRESHOLD_FOR_AUTO_MOVE; n < AmmoPosX + RENDER_THRESHOLD_FOR_AUTO_MOVE; n++)
      {
        if (m < 0 || m > MATRIX_Y - 1 || n < 0 || n > MATRIX_X - 1
          /*|| (m - AmmoPosY)*(m - AmmoPosY) + (n - AmmoPosX)*(n - AmmoPosX) > RENDER_THRESHOLD_FOR_AUTO_MOVE * RENDER_THRESHOLD_FOR_AUTO_MOVE*/)
        {
          continue;
        }

        m_chMatrixEx[m][n] = 1;
      }
    }
    
  }

 
  return 0;
}







