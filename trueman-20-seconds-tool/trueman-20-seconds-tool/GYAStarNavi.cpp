#include "stdafx.h"
#include "GYAStarNavi.h"
#include "SingleInstanceMacro.h"
#include "Trueman20SecondsCheats.h"

#include "GYEasyStack.h"
#include <math.h>

//默认构造
CGYAStarNavi::CGYAStarNavi()
  :m_nMazeWidth(constnMazeWidth), m_nMazeHeight(constnMazeHeight)
{
}


CGYAStarNavi::~CGYAStarNavi()
{
}


int CGYAStarNavi::load_maze()
{
/*
  CGameMap *pTmp = GET_SINGLE(CGameMap);
  pTmp->get_map((char *) m_chMaze);*/
  memcpy(m_chMaze, Trueman20SecondsCheats::m_chMatrixEx, sizeof(m_chMaze));
  return 0;
}


int CGYAStarNavi::get_path(int nStartCoordX, int nStartCoordY, int nEndCoordX, int nEndCoordY, CGYEasyStack & CoordStack)
{
  if (nStartCoordX == nEndCoordX && nStartCoordY == nEndCoordY)
  {
    return -1;
  }

  NaviNode OpenList[constnListSlotCount];
  NaviNode ClosedList[constnListSlotCount];

  NaviNode TmpOrigin;
  NaviNode TmpNeighbor;

  int nBreakEndlessLoopCounter = 0;
  NaviNode TmpSmallestH;
  TmpSmallestH.nHCost = /*(constnMazeWidth + constnMazeHeight) * 10*/10000;  //随便设个大数，用于目的地无法到达的情况，选最优路径

  int nFlagLeftUp = -1;
  int nFlagRightUp = -1;
  int nFlagLeftDown = -1;
  int nFlagRightDown = -1;

  int nTmpRecord = 0;
  int nTmpSmallestF = 0;

  list_init(OpenList, constnListSlotCount);
  list_init(ClosedList, constnListSlotCount);

  TmpOrigin.nID = nStartCoordX + nStartCoordY * m_nMazeWidth;

  TmpOrigin.nCoordX = nStartCoordX;
  TmpOrigin.nCoordY = nStartCoordY;
  TmpOrigin.nFather = -2;
  TmpOrigin.nGCost = 0;
  TmpOrigin.nHCost = 0;

  insert_to_list(OpenList, constnListSlotCount, TmpOrigin);

  while (true)
  {
    nFlagLeftUp = -1;
    nFlagRightUp = -1;
    nFlagLeftDown = -1;
    nFlagRightDown = -1;

    //正上
    if (TmpOrigin.nCoordY - 1 >= 0
      && m_chMaze[TmpOrigin.nCoordY - 1][TmpOrigin.nCoordX] == MAZE_PATH
      && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + (TmpOrigin.nCoordY - 1) * m_nMazeWidth) == -1)
    {
      nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + (TmpOrigin.nCoordY - 1) * m_nMazeWidth);
      if (nTmpRecord == -1)
      {
        //加入
        TmpNeighbor.nID = TmpOrigin.nCoordX + (TmpOrigin.nCoordY - 1) * m_nMazeWidth;

        TmpNeighbor.nCoordX = TmpOrigin.nCoordX;
        TmpNeighbor.nCoordY = TmpOrigin.nCoordY - 1;
        TmpNeighbor.nFather = TmpOrigin.nID;
        TmpNeighbor.nGCost = TmpOrigin.nGCost + 10;
        TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - 1 - nEndCoordY) * 10;

        insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
      }
      else
      {
        if (TmpOrigin.nGCost + 10 < OpenList[nTmpRecord].nGCost)
        {
          OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 10;
          OpenList[nTmpRecord].nFather = TmpOrigin.nID;
        }
      }

      //左上
      if (TmpOrigin.nCoordX - 1 >= 0
        && m_chMaze[TmpOrigin.nCoordY - 1][TmpOrigin.nCoordX - 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth) == -1)
      {
        nFlagLeftUp = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX - 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY - 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }

      //右上
      if (TmpOrigin.nCoordX + 1 < m_nMazeWidth
        && m_chMaze[TmpOrigin.nCoordY - 1][TmpOrigin.nCoordX + 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth) == -1)
      {
        nFlagRightUp = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX + 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY - 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX + 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }
    }

    //正下
    if (TmpOrigin.nCoordY + 1 < m_nMazeHeight
      && m_chMaze[TmpOrigin.nCoordY + 1][TmpOrigin.nCoordX] == MAZE_PATH
      && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + (TmpOrigin.nCoordY + 1) * m_nMazeWidth) == -1)
    {
      nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + (TmpOrigin.nCoordY + 1) * m_nMazeWidth);
      if (nTmpRecord == -1)
      {
        //加入
        TmpNeighbor.nID = TmpOrigin.nCoordX + (TmpOrigin.nCoordY + 1) * m_nMazeWidth;

        TmpNeighbor.nCoordX = TmpOrigin.nCoordX;
        TmpNeighbor.nCoordY = TmpOrigin.nCoordY + 1;
        TmpNeighbor.nFather = TmpOrigin.nID;
        TmpNeighbor.nGCost = TmpOrigin.nGCost + 10;
        TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY + 1 - nEndCoordY) * 10;

        insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
      }
      else
      {
        if (TmpOrigin.nGCost + 10 < OpenList[nTmpRecord].nGCost)
        {
          OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 10;
          OpenList[nTmpRecord].nFather = TmpOrigin.nID;
        }
      }

      //左下
      if (TmpOrigin.nCoordX - 1 >= 0
        && m_chMaze[TmpOrigin.nCoordY + 1][TmpOrigin.nCoordX - 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth) == -1)
      {
        nFlagLeftDown = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX - 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY + 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY + 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }

      //右下
      if (TmpOrigin.nCoordX + 1 < m_nMazeWidth
        && m_chMaze[TmpOrigin.nCoordY + 1][TmpOrigin.nCoordX + 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth) == -1)
      {
        nFlagRightDown = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX + 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY + 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX + 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY + 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }
    }

    //正左
    if (TmpOrigin.nCoordX - 1 >= 0
      && m_chMaze[TmpOrigin.nCoordY][TmpOrigin.nCoordX - 1] == MAZE_PATH
      && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX - 1 + TmpOrigin.nCoordY * m_nMazeWidth) == -1)
    {
      nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX - 1 + TmpOrigin.nCoordY * m_nMazeWidth);
      if (nTmpRecord == -1)
      {
        //加入
        TmpNeighbor.nID = TmpOrigin.nCoordX - 1 + TmpOrigin.nCoordY * m_nMazeWidth;

        TmpNeighbor.nCoordX = TmpOrigin.nCoordX - 1;
        TmpNeighbor.nCoordY = TmpOrigin.nCoordY;
        TmpNeighbor.nFather = TmpOrigin.nID;
        TmpNeighbor.nGCost = TmpOrigin.nGCost + 10;
        TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - nEndCoordY) * 10;

        insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
      }
      else
      {
        if (TmpOrigin.nGCost + 10 < OpenList[nTmpRecord].nGCost)
        {
          OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 10;
          OpenList[nTmpRecord].nFather = TmpOrigin.nID;
        }
      }

      //左上
      if (nFlagLeftUp == -1
        && TmpOrigin.nCoordY - 1 >= 0
        && m_chMaze[TmpOrigin.nCoordY - 1][TmpOrigin.nCoordX - 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth) == -1)
      {
        nFlagLeftUp = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX - 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY - 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }

      //左下
      if (nFlagLeftDown == -1
        && TmpOrigin.nCoordY + 1 < m_nMazeHeight
        && m_chMaze[TmpOrigin.nCoordY + 1][TmpOrigin.nCoordX - 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth) == -1)
      {
        nFlagLeftDown = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX - 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX - 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY + 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX - 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY + 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }
    }

    //正右
    if (TmpOrigin.nCoordX + 1 < m_nMazeWidth
      && m_chMaze[TmpOrigin.nCoordY][TmpOrigin.nCoordX + 1] == MAZE_PATH
      && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + 1 + TmpOrigin.nCoordY * m_nMazeWidth) == -1)
    {
      nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + 1 + TmpOrigin.nCoordY * m_nMazeWidth);
      if (nTmpRecord == -1)
      {
        //加入
        TmpNeighbor.nID = TmpOrigin.nCoordX + 1 + TmpOrigin.nCoordY * m_nMazeWidth;

        TmpNeighbor.nCoordX = TmpOrigin.nCoordX + 1;
        TmpNeighbor.nCoordY = TmpOrigin.nCoordY;
        TmpNeighbor.nFather = TmpOrigin.nID;
        TmpNeighbor.nGCost = TmpOrigin.nGCost + 10;
        TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX + 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - nEndCoordY) * 10;

        insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
      }
      else
      {
        if (TmpOrigin.nGCost + 10 < OpenList[nTmpRecord].nGCost)
        {
          OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 10;
          OpenList[nTmpRecord].nFather = TmpOrigin.nID;
        }
      }

      //右上
      if (nFlagRightUp == -1
        && TmpOrigin.nCoordY - 1 >= 0
        && m_chMaze[TmpOrigin.nCoordY - 1][TmpOrigin.nCoordX + 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth) == -1)
      {
        nFlagRightUp = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY - 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX + 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY - 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX + 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY - 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }

      //右下
      if (nFlagRightDown == -1
        && TmpOrigin.nCoordY + 1 < m_nMazeHeight
        && m_chMaze[TmpOrigin.nCoordY + 1][TmpOrigin.nCoordX + 1] == MAZE_PATH
        && find_the_slot_of_a_node(ClosedList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth) == -1)
      {
        nFlagRightDown = 1;
        nTmpRecord = find_the_slot_of_a_node(OpenList, constnListSlotCount, TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth);
        if (nTmpRecord == -1)
        {
          //加入
          TmpNeighbor.nID = TmpOrigin.nCoordX + 1 + (TmpOrigin.nCoordY + 1) * m_nMazeWidth;

          TmpNeighbor.nCoordX = TmpOrigin.nCoordX + 1;
          TmpNeighbor.nCoordY = TmpOrigin.nCoordY + 1;
          TmpNeighbor.nFather = TmpOrigin.nID;
          TmpNeighbor.nGCost = TmpOrigin.nGCost + 14;
          TmpNeighbor.nHCost = abs(TmpOrigin.nCoordX + 1 - nEndCoordX) * 10 + abs(TmpOrigin.nCoordY + 1 - nEndCoordY) * 10;

          insert_to_list(OpenList, constnListSlotCount, TmpNeighbor);
        }
        else
        {
          if (TmpOrigin.nGCost + 14 < OpenList[nTmpRecord].nGCost)
          {
            OpenList[nTmpRecord].nGCost = TmpOrigin.nGCost + 14;
            OpenList[nTmpRecord].nFather = TmpOrigin.nID;
          }
        }
      }
    }

    remove_from_list(OpenList, constnListSlotCount, TmpOrigin);
    insert_to_list(ClosedList, constnListSlotCount, TmpOrigin);

    nTmpSmallestF = find_the_smallest_f_in_list(OpenList, constnListSlotCount);

    TmpOrigin = OpenList[nTmpSmallestF];

    if (TmpOrigin.nHCost < TmpSmallestH.nHCost)
    {
      TmpSmallestH = TmpOrigin;
    }

    if (TmpOrigin.nCoordX == nEndCoordX && TmpOrigin.nCoordY == nEndCoordY)
    {
      break;
    }

    nBreakEndlessLoopCounter++;
    if (nBreakEndlessLoopCounter > constnMazeWidth * constnMazeHeight)
    {
      TmpOrigin = TmpSmallestH;
      break;
    }
  }

  int nCoordX = 0;
  int nCoordY = 0;
  NaviNode bktrace = TmpOrigin;
  NaviNode bktraceBackup = bktrace;


  int nSlot = 0;

  //int nPushTime = 0;    //debug

  while (bktrace.nFather != -2)
  {
    decipher_coord(nCoordX, nCoordY, bktrace.nID);
    //m_chMaze[nCoordY][nCoordX] = 6;

    CoordStack.push(nCoordX);
    CoordStack.push(nCoordY);

    //nPushTime++;    //debug

    bktraceBackup = bktrace;

    nSlot = find_the_slot_of_a_node(ClosedList, constnListSlotCount, bktrace.nFather);

    if (nSlot == -1)
    {
      nSlot = find_the_slot_of_a_node(OpenList, constnListSlotCount, bktrace.nFather);
      bktrace = OpenList[nSlot];
    }
    else
    {
      bktrace = ClosedList[nSlot];
    }

    //如果不是一条直线，需要圆润（加入过渡点）
//     if (if_two_nodes_in_a_line(bktraceBackup, bktrace) == -1)
//     {
//       get_buffer_point(bktraceBackup, bktrace, nCoordX, nCoordY);
//       //m_chMaze[nCoordY][nCoordX] = 6;
// 
//       CoordStack.push(nCoordX);
//       CoordStack.push(nCoordY);
//       //nPushTime++;    //debug
//     }

  }
  
  //int m = nPushTime;    //debug

  return 0;
}


