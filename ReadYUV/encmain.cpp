#include "def.h"
#include "YUVReader.h"
#include "EdgeDrawer.h"
#include "Spliter.h"
#include "CaffeApplyer.h"
int main(int argc, char** argv)
{
    string modelFile = "angle.caffemodel";
    string deployFile = "deploy.prototxt";
    string imgPath = "img.jpg";
    CaffeApplyer app(deployFile, modelFile);
    Mat img = imread(imgPath);
    img.convertTo(img, CV_8UC1);
    Mat ret = app.run_Filter(img);
    /*string GT = "video.yuv";
    YUVReader reader(GT, 1024, 1792);
    Mat img = reader.readFrameYUV(0);*/
  /*string GT = "video.yuv";
  string dec = "dec.yuv";
  string dirFile = "dump_dir.txt";
  string dstDir = "data\\";
  Spliter sp(GT, dec, 1024, 1792, 702);
  sp.doSplitYUV(dirFile, dstDir);*/
  /*YUVReader ori("video.yuv", 1024, 1792);
  YUVReader rec("rec.yuv", 1024, 1792);
  for (ui i = 0; i < 702; ++i)
  {
    Mat a = rec.readFrameYUV(i);
    Mat b = rec.readFrameYUV(i);
    i = i;
  }*/
  return 0;
}