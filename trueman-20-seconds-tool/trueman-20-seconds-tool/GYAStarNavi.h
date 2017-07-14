#pragma once
#include "stdafx.h"
#include "SingleInstanceMacro.h"
#include "Trueman20SecondsCheats.h"
#include "GYEasyStack.h"

//A星寻路算法：用于获取地图信息，坐标信息，并输出路径数组。单例类。

//迷宫大小是必须是const值，此次应用中，直接从CGameMap类的const常量载入。
const int constnMazeWidth = 320;/*Trueman20SecondsCheats::MATRIX_X;*/
const int constnMazeHeight = 240;

const int constnListSlotCount = constnMazeWidth * constnMazeHeight;

struct NaviNode
{
  int nID;

  int nCoordX;
  int nCoordY;
  int nFather;
  int nGCost;
  int nHCost;
};

class CGYAStarNavi
{
public:
  enum eMazeIdentifer
  {
    MAZE_PATH = 0,
    MAZE_BRICK = 1
  };

  SINGLE_INSTANCE(CGYAStarNavi)

  int load_maze();
  int get_path(int nStartCoordX, int nStartCoordY, int nEndCoordX, int nEndCoordY, CGYEasyStack & CoordStack);
private:
  CGYAStarNavi();
  virtual ~CGYAStarNavi();

private:
  //地图（在寻路算法类里，称为迷宫）
  char m_chMaze[constnMazeHeight][constnMazeWidth];

  const int m_nMazeWidth;
  const int m_nMazeHeight;

private:
  int list_init(NaviNode TargetList[], int nListSlotCount);
  int insert_to_list(NaviNode TargetList[], int nListSlotCount, NaviNode & node);
  int find_the_first_available_slot(NaviNode TargetList[], int nListSlotCount);
  int find_the_slot_of_a_node(NaviNode TargetList[], int nListSlotCount, int nTargetID);
  int remove_from_list(NaviNode TargetList[], int nListSlotCount, NaviNode & node);
  int find_the_smallest_f_in_list(NaviNode TargetList[], int nListSlotCount);
  int decipher_coord(int &CoordX, int &CoordY, int nID);
  int if_two_nodes_in_a_line(NaviNode &node1, NaviNode &node2);
  int get_buffer_point(NaviNode &node1, NaviNode &node2, int &nCoordX, int &nCoordY);
};

