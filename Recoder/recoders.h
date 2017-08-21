#ifndef RECODERS_H
#define RECODERS_H

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;


static Mat _inImage;
static Mat _outImage;

static    HOGDescriptor _hog;
static const char* _windowName = "people detector";
static float _hitThreshold = 0;
static float _scaleFactor = 1.059;
static float _groupThreshold = 0.0;
static int MAX_TRACKBAR = 200;
static int _trackbar1 = _scaleFactor * MAX_TRACKBAR/2.0;


class recoders
{
public:
    recoders();
    void showCam();
    static void setupHogWindow();
    static int imshowWithCaption(const char* , Mat,  const char* );
    static void hogDetect ();
    static void hogTrackbarCallback1 (int trackbarPos, void*);
    void peopleDetection();

    // face detection.
    /** @function detectAndDisplay */
    void detectAndDisplay( Mat frame );
    /** Global variables */
    String face_cascade_name = "haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    string window_name = "Capture - Face detection";
    void loadRuning();

};

#endif // RECODERS_H
