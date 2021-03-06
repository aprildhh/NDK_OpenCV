#include <jni.h>
#include <string>
#include <android/log.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


extern "C" JNIEXPORT jstring

JNICALL
Java_com_dhh_ndk_1opencv_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_dhh_ndk_1opencv_MainActivity_grayP(JNIEnv *env, jclass type, jintArray pixels_, jint w,
                                            jint h) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    if (pixels == NULL) {
        return 0;
    }

    /**
     * RGBA  将数组转化成Mat
     * bitmap中ARGB_8888 实际的通道顺序是BGRA
     * CV_8UC4 cv_表示在OpenCV中使用，8 代表每一个通道占的位数， U unsigned， C char， 4 通道数
     */
    Mat imgData(h, w, CV_8UC4, (unsigned char *) pixels);

    /**
     * 指针方式--操作像素
     * 速度快耗时少，但很容易发生越界
     */
//    uchar *ptr = imgData.ptr(0);
//
//    //获取当前的CPU钟摆时间
//    double time = static_cast<double >(getTickCount());
//
//    //中间是运行过程
//    for (int i = 0; i < w * h; ++i) {
//        /**
//         * 灰度值计算公式  像素灰度值 = R*0.3+ G*0.59 + B*0.11
//         * 从RGB转Y（亮度）UV得出来的
//         * 矩阵的第一行就是一个灰度值
//         */
//        uchar gray = (uchar) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
//                              ptr[4 * i + 0] * 0.114);
//        ptr[4 * i + 0] = gray;
//        ptr[4 * i + 1] = gray;
//        ptr[4 * i + 2] = gray;
//
//    }
//
//    //计算运行时间
//    time = ((double) getTickCount() - time) / getTickFrequency();
//    __android_log_print(ANDROID_LOG_ERROR,"指针方式--操作像素所用时长","%lf",time);//0.102784


    /**
     * 迭代器--操作像素  0.581679
     * 保证在像素范围内，不会越界，安全性高
     */
//    //获取当前的CPU钟摆时间
//    double time = static_cast<double >(getTickCount());
//    //创建起始位置的迭代器
//    //Vec代表矩阵，4 代表通道数，b 代表uchar类型
//    Mat_<Vec4b>::iterator it = imgData.begin<Vec4b>();
//
//    //创建结束位置的迭代器
//    Mat_<Vec4b>::iterator itend = imgData.end<Vec4b>();
//
//    for (; it != itend; ++it) {
//        uchar gray = (*it)[2] * 0.299 + (*it)[1] * 0.587 + (*it)[0] * 0.114;
//        (*it)[0] = gray;
//        (*it)[1] = gray;
//        (*it)[2] = gray;
//    }
//
//    //计算运行时间
//    time = ((double) getTickCount() - time) / getTickFrequency();
//    __android_log_print(ANDROID_LOG_ERROR, "迭代器--操作像素所用时长", "%lf", time);//0.581317


    /**
     * 动态地址计算--操作像素
     */
//    //获取图片的行列数
//    int row = imgData.rows;
//    int col = imgData.cols;
//    double time = static_cast<double >(getTickCount());
//    for (int i = 0; i < row; ++i) {
//        for (int j = 0; j < col; ++j) {
//            uchar gray = imgData.at<Vec4b>(i, j)[2] * 0.299 + imgData.at<Vec4b>(i, j)[1] * 0.587 +
//                         imgData.at<Vec4b>(i, j)[0] * 0.114;
//            imgData.at<Vec4b>(i, j)[0] = gray;
//            imgData.at<Vec4b>(i, j)[1] = gray;
//            imgData.at<Vec4b>(i, j)[2] = gray;
//        }
//    }
//
//    //计算运行时间
//    time = ((double) getTickCount() - time) / getTickFrequency();
//    __android_log_print(ANDROID_LOG_ERROR, "动态地址计算--操作像素所用时长：", "%lf", time);//0.609992


