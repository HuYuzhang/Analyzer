#include "def.h"
#include "YUVReader.h"
#include "EdgeDrawer.h"
#include "Spliter.h"
int main(int argc, char** argv)
{
  string GT = "video.yuv";
  string dec = "dec.yuv";
  string dirFile = "dump_dir.txt";
  string dstDir = "1\\";
  Spliter sp(GT, dec, 1024, 1792);
  sp.doSplitYUV(0, dirFile, dstDir);
  return 0;
}