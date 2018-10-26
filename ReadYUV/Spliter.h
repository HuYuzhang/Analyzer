#pragma once
#include "def.h"
#include "YUVReader.h"
using namespace cv;
using namespace std;
class Spliter
{
private:
  YUVReader GTReader, RecReader;
public:
  Spliter(string GTFile, string RecFile, ui h, ui w);
  ~Spliter();
  void doSplitYUV(ui idx, string predDirectionFile, string dstDir);
};

