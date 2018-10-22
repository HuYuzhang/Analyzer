#include "def.h"
#include "YUVReader.h"
#include "EdgeDrawer.h"
int main(int argc, char** argv)
{
  EdgeDrawer drawer(0);
  string path = argv[1];
  Mat img = imread(path);
  vector<CU> v;
  CU cc;
  cc.X = 100;
  cc.Y = 100;
  cc.size = 80;
  v.clear();
  v.push_back(cc);
  drawer.drawEdge(img, v);
  /*
  YUVReader reader(path, 1024, 1792);

  Mat tmp;
  for (int i = 0; i < 10; ++i)
  {
    tmp = reader.readFrame(i);
  }*/
  return 0;
}