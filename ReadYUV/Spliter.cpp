#include "Spliter.h"


Spliter::Spliter(string GTFile, string RecFile, ui h, ui w, ui frameNum) : GTReader(GTFile, h, w), RecReader(RecFile, h, w), frameNumber(frameNum)
{
}


Spliter::~Spliter()
{
}

/*
param:
idx：需要对于第几帧进行split（从0开始计数）
predDirectionFile：存储这一帧所有的CU块预测模式的文本文件
dstDir：存储处理结果的路径位置（暂时咱先手动建立一下，打算是一帧先对应于一个目录，目录名可以就用idx表示）
*/


void Spliter::doSplitYUV(string predDirectionFile, string dstDir)
{
  ui planarCnt = 0;
  ui dcCnt = 0;
  ui angleCnt = 0;
  ifstream fin = ifstream(predDirectionFile);
  if (!fin)
  {
    cout << "Fail to open the predDirectionFile: " << predDirectionFile << endl;
    exit(0);
  }

  ui frame_id, pelX, pelY, predMode;
  string dstName;
  string planar = "planar\\";
  string dc = "dc\\";
  string angle = "angle\\";
  const ui blockEachFrame = (1792 / 32) * (1024 / 32);
  //对于每一帧进行数据处理
  for (ui f = 0; f < frameNumber; ++f)
  {
    Mat GTFrame = GTReader.readFrameYUV(f);
    Mat RecFrame = RecReader.readFrameYUV(f);
    Mat tmp(64, 64, CV_8UC1);
    ui blockCnt = 0;
    while (fin >> frame_id >> pelY >> pelX >> predMode)//每次都读入一个CU的相关信息
    {
      ++blockCnt;
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
        dstName = to_string(f) + "_" + to_string(pelX) + "_" + to_string(pelY) + "_" + to_string(predMode) + ".jpg";
        if (predMode == 0)
        {
          ++planarCnt;
          imwrite(dstDir + planar + dstName, tmp);
        }
        else if (predMode == 1)
        {
          ++dcCnt;
          imwrite(dstDir + dc + dstName, tmp);
        }
        else
        {
          ++angleCnt;
          imwrite(dstDir + angle + dstName, tmp);
        }
      }
      if (blockCnt == blockEachFrame)
      {
        break;//完成了对于当前帧所有CU信息的读取
      }
    }
    cout << "Frame: " << f << " finished" << endl;
  }
  cout << "----------------------------------------------" << endl;
  cout << "Totally, we have PLANAR: " << planarCnt << ", DC: " << dcCnt << ", Angle: " << angleCnt << endl;
  cout << "----------------------------------------------" << endl << endl;
}


void Spliter::doSplitYUV(ui idx, string predDirectionFile, string dstDir)
{
  //这里就只把YUV当中的Y存下来
  //emmm要不要忽略左上角那个呢，好像左上角那个确实也没有什么利用价值，那么暂且忽略掉吧
  //算了，现在的打算是直接放弃最左边和最上面这一行一列，主要原因在于无法获取参考像素
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
  //这里我们只存亮度通道吧。设置成64的原因是咱想让input和label干脆长在一起吧。
  //虽然在同一张图中，但是右下角的块是和其他三块来自不同的图像中的。
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
