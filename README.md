# RTSP-Client-FFMPEG-OpenCV-ON-QT

## Prerequisite
Install libraries to use ffmpeg
```
sudo apt-get install libavcodec-dev
sudo apt-get install libavformat-dev
sudo apt-get install libavutil-dev
sudo apt-get install libswscale-dev
sudo apt-get install libswresample-dev
sudo apt-get install libavdevice-dev
sudo apt-get install libavfilter-dev
```
Install qtcreator
```
sudo apt-get install qtcreator
```
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
