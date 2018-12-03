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


    /**
     * 亮度和对比度--操作像素
     */
    uchar *ptr = imgData.ptr(0);

    //获取当前的CPU钟摆时间
    double time = static_cast<double >(getTickCount());
    int a = 4;  //对比度
    int b = 50; //亮度
    //中间是运行过程
    for (int i = 0; i < w * h; ++i) {
        /**
         * 灰度值计算公式  像素灰度值 = R*0.3+ G*0.59 + B*0.11
         * 从RGB转Y（亮度）UV得出来的
         * 矩阵的第一行就是一个灰度值
         */
        //把灰度注释掉
//        uchar gray = (uchar) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
//                              ptr[4 * i + 0] * 0.114);
        //对每一个像素针对性的处理,容易越界
//        ptr[4 * i + 0] = (ptr[4 * i + 0] + b) > 255 ? 255 : ptr[4 * i + 0] + b;
//        ptr[4 * i + 1] = (ptr[4 * i + 1] + b) > 255 ? 255 : ptr[4 * i + 0] + b;
//        ptr[4 * i + 2] = (ptr[4 * i + 2] + b) > 255 ? 255 : ptr[4 * i + 0] + b;

//        //亮度
        //*********是saturate_cast，不是static_cast**********
        ptr[4 * i + 0] = saturate_cast<uchar>( ptr[4 * i + 0] + b);
        ptr[4 * i + 1] = saturate_cast<uchar>( ptr[4 * i + 1] + b);
        ptr[4 * i + 2] = saturate_cast<uchar>( ptr[4 * i + 2] + b);

//        //对比度
//        ptr[4 * i + 0] = saturate_cast<uchar>( ptr[4 * i + 0] * a);
//        ptr[4 * i + 1] = saturate_cast<uchar>( ptr[4 * i + 1] * a);
//        ptr[4 * i + 2] = saturate_cast<uchar>( ptr[4 * i + 2] * a);

    }

    //计算运行时间
    time = ((double) getTickCount() - time) / getTickFrequency();
    __android_log_print(ANDROID_LOG_ERROR, "亮度和对比度--操作像素所用时长", "%lf", time);//0.102784

    //腐蚀效果
//    Mat ppt = getStructuringElement(MORPH_RECT,Size(50,50));
//    erode(imgData,imgData,ppt);

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);
    return result;
}