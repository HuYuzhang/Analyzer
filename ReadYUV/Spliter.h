#pragma once
#include "def.h"
#include "YUVReader.h"
using namespace cv;
using namespace std;
class Spliter
{
private:
  YUVReader GTReader, RecReader;
  ui frameNumber;
public:
  Spliter(string GTFile, string RecFile, ui h, ui, ui frameNum);
  ~Spliter();
  /*
  重载了doSplitYUV，因为一开始存预测模式的时候为了测试，所以每一条记录中并没有加上当前帧的编号
  完善之后每条记录开头加上了帧的编号，所以就不需要当前帧的编号了，直接对于所有帧进行操作
  */

  void doSplitYUV(string predDirectionFile, string dstDir);

  void doSplitYUV(ui idx, string predDirectionFile, string dstDir);

};

