#include "Spliter.h"


Spliter::Spliter(string GTFile, string RecFile, ui h, ui w) : GTReader(GTFile, h, w), RecReader(RecFile, h, w)
{
}


Spliter::~Spliter()
{
}

/*
param:
idx����Ҫ���ڵڼ�֡����split����0��ʼ������
predDirectionFile���洢��һ֡���е�CU��Ԥ��ģʽ���ı��ļ�
dstDir���洢��������·��λ�ã���ʱ�����ֶ�����һ�£�������һ֡�ȶ�Ӧ��һ��Ŀ¼��Ŀ¼�����Ծ���idx��ʾ��
*/
void Spliter::doSplitYUV(ui idx, string predDirectionFile, string dstDir)
{
  //�����ֻ��YUV���е�Y������
  //emmmҪ��Ҫ�������Ͻ��Ǹ��أ��������Ͻ��Ǹ�ȷʵҲû��ʲô���ü�ֵ����ô���Һ��Ե���
  //���ˣ����ڵĴ�����ֱ�ӷ�������ߺ���������һ��һ�У���Ҫԭ�������޷���ȡ�ο�����
  ifstream fin = ifstream(predDirectionFile);
  if (!fin)
  {
    cout << "Fail to open the predDirectionFile: " << predDirectionFile << endl;
    exit(0);
  }
  Mat GTFrame = GTReader.readFrameYUV(idx);
  Mat RecFrame = RecReader.readFrameYUV(idx);
  ui pelX, pelY, predMode;
  Mat tmp(64, 64, CV_8UC1);
  string dstName;
  //��������ֻ������ͨ���ɡ����ó�64��ԭ����������input��label�ɴ೤��һ��ɡ�
  //��Ȼ��ͬһ��ͼ�У��������½ǵĿ��Ǻ������������Բ�ͬ��ͼ���еġ�
  while (fin >> pelY >> pelX >> predMode)
  {
    if (pelX != 0 && pelY != 0)
    {
      pelX -= 32;
      pelY -= 32;
      for (ui i = 0; i < 64; ++i)
      {
        for (ui j = 0; j < 64; ++j)
        {
          tmp.at<uc>(i, j) = GTFrame.at<Vec3b>(i + pelX, j + pelY)[0];
        }
      }
      pelX += 32;
      pelY += 32;
      for (ui i = 0; i < 32; ++i)
      {
        for (ui j = 0; j < 32; ++j)
        {
          tmp.at<uc>(32 + i, 32 + j) = RecFrame.at<Vec3b>(i + pelX, j + pelY)[0];
        }
      }
      dstName = to_string(pelX) + "_" + to_string(pelY) + "_" + to_string(predMode) + ".jpg";
      imwrite(dstDir + dstName, tmp);
    }
  }
  return;
}
