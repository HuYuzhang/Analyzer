
#include "CaffeApplyer.h"




void CaffeApplyer::WrapInputLayer(std::vector<cv::Mat>* data_channels) {
    //Blob<float>* input_layer = net_->input_blobs()[0];
    Blob<float>* data_layer = net_->input_blobs()[0];
    //Blob<float>* pred_layer = net_->input_blobs()[1];


    int width = data_layer->width();
    int height = data_layer->height();
    //float* input_data;
    float* data_p;
    //float* pred_p;

    if (Caffe::mode() == Caffe::CPU)
    {
        data_p = data_layer->mutable_cpu_data();
        //pred_p = pred_layer->mutable_cpu_data();
        //input_data = input_layer->mutable_cpu_data();
    }
    else
    {
        //input_data = input_layer->mutable_cpu_data();
        data_p = data_layer->mutable_gpu_data();
        //pred_p = pred_layer->mutable_gpu_data();
        //input_data = input_layer->mutable_gpu_data();
    }

    //firstly prepare for the data_layer
    for (int i = 0; i < data_layer->channels(); ++i)
    {
        cv::Mat channel(height, width, CV_32FC1, data_p);
        data_channels->push_back(channel);
        data_p += width * height;
    }

    /*for (int i = 0; i < pred_layer->channels(); ++i)
    {
        cv::Mat channel(height, width, CV_32FC1, pred_p);
        pred_channels->push_back(channel);
        pred_p += width * height;
    }*/
}


void CaffeApplyer::WrapOutputLayer(std::vector<cv::Mat>* output_channels) {
    Blob<float>* ourput_layer = net_->output_blobs()[0];

    int width = ourput_layer->width();
    int height = ourput_layer->height();

    float* ouput_data;
    if (Caffe::mode() == Caffe::CPU)
    {
        ouput_data = ourput_layer->mutable_cpu_data();
    }
    else
    {
        //ouput_data = ourput_layer->mutable_cpu_data();
        ouput_data = ourput_layer->mutable_gpu_data();
    }
    for (int i = 0; i < ourput_layer->channels(); ++i) {
        cv::Mat channel(height, width, CV_32FC1, ouput_data);
        output_channels->push_back(channel);
        ouput_data += width * height;
    }
}



void CaffeApplyer::Preprocess(const cv::Mat& img,
    std::vector<cv::Mat>* data_channel) {

    //果然，这里的输入图片的大小应当是64*64的
    //我记得下面之所以要设置成cnt是因为我们的长宽都是1？然后所有的维数都集中在通道数上面了~
    //first let's deal with the data_channel
    int cnt = 0;
    for (int i = 0; i < K; ++i)
    {
        for (int j = 0; j < K + N; ++j)
        {
            //fprintf(stdout, "------------> position is %d %d, size of data_channel's element is %d %d %d\n", i, j, (*data_channel)[cnt].rows, (*data_channel)[cnt].cols, (*data_channel)[cnt].channels());
            (*data_channel)[cnt].at<float>(0, 0) = img.at<float>(i, j);
            ++cnt;
        }
        //i = i;
    }
    for (int i = K; i < K + M; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            (*data_channel)[cnt].at<float>(0, 0) = img.at<float>(i, j);
            ++cnt;
        }
    }

    ////now prepare the pred_channel
    //cnt = 0;
    //for (int i = K; i < K + M; ++i)
    //{
    //    for (int j = K; j < K + N; ++j)
    //    {
    //        (*pred_channel)[cnt].at<float>(0, 0) = img.at<float>(i, j);
    //        ++cnt;
    //    }
    //}
    //ojbk, now we finish all the prepare~
    return;
}

cv::Mat CaffeApplyer::Outputprocess(std::vector<cv::Mat>* output_channel)
{
    //这里也是一样的思路
    cv::Mat ret(M, N, CV_32FC1);

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ret.at<float>(i, j) = (*output_channel)[i * N + j].at<float>(0, 0);
        }
    }
    return ret;
}



CaffeApplyer::CaffeApplyer(const string& model_file, const string& trained_file, bool ifGPU) {
    //我们认为，目前输入的图像的大小是64*64的。。。
    //ifGPU = false;
    if (ifGPU)
    {
        Caffe::set_mode(Caffe::GPU);
    }
    else
    {
        Caffe::set_mode(Caffe::CPU);
    }


    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);

    //CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
    //CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";
    fprintf(stdout, "------------> Number of the input is %d\n", net_->num_inputs());
    fprintf(stdout, "------------> Number of the output is %d\n", net_->num_outputs());

    //now begin my change!!!
    Blob<float>* data = net_->input_blobs()[0];
    //Blob<float>* pred = net_->input_blobs()[1];
    fprintf(stdout, "------------> Size of the data is height: %d width %d\n", data->height(), data->width());
    //fprintf(stdout, "------------> Size of the pred is height: %d width %d\n", pred->height(), pred->width());
    //其实下面这些东西都没什么用。。。只是模仿他原来的写法罢了
    data_channel = data->channels();
    //pred_channel = pred->channels();
}

cv::Mat CaffeApplyer::run_Filter(const cv::Mat& img) {

    //似乎mat只能是2维的？？？那么就先这样子，默认高度是1（虽然和向量的规定似乎不符合？），宽度是3072/1024
    cv::Mat f_img;
    img.convertTo(f_img, CV_32FC1);
    f_img /= 255.0;
    std::vector<cv::Mat> data_channel;
    std::vector<cv::Mat> output_channel;
    WrapInputLayer(&data_channel);
    Preprocess(f_img, &data_channel);
    WrapOutputLayer(&output_channel);
    net_->Forward();
    cv::Mat pred = Outputprocess(&output_channel);
    cv::Mat ret(64, 64, CV_8UC1);
    for (int i = 0; i < 64; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            ret.at<unsigned char>(i, j) = img.at<cv::Vec3b>(i, j)[0];
        }
    }
    for (int i = K; i < K + M; ++i)
    {
        for (int j = K; j < K + N; ++j)
        {
            ret.at<unsigned char>(i, j) = (unsigned char)(pred.at<float>(i - K, j - K) * 255.0);
        }
    }
    return ret;
}
