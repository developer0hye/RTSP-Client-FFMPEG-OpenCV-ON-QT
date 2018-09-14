# RTSP-Client-FFMPEG-OpenCV-ON-QT

if you want to process only a image except a packet, you can easily process a image by using the below code.

```

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
  cv::VideoCapture vc("your rtsp address");

  if(vc.isOpened())
  {
    cv::Mat src;

    while(vc.read(src))
    {
      cv::imshow("src",src);
      cv::waitKey(10);
    }
  }

  return 0;
}

```
