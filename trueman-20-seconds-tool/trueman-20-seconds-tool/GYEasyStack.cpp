#include "stdafx.h"
#include "GYEasyStack.h"
#include <memory.h>


CGYEasyStack::CGYEasyStack()
{
  init_stack();
}


CGYEasyStack::~CGYEasyStack()
{
}


int CGYEasyStack::init_stack()
{
  m_nTop = -1;
  memset(m_nBuf, 0, sizeof(m_nBuf));
  return 0;
}


int CGYEasyStack::push(int nNum)
{
  if (m_nTop < C_GY_EASY_STACK_SIZE - 1)
  {
    m_nBuf[++m_nTop] = nNum;
  }

  return 0;
}


int CGYEasyStack::pop()
{
  if (m_nTop >= 0)
  {
    return m_nBuf[m_nTop--];
  }

  return 0;
}


bool CGYEasyStack::is_empty()
{
  return m_nTop < 0 ? true : false;
}


int CGYEasyStack::get_top()
{
  return m_nTop;
}