//    /**
//     * 亮度和对比度--操作像素
//     */
//    uchar *ptr = imgData.ptr(0);
//
//    //获取当前的CPU钟摆时间
//    double time = static_cast<double >(getTickCount());
//    int a = 4;  //对比度
//    int b = 50; //亮度
//    //中间是运行过程
//    for (int i = 0; i < w * h; ++i) {
//        /**
//         * 灰度值计算公式  像素灰度值 = R*0.3+ G*0.59 + B*0.11
//         * 从RGB转Y（亮度）UV得出来的
//         * 矩阵的第一行就是一个灰度值
//         */
//        //把灰度注释掉
////        uchar gray = (uchar) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
////                              ptr[4 * i + 0] * 0.114);
//        //对每一个像素针对性的处理,容易越界
////        ptr[4 * i + 0] = (ptr[4 * i + 0] + b) > 255 ? 255 : ptr[4 * i + 0] + b;
////        ptr[4 * i + 1] = (ptr[4 * i + 1] + b) > 255 ? 255 : ptr[4 * i + 0] + b;
////        ptr[4 * i + 2] = (ptr[4 * i + 2] + b) > 255 ? 255 : ptr[4 * i + 0] + b;
//
////        //亮度
//        //*********是saturate_cast，不是static_cast**********
//        ptr[4 * i + 0] = saturate_cast<uchar>( ptr[4 * i + 0] + b);
//        ptr[4 * i + 1] = saturate_cast<uchar>( ptr[4 * i + 1] + b);
//        ptr[4 * i + 2] = saturate_cast<uchar>( ptr[4 * i + 2] + b);
//
////        //对比度
////        ptr[4 * i + 0] = saturate_cast<uchar>( ptr[4 * i + 0] * a);
////        ptr[4 * i + 1] = saturate_cast<uchar>( ptr[4 * i + 1] * a);
////        ptr[4 * i + 2] = saturate_cast<uchar>( ptr[4 * i + 2] * a);
//
//    }
//
//    //计算运行时间
//    time = ((double) getTickCount() - time) / getTickFrequency();
//    __android_log_print(ANDROID_LOG_ERROR, "亮度和对比度--操作像素所用时长", "%lf", time);//0.102784


//    /**
//     * 颜色通道的分离与合并
//     */
//    Mat img(h, w, CV_8UC4, (unsigned char *) pixels);
//
//    vector<Mat> outimgs;
//    //分离
//    split(imgData, outimgs);
//    //代表第一个通道
//    Mat out1;
//    out1 = outimgs.at(0);
//
//    //合并
//    //把outimgs进行操作之后，还原到imgData中，或者新建一个Mat img参数和imgData一样
//    merge(outimgs,img);

//    /**
//     * 颜色空间的转换
//     */
//    cvtColor(img,img,CV_BGRA2GRAY);//OpenCV2中的写法，直接将图片变成了一个灰度图，但是通道会变，运行会报错，只是中间操作
//    cvtColor(img,img,COLOR_BGRA2GRAY);//OpenCV3中的写法

    /**
     * 滤波
     */
    Mat img(h, w, CV_8UC4, (unsigned char *) pixels);

    /**
     * 方框滤波：用方框滤波器模糊一张图片
     * boxFilter( InputArray src输入图片, OutputArray dst输出图片, int ddepth（输出图像的深度-1时代表使用原图深度）,
                             Size ksize核的大小, Point anchor锚点（被处理掉的那个点） = Point(-1,-1)核的默认值，表示核的中心点,
                             bool normalize = true表示内核是否被区域归一化,
                             int borderType = BORDER_DEFAULT 边界值，一般不对其改变)
     */
    //其他参数都使用默认值
//    boxFilter(img,img,-1,Size(50,50));

//    /**
//     * 均值滤波：去燥（缺陷：不能保护图像细节，不可避免的会模糊）
//     * blur( InputArray src, OutputArray dst,
//                        Size ksize, Point anchor = Point(-1,-1),
//                        int borderType = BORDER_DEFAULT )
//     * src 输入：有要求格式
//     * dst 输出：要求和原图片有一样的尺寸和类型
//     * ksize 核: 值比较小的时候属于高通，有锐化的效果
//     * borderType 边界值
//     * /
//    blur(img,img,Size(15,15));

    /**
     * 高斯滤波
     * GaussianBlur( InputArray src, OutputArray dst, Size ksize,
                                double sigmaX, double sigmaY = 0,
                                int borderType = BORDER_DEFAULT )
     * src 输入：有要求格式
     * dst 输出：要求和原图片有一样的尺寸和类型
     * ksize：宽度和高度数值必须为正数和奇数，或者都是0
     * sigmaX：当前的高斯核函数在X轴上的一个标准偏差
     * sigmaY：当前的高斯核函数在Y轴上的一个标准偏差，
     *         如果y=0,也就是让x也等于0，就要根据ksize中的值进行计算
     *         如果y有值，x也有值，就把ksize中的值都设置为0，让它自行去运算
     * borderType：
     */
    GaussianBlur(img,img,Size(55,55),0);



    //腐蚀效果
//    Mat ppt = getStructuringElement(MORPH_RECT,Size(50,50));
//    erode(imgData,imgData,ppt);

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);
    return result;
}