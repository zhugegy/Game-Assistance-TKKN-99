#include "stdafx.h"
#include "DoNotUse.h"
#include "SingleInstanceMacro.h"

#include "GYAStarNavi.h"


CDoNotUse::CDoNotUse()
{
  CREATE_SINGLE(CGYAStarNavi)
}


CDoNotUse::~CDoNotUse()
{
  RELEASE_SINGLE(CGYAStarNavi)
}
