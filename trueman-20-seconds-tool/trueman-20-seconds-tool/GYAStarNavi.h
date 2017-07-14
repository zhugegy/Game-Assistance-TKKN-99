#pragma once
#include "stdafx.h"
#include "SingleInstanceMacro.h"
#include "Trueman20SecondsCheats.h"
#include "GYEasyStack.h"

//A��Ѱ·�㷨�����ڻ�ȡ��ͼ��Ϣ��������Ϣ�������·�����顣�����ࡣ

//�Թ���С�Ǳ�����constֵ���˴�Ӧ���У�ֱ�Ӵ�CGameMap���const�������롣
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
  //��ͼ����Ѱ·�㷨�����Ϊ�Թ���
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

