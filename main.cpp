#include <iostream>
#include "ffmpegdecoder.h"

int main()
{
    //this is example... write your own rtsp address
    FFmpegDecoder decoder("rtsp://admin:guest@192.168.3.17:554/udp/unicast/Profile_H264_1");

    decoder.connect();
    if(decoder.isConncected())
    {
        std::thread t1{&FFmpegDecoder::playMedia, &decoder};


        t1.join();
    }

    return 0;
}
