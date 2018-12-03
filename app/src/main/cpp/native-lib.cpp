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

//    /**
//     * 指针方式操作像素
//     */
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
//    __android_log_print(ANDROID_LOG_ERROR,"JNI","%ld",time);


  //获取当前的CPU钟摆时间
    double time = static_cast<double >(getTickCount());

    //中间是运行过程
    for (int i = 0; i < w * h; ++i) {
        /**
         * 灰度值计算公式  像素灰度值 = R*0.3+ G*0.59 + B*0.11
         * 从RGB转Y（亮度）UV得出来的
         * 矩阵的第一行就是一个灰度值
         */
        uchar gray = (uchar) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587 +
                              ptr[4 * i + 0] * 0.114);
        ptr[4 * i + 0] = gray;
        ptr[4 * i + 1] = gray;
        ptr[4 * i + 2] = gray;

    }

    //计算运行时间
    time = ((double) getTickCount() - time) / getTickFrequency();
    __android_log_print(ANDROID_LOG_ERROR,"JNI","%ld",time);

    //腐蚀效果
//    Mat ppt = getStructuringElement(MORPH_RECT,Size(50,50));
//    erode(imgData,imgData,ppt);

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);
    return result;
}