#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat img = imread("Lena.jpg");
    if (img.empty())
    {
        cout << "无法读取图像" << endl;
        return -1;
    }

    // 转换为灰度图
    Mat grayImg;
    cvtColor(img, grayImg, COLOR_BGR2GRAY);

    // 转换为二值图
    Mat binaryImg;
    threshold(grayImg, binaryImg, 128, 255, THRESH_BINARY);

    // 显示灰度图和二值图
    imshow("Gray Image", grayImg);
    imshow("Binary Image", binaryImg);
    waitKey(0);

    // 输出灰度图
    cout << "灰度图：" << endl;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < img.cols; ++j){
            cout << setw(4) << static_cast<int>(img.at<uchar>(i, j)) << " ";
        }
        cout << endl;
    }
  
    // 计算前两行数的平均值和中位数
    Mat firstTwoRows = img.rowRange(0, 2);
    Scalar meanValue, medianValue;
    meanStdDev(firstTwoRows.reshape(0, 1), meanValue, medianValue);

    double average = meanValue.val[0];
    double median = medianValue.val[0];

    cout << "平均值: " << average << endl;
    cout << "中位数: " << median << endl;

    // 根据阈值处理矩阵数据
    double T = (average + median) / 2;
    cout << "阈值 T: " << T << endl;

    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < img.cols; ++j){
            if (img.at<uchar>(i, j) < T){
                img.at<uchar>(i, j) = 0;
            }
            else{
                img.at<uchar>(i, j) = 255;
            }
        }
    }

    // 输出处理后的矩阵
    cout << "处理后的矩阵：" << endl;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < img.cols; ++j){
            cout << setw(4) << static_cast<int>(img.at<uchar>(i, j)) << " ";
        }
        cout << endl;
    }
    return 0;
}