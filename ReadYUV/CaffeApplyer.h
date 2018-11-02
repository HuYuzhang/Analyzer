#include "caffe_head.h"
#include <time.h>

#include <caffe/caffe.hpp>
#include <caffe/layers/memory_data_layer.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\gpu\gpumat.hpp>

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define USE_OPENCV 1
#define CPU_ONLY 1

using namespace caffe;  // NOLINT(build/namespaces)
using std::string;
using GpuMat = cv::gpu::GpuMat;

/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;

class CaffeApplyer {
public:
    CaffeApplyer(const string& model_file,
        const string& trained_file, bool ifGPU = false);

    //void change_model(const string& trained_file);

    cv::Mat run_Filter(const cv::Mat& img);

private:

    //void WrapInputLayer(std::vector<cv::Mat>* input_channels);
    void WrapInputLayer(std::vector<cv::Mat>* data_channels);

    void WrapOutputLayer(std::vector<cv::Mat>* input_channels);

    void Preprocess(const cv::Mat& img,
        std::vector<cv::Mat>* data_channel);

    cv::Mat Outputprocess(std::vector<cv::Mat>* output_channel);

private:
    std::shared_ptr<Net<float> > net_;
    boost::shared_ptr<Net<float> > net;
    int data_channel;
    int pred_channel;
    int K = 32;
    int M = 32;
    int N = 32;
    //int model_qp;
};