int CGYAStarNavi::list_init(NaviNode TargetList[], int nListSlotCount)
{
  int i = 0;

  for (i = 0; i < nListSlotCount; i++)
  {
    TargetList[i].nID = -1;
    TargetList[i].nGCost = -1;
    TargetList[i].nHCost = -1;
  }

  return 0;
}


int CGYAStarNavi::insert_to_list(NaviNode TargetList[], int nListSlotCount, NaviNode & node)
{
  int nSlotNum = find_the_first_available_slot(TargetList, nListSlotCount);

  //assert(nSlotNum >= 0);

  TargetList[nSlotNum] = node;

  return 0;
}


int CGYAStarNavi::find_the_first_available_slot(NaviNode TargetList[], int nListSlotCount)
{
  for (int i = 0; i < nListSlotCount; i++)
  {
    if (TargetList[i].nID == -1)
    {
      return i;
    }
  }

  return -1;
}


int CGYAStarNavi::find_the_slot_of_a_node(NaviNode TargetList[], int nListSlotCount, int nTargetID)
{
  for (int i = 0; i < nListSlotCount; i++)
  {
    if (TargetList[i].nID == nTargetID)
    {
      return i;
    }
  }

  return -1;
}


int CGYAStarNavi::remove_from_list(NaviNode TargetList[], int nListSlotCount, NaviNode & node)
{
  int nSlotNum = find_the_slot_of_a_node(TargetList, nListSlotCount, node.nID);

  //assert(nSlotNum >= 0);

  TargetList[nSlotNum].nID = -1;

  return 0;
}


