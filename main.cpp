#include <iostream>
#include "ffmpegdecoder.h"

int main()
{
    FFmpegDecoder decoder("your rtsp address");

    decoder.connect();

    if(decoder.isConncected())
    {
        std::thread t1{&FFmpegDecoder::decode, &decoder};

        t1.join();
    }

    return 0;
}
