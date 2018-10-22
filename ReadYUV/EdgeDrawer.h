#pragma once
#include "def.h"
class EdgeDrawer
{
private:
  uc color;
public:
  EdgeDrawer(uc Color);
  ~EdgeDrawer();
  void drawEdge(Mat& img, vector<CU>& edges, ui mxaa = 2);
};

