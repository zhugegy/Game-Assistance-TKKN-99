#pragma once

#include "GYEasyStack.h"
#include "GYAStarNavi.h"

class CGYAStarNavi;

class Trueman20SecondsCheats
{
public:
#define MATRIX_X 320
#define MATRIX_Y 240

#define RENDER_THRESHOLD_FOR_AUTO_MOVE 8  //8 //12
#define EMERGENCY_NAVI_DISTANCE 2 //2
#define AUTO_MOVE_DEST_AREA_AMMO_NUM_THRESHOLD 7  //4  总数除以3最佳
#define AUTO_MOVE_BORDER_RESRTICTION 4  //4  总数除以3最佳


#define AMMO_NUMBER_LOCK 27  //16

#define SHIELD_RATIO_FOR_SHIELD 40
#define DANGER_THRESHOLD_FOR_FLASH_MOVE 20


#define CAL_AMMO_DENSITY_RATIO 0.2  //0.2
#define AUTO_MOVE_DEST_THRESHOLD_A 0.24  //0.26
#define AUTO_MOVE_DEST_THRESHOLD_B 0.5  //0.5
#define AUTO_MOVE_DEST_THRESHOLD_C 0.76  //0.74

  struct PosInfo
  {
    int PosX;
    int PosY;
  };

  enum CheatingType
  {
    INVULNERABILITY,
    FLASH_MOVE,
    SHIELD,
    AUTO_MOVE,
    NOT_CHEATING
  };

  Trueman20SecondsCheats();
  virtual ~Trueman20SecondsCheats();

  static int Invulnerability();
  static int FlashMove();
  static int Shield();
  static int AutoMove();
  static int GetGameProcessHandle();
  static bool IsDangerous(int nPosX, int nPosY);
  static bool IsDangerousForFlashMove(int nPosX, int nPosY);

  static int GetAreaAmmoNumForAutoMove(int nPosX, int nPosY);
  static int UpdateMatrix();
  static int UpdateMatrixEx();
  static int AdjustPosition(int &nPosX, int &nPosY);

  static int AutoMoveFindDest(int nPosX, int nPosY, int &nDestPosX, int &nDestPosY);

  static DWORD WINAPI CheatingThreadFunc(LPVOID pParam);

//   static DWORD WINAPI CheatingControlUpThreadFunc(LPVOID pParam);
  static bool m_bIsNowCheating;

  //用于作弊的线程
  static HANDLE m_hCheatingThread;

  static HANDLE m_hGameProcess;

  static char m_chMatrix[MATRIX_Y][MATRIX_X];
  static char m_chMatrixEx[MATRIX_Y][MATRIX_X];
  static int m_nDestPosXList[8];
  static int m_nDestPosYList[8];

//   static CGYEasyStack m_PathStack;
//   static CGYAStarNavi * m_pGYAStarNavi;
  static int m_nPlaneCurrentPosX;
  static int m_nPlaneCurrentPosY;

  static int m_nCurrentDestPosX;
  static int m_nCurrentDestPosY;

  static POINT m_ptAmmoPos[100];
  static int m_nCurrentAmmoNum;

  static int m_nAutoMoveDirection;

  //CloseHandle(hProcess);
private:
  static int LockAmmoNum(int nAmmoNum);
  static int AutoMoveFindDestArea(int nAreaNum);
  static int GetEmergeDest(int nPosX, int nPosY, int & nEmergeDestX, int & nEmergeDestY);
};

