//
//  ffmpegdecoder.h
//  ffmpeg RTSP Client
//
//  Created by Yonghye Kwon on 9/14/18.
//  Copyright (c) Freeeeeeeeeeeeeee
//

#ifndef ffmpegdecoder_H
#define ffmpegdecoder_H

#include <iostream>
#include <string>

#include <thread>
#include <mutex>
#include <chrono>

#include <opencv2/opencv.hpp>

extern "C"
{
#include <libavutil/mathematics.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/pixdesc.h>
#include <libavdevice/avdevice.h>

}

class FFmpegDecoder
{
    public:
        FFmpegDecoder(std::string);
        ~FFmpegDecoder();

        void connect();
        void decode();

        bool isConncected() const {return bConnected;}

        std::deque <cv::Mat> decodedImgBuf;
        std::mutex mtx;

    private:

        void destroy();

        AVFormatContext *pFormatCtx;
        AVCodecContext *pCodecCtx;
        AVCodec *pCodec;
        AVFrame *pFrame, *pFrameBGR;
        AVPacket *packet;
        uint8_t *outBuffer;
        SwsContext *imgConvertCtx;

        int videoStream;

        std::string path;

        bool bConnected;
};

#endif
