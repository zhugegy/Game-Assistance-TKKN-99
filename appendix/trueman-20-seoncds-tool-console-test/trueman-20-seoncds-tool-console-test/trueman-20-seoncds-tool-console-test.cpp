// trueman-20-seoncds-tool-console-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

#define MATRIX_X 320
#define MATRIX_Y 240
#define RENDER_THRESHOLD 12

struct AmmoInfo
{
  int PosX;
  int PosY;
};

//int SetStatus(int nMatrix[][304], int nNum);
int UpdateMatrix(int m_nMatrix[][MATRIX_X], HANDLE m_hGameProcess);
int RenderMatrixEx(int m_nMatrix[][MATRIX_X], int m_nMatrixEx[][MATRIX_X]);


int main()
{
  HWND hWnd = ::FindWindow(NULL, TEXT("“ÁŒP"));

  while (true)
  {
    SendMessage(hWnd, WM_KEYDOWN, VK_UP, 0);
    SendMessage(hWnd, WM_KEYDOWN, VK_UP, 0);
    SendMessage(hWnd, WM_KEYDOWN, VK_UP, 0);

    Sleep(1000);
  }

  getchar();

  if (hWnd == NULL)
  {
    return 0;
  }

  DWORD dwPid = 0;
  DWORD dwTid = GetWindowThreadProcessId(hWnd, &dwPid);

  BOOL bRet = FALSE;

  HANDLE hProcess = INVALID_HANDLE_VALUE;
  hProcess = OpenProcess(PROCESS_ALL_ACCESS,
    FALSE,
    dwPid);
 
  int nStatus[MATRIX_Y][MATRIX_X] = { 0 };
  int nStatusEx[MATRIX_Y][MATRIX_X] = { 0 };

  memset(nStatus, 0, sizeof(nStatus));
  UpdateMatrix(nStatus, hProcess);
  RenderMatrixEx(nStatus, nStatusEx);

  TCHAR szdebug[400] = { 0 };

  for (int i = 0; i < MATRIX_Y; i++)
  {
    for (int j = 0; j < MATRIX_X; j++)
    {
      if (nStatusEx[i][j] == 0)
      {
        szdebug[j] = TEXT(' ');
      }
      else
      {
        szdebug[j] = TEXT('1');
      }
    }

    szdebug[MATRIX_X] = TEXT('\r');
    szdebug[MATRIX_X + 1] = TEXT('\0');


    OutputDebugString((LPCWSTR)szdebug);
  }


 /* for (int i = 0; i < MATRIX_Y; i++)
  {
    for (int j = 0; j < MATRIX_X; j++)
    {
      printf("%d", nStatus[i][j]);
    }

    printf("\r\n");
  }*/

 /* char szBuffer[(8 + 7) * 0x32 * 10];

  int nAmmoNumber = 0;
  UINT nReadedBytes = 0;
  bRet = ReadProcessMemory(hProcess,
    (LPCVOID)0x00406DA8,
    &nAmmoNumber,
    sizeof(int),
    (unsigned long *)&nReadedBytes);

  bRet = ReadProcessMemory(hProcess,
    (LPCVOID)0x00406E10,
    &szBuffer,
    nAmmoNumber * 15,
    (unsigned long *)&nReadedBytes);

  AmmoInfo *pTmp = NULL;

  for (int i = 0; i < nAmmoNumber; i++)
  {
    pTmp = (AmmoInfo *)(szBuffer + i * 15);
    printf("%d: %d %d \t", i, ((pTmp->PosX) >> 6) - 4, ((pTmp->PosY) >> 6) - 4);
  }*/

  //getchar();
  return 0;
}

/*
int SetStatus(int nMatrix[][MATRIX_X], int nNum)
{
  for (int i = 0; i < 224; i++)
  {
    for (int j = 0; j < 304; j++)
    {
      nMatrix[i][j] = nNum;
    }
  }

  return 0;
}*/

int AdjustPosition(int &nPosX, int &nPosY)
{
  if (nPosX < 0)
  {
    nPosX = 0;
  }

  if (nPosY <= 0)
  {
    nPosY = 1;  //240 - 0 = 240 -> Ô½½ç
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


int UpdateMatrix(int m_nMatrix[][MATRIX_X], HANDLE m_hGameProcess)
{
  char szBuffer[(8 + 7) * 0x32 * 10];

  int nAmmoNumber = 0;
  UINT nReadedBytes = 0;
  bool bRet = false;
  AmmoInfo *pTmp = NULL;
  int nPosX = 0;
  int nPosY = 0;

  memset(m_nMatrix, 0, sizeof(m_nMatrix));

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
    pTmp = (AmmoInfo *)(szBuffer + i * 15);
    nPosX = ((pTmp->PosX) >> 6) - 4;
    nPosY = ((pTmp->PosY) >> 6) - 4;
    AdjustPosition(nPosX, nPosY);

    m_nMatrix[nPosY][nPosX] = 1;
  }

  return 0;
}


int RenderMatrixEx(int m_nMatrix[][MATRIX_X], int m_nMatrixEx[][MATRIX_X])
{
  memset(m_nMatrixEx, 0, sizeof(m_nMatrix));

  for (int i = 0; i < MATRIX_Y; i++)
  {
    for (int j = 0; j < MATRIX_X; j++)
    {
      if (m_nMatrix[i][j] == 1)
      {
        for (int m = i - RENDER_THRESHOLD; m < i + RENDER_THRESHOLD; m++)
        {
          for (int n = j - RENDER_THRESHOLD; n < j + RENDER_THRESHOLD; n++)
          {
            if (m < 0 || m > MATRIX_Y - 1 || n < 0 || n > MATRIX_X - 1)
            {
              continue;
            }

            m_nMatrixEx[m][n] = 1;

          }
        }
      }
    }
  }

  return 0;
}