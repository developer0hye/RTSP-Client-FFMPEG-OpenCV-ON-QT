#include <iostream>
#include "ffmpegdecoder.h"


class ImageProc
{

public:
    ImageProc(){}
    ~ImageProc(){}
    void process(FFmpegDecoder& decoder);
};


void ImageProc::process(FFmpegDecoder &decoder)
{
    while(decoder.isConncected())
    {
        std::chrono::milliseconds duration(2);

        cv::Mat src;

        decoder.mtx.lock();
        if(!decoder.decodedImgBuf.empty())
        {
            src = decoder.decodedImgBuf.front().clone();
            decoder.decodedImgBuf.pop_front();
           // std::cout <<"img buffer size = "<< decoder.decodedImgBuf.size() << std::endl;
        }
        decoder.mtx.unlock();

        if(!src.empty())
        {
            //do your stuff...

            //


            cv::imshow("src", src);
            cv::waitKey(10);
        }

        std::this_thread::sleep_for(duration);
    }
}

int main()
{
    FFmpegDecoder decoder("your rstp address");

    decoder.connect();
    if(decoder.isConncected())
    {
        ImageProc imgProc;

        std::thread t1{&FFmpegDecoder::decode, &decoder};
        imgProc.process(decoder);

        t1.join();
    }
    return 0;
}
