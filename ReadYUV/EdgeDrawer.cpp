#include "EdgeDrawer.h"


EdgeDrawer::EdgeDrawer(uc Color)
{
  color = Color;
}


EdgeDrawer::~EdgeDrawer()
{
}

void EdgeDrawer::drawEdge(Mat& img, vector<CU>& edges, ui mxaa)
{
  //������ÿһ���߶����бߵĻ滭,Ҳ�����������ܻ�һȦ
  ui height = img.rows;
  ui width = img.cols;
  Mat tmp(height * mxaa, width * mxaa, CV_8UC3);
  resize(img, tmp, Size(height * mxaa, width * mxaa));
  ui edgeNum = edges.size();

  for (ui i = 0; i < edgeNum; ++i)
  {
    ui X = edges[i].X;
    ui Y = edges[i].Y;
    ui size = edges[i].size;
    ui leftTopX = X;
    ui leftTopY = Y;
    ui rightDownX = X + size - 1;
    ui rightDownY = Y + size - 1;
    leftTopX *= mxaa;
    leftTopY *= mxaa;
    rightDownX *= mxaa;
    rightDownY *= mxaa;
    //������������,
    for (ui xx = leftTopX; xx <= rightDownX; ++xx)
    {
      tmp.at<Vec3b>(xx, leftTopY)[0] = color;
      tmp.at<Vec3b>(xx, leftTopY)[1] = color;
      tmp.at<Vec3b>(xx, leftTopY)[2] = color;
      tmp.at<Vec3b>(xx, rightDownY)[0] = color;
      tmp.at<Vec3b>(xx, rightDownY)[1] = color;
      tmp.at<Vec3b>(xx, rightDownY)[2] = color;
    }
    //������������
    for (ui yy = leftTopY; yy <= rightDownY; ++yy)
    {
      tmp.at<Vec3b>(leftTopX, yy)[0] = color;
      tmp.at<Vec3b>(leftTopX, yy)[1] = color;
      tmp.at<Vec3b>(leftTopX, yy)[2] = color;
      tmp.at<Vec3b>(rightDownX, yy)[0] = color;
      tmp.at<Vec3b>(rightDownX, yy)[1] = color;
      tmp.at<Vec3b>(rightDownX, yy)[2] = color;
    }
  }

  resize(tmp, img, Size(height, width));
  return;
}
