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
  ������doSplitYUV����Ϊһ��ʼ��Ԥ��ģʽ��ʱ��Ϊ�˲��ԣ�����ÿһ����¼�в�û�м��ϵ�ǰ֡�ı��
  ����֮��ÿ����¼��ͷ������֡�ı�ţ����ԾͲ���Ҫ��ǰ֡�ı���ˣ�ֱ�Ӷ�������֡���в���
  */

  void doSplitYUV(string predDirectionFile, string dstDir);

  void doSplitYUV(ui idx, string predDirectionFile, string dstDir);

};

