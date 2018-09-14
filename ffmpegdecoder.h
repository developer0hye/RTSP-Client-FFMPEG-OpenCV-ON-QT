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

    private:

        void destroy();

        AVFormatContext *pFormatCtx;
        AVCodecContext *pCodecCtx;
        AVCodec *pCodec;
        AVFrame *pFrame, *pFrameBGR;
        AVPacket *packet;
        uint8_t *out_buffer;
        SwsContext *img_convert_ctx;

        int videoStream;

        std::string path;

        bool bConnected;
};

#endif