int CGYAStarNavi::find_the_smallest_f_in_list(NaviNode TargetList[], int nListSlotCount)
{
  int i = 0;

  int SmallestF = 6553500;
  int SmallestSerial = 0;

  for (i = 0; i < nListSlotCount; i++)
  {
    if (TargetList[i].nID != -1 &&
      TargetList[i].nGCost != -1 && TargetList[i].nHCost != -1
      && TargetList[i].nGCost + TargetList[i].nHCost < SmallestF)
    {
      SmallestF = TargetList[i].nGCost + TargetList[i].nHCost;
      SmallestSerial = i;
    }
  }

  return SmallestSerial;
}


int CGYAStarNavi::decipher_coord(int &CoordX, int &CoordY, int nID)
{
  CoordY = nID / m_nMazeWidth;
  CoordX = nID - CoordY * m_nMazeWidth;

  return 0;
}


int CGYAStarNavi::if_two_nodes_in_a_line(NaviNode &node1, NaviNode &node2)
{
  if (node1.nCoordX == node2.nCoordX || node1.nCoordY == node2.nCoordY)
  {
    return 1;
  }

  return -1;
}


int CGYAStarNavi::get_buffer_point(NaviNode &node1, NaviNode &node2, int &nCoordX, int &nCoordY)
{
  //node1在node2左上
  if (node1.nCoordX < node2.nCoordX && node1.nCoordY < node2.nCoordY)
  {
    if (m_chMaze[node1.nCoordY][node1.nCoordX + 1] == MAZE_PATH)
    {
      nCoordX = node1.nCoordX + 1;
      nCoordY = node1.nCoordY;
    }
    else
    {
      nCoordX = node1.nCoordX;
      nCoordY = node1.nCoordY + 1;
    }

    return 0;
  }

  //node1在node2右上
  if (node1.nCoordX > node2.nCoordX && node1.nCoordY < node2.nCoordY)
  {
    if (m_chMaze[node1.nCoordY][node1.nCoordX - 1] == MAZE_PATH)
    {
      nCoordX = node1.nCoordX - 1;
      nCoordY = node1.nCoordY;
    }
    else
    {
      nCoordX = node1.nCoordX;
      nCoordY = node1.nCoordY + 1;
    }

    return 0;
  }

  //node1在node2左下
  if (node1.nCoordX < node2.nCoordX && node1.nCoordY > node2.nCoordY)
  {
    if (m_chMaze[node1.nCoordY - 1][node1.nCoordX] == MAZE_PATH)
    {
      nCoordX = node1.nCoordX;
      nCoordY = node1.nCoordY - 1;
    }
    else
    {
      nCoordX = node1.nCoordX + 1;
      nCoordY = node1.nCoordY;
    }

    return 0;
  }

  //node1在node2右下
  if (node1.nCoordX > node2.nCoordX && node1.nCoordY > node2.nCoordY)
  {
    if (m_chMaze[node1.nCoordY - 1][node1.nCoordX] == MAZE_PATH)
    {
      nCoordX = node1.nCoordX;
      nCoordY = node1.nCoordY - 1;
    }
    else
    {
      nCoordX = node1.nCoordX - 1;
      nCoordY = node1.nCoordY;
    }

    return 0;
  }

  return 0;
}
