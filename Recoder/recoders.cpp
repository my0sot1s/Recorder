#include "recoders.h"

recoders::recoders()
{

}

void recoders::showCam()
{
    VideoCapture cap(0);
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

        if (!cap.isOpened())
            return;

        Mat img;
        namedWindow("WindowCV", CV_WINDOW_AUTOSIZE);
        HOGDescriptor hog;
        hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

        while (true)
        {
            cap >> img;
            if (img.empty())
                continue;

            std::vector<Rect> found, found_filtered;
            hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
            size_t i, j;
            for (i=0; i<found.size(); i++)
            {
                Rect r = found[i];
                for (j=0; j<found.size(); j++)
                    if (j!=i && (r & found[j]) == r)
                        break;
                if (j== found.size())
                    found_filtered.push_back(r);
            }

            for (i=0; i<found_filtered.size(); i++)
            {
                Rect r = found_filtered[i];
                r.x += cvRound(r.width*0.1);
                r.width = cvRound(r.width*0.8);
                r.y += cvRound(r.height*0.07);
                r.height = cvRound(r.height*0.8);
                rectangle(img, r.tl(), r.br(), Scalar(0,255,0), 3);
            }

            imshow("opencv", img);
            if (waitKey(10)>=0)
                break;
        }

}

 int  recoders::imshowWithCaption(const char* windowName, Mat inImage,  const char* caption )
{
    putText( inImage, caption,
            Point( MIN(10,inImage.cols), MIN(20,inImage.rows)),
            FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255) );

    imshow( windowName, inImage );
    return 0;
}


void recoders::setupHogWindow()
{
    namedWindow( _windowName, WINDOW_AUTOSIZE );

        createTrackbar( "scaleFactor" //– Name of the created trackbar.
                       , _windowName  //– Name of the window that will be used as a parent of the created trackbar.
                       , &_trackbar1 //– Optional pointer to an integer variable whose value reflects the position of the slider. Upon creation, the slider position is defined by this variable.
                       , MAX_TRACKBAR  //– Maximal position of the slider. The minimal position is always 0.
                       , hogTrackbarCallback1  //– Pointer to the function to be called every time the slider changes position. This function should be prototyped as void Foo(int,void*); , where the first parameter is the trackbar position and the second parameter is the user data (see the next parameter). If the callback is the NULL pointer, no callbacks are called, but only value is updated.
                       , nullptr// – User data that is passed as is to the callback. It can be used to handle trackbar events without using global variables.
                       );

}

void recoders::hogDetect()
{
    _inImage.copyTo(_outImage);
     vector<Rect> found;
     vector <Rect> found_filtered;
    _hog.detectMultiScale(
                          _inImage //const Mat&
                          //Matrix of the type CV_8U containing an image where objects are detected.
                          , found // vector<Rect>& objects
                          //Vector of rectangles where each rectangle contains the detected object.
                          , _hitThreshold  // hit_threshold=0
                          //hit_threshold – Threshold for the distance between features and SVM classifying plane.  Usually it is 0 and should be specfied in the detector coefficients (as the last free coefficient). But if the free coefficient is omitted (which is allowed), you can specify it manually here.

                          , Size(8,8)//winSize
                          //win_stride – Window stride. It must be a multiple of block stride
                          , Size(32,32)//padding
                          //padding – Mock parameter to keep the CPU interface compatibility. It must be (0,0).
                          , _scaleFactor  // double scale = 1.05
                          //scale0 – Coefficient of the detection window increase.
                             //scaleFactor - Parameter specifying how much the image size is reduced at each image scale.
                          , _groupThreshold  //group_threshold=2
                          //group_threshold – Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping. See groupRectangles() .
                          );

    size_t i, j;




    for( i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];
        for( j = 0; j < found.size(); j++ ) {
            //filter out overlapping rectangles
            if ( j!=i ) {
            Rect iRect =  r;
            Rect jRect = found[j];
            Rect intersectRect = (iRect & jRect);
            if (intersectRect.area()>=iRect.area()*0.9) break;
            }
        }
        if( j == found.size() )
            found_filtered.push_back(r);
    }
    for( i = 0; i < found_filtered.size(); i++ )
    {
        Rect r = found_filtered[i];
        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.5);
        // hacky shift right by 40px - rects seem to be shifted consistently
        r.x +=-40;
        r.width = cvRound(r.width*0.3);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(_outImage, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
    }
    //eliminate overlaps

    //imshow(_windowName, _outImage);
    string param1string = std::string("hitThreshold ") + to_string((int)_hitThreshold);
    string param2string = std::string(" groupThreshold ") + to_string((int)_groupThreshold);
    string param3string = std::string(" scaleFactor ") + to_string(_scaleFactor);
    string combinedString = param1string + param2string + param3string;
    const char* captionString = combinedString.c_str();
    imshowWithCaption(_windowName, _outImage, captionString);

}

void recoders::hogTrackbarCallback1(int trackbarPos, void *)
{
    _trackbar1 = trackbarPos;
        _scaleFactor = trackbarPos/100.0;
        hogDetect();

}

void recoders::peopleDetection()
{
    string filenamestr = "queue.jpg";
        _inImage = imread(filenamestr);
        _hog = HOGDescriptor::HOGDescriptor();
        _hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        namedWindow(_windowName, 1);
        setupHogWindow();
        hogDetect();
}

void recoders::detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
      Mat frame_gray;

      cvtColor( frame, frame_gray, CV_BGR2GRAY );
      equalizeHist( frame_gray, frame_gray );

      //-- Detect faces
      face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t i = 0; i < faces.size(); i++ )
      {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( size_t j = 0; j < eyes.size(); j++ )
         {
           Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
           int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
           circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
         }
      }
      //-- Show what you got
      imshow( window_name, frame );
}

void recoders::loadRuning()
{
//    CvCapture* capture;
       Mat frame;

       VideoCapture capture(0);
           capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
           capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

           if (!capture.isOpened())
               return;

       //-- 1. Load the cascades
       if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return; };
       if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return; };

       //-- 2. Read the video stream

         while( true )
         {
        capture>>frame;
       //-- 3. Apply the classifier to the frame
           if( !frame.empty() )
           { detectAndDisplay( frame ); }
           else
           { printf(" --(!) No captured frame -- Break!"); break; }

           int c = waitKey(10);
           if( (char)c == 'c' ) { break; }
          }
}

