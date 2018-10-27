#include "YUVReader.h"

YUVReader::YUVReader(string s, ui h, ui w)
{
  fileName = s;
  height = h;
  width = w;
  fin = ifstream(s, ios::binary | ios::in);
  if (!fin)
  {
    cout << "Failed to open the file: " << s << endl;
    exit(0);
  }
}


YUVReader::~YUVReader()
{
}

cv::Mat YUVReader::readFrameYUV(ui idx)
{
  ui offset = idx * height * width * 3 / 2;
  ui pixelNum = height * width * 3 / 2;
  fin.seekg(offset, ios::beg);
  cv::Mat ret(height, width, CV_8UC3);
  uc* buf = new uc[pixelNum];
  uc* tmp = buf;
  fin.read((char *)buf, pixelNum);
  //cout << fin.gcount();
  ui sub_height = height >> 1;
  ui sub_width = width >> 1;

  for (ui i = 0; i < height; ++i)
  {
    for (ui j = 0; j < width; ++j)
    {
      ret.at<cv::Vec3b>(i, j)[0] = tmp[i * width + j];
    }
  }
  tmp += width * height;
  for (ui i = 0; i < sub_height; ++i)
  {
    for (ui j = 0; j < sub_width; ++j)
    {
      ret.at<cv::Vec3b>(2 * i, 2 * j)[1] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i, 2 * j + 1)[1] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i + 1, 2 * j)[1] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i + 1, 2 * j + 1)[1] = tmp[i * sub_width + j];
    }
  }
  tmp += sub_width * sub_height;
  for (ui i = 0; i < sub_height; ++i)
  {
    for (ui j = 0; j < sub_width; ++j)
    {
      ret.at<cv::Vec3b>(2 * i, 2 * j)[2] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i, 2 * j + 1)[2] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i + 1, 2 * j)[2] = tmp[i * sub_width + j];
      ret.at<cv::Vec3b>(2 * i + 1, 2 * j + 1)[2] = tmp[i * sub_width + j];
    }
  }
  //cv::cvtColor(ret, ret, CV_YCrCb2RGB);
  delete[] buf;
  return ret;
}
cv::Mat YUVReader::readFrameRGB(ui idx)
{
  cv::Mat ret(height, width, CV_8UC3);
  ret = readFrameYUV(idx);
  cvtColor(ret, ret, CV_YUV2RGB);
  return ret;
}
string YUVReader::getFileName()
{
  return fileName;
}