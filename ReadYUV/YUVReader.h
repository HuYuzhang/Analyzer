#pragma once
#include"def.h"

//从第零帧开始读取（也就是下标从0开始）
class YUVReader
{
private:
  ui height;
  ui width;
  string fileName;
  ifstream fin;
public:
  YUVReader(string s, ui h, ui w);
  ~YUVReader();
  cv::Mat readFrameYUV(ui idx);
  cv::Mat readFrameRGB(ui idx);
  string getFileName();
};

