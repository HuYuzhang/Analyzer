#pragma once
#include"def.h"

//�ӵ���֡��ʼ��ȡ��Ҳ�����±��0��ʼ��
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
  cv::Mat readFrame(ui idx);
};

