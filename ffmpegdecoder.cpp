//
//  ffmpegdecoder.h
//  ffmpeg RTSP Client
//
//  Created by Yonghye Kwon on 9/14/18.
//  Copyright (c) Freeeeeeeeeeeeeee
//

#include "ffmpegdecoder.h"


FFmpegDecoder::FFmpegDecoder(std::string path)
    :bConnected(false)
{
    this->path = path;
}

FFmpegDecoder::~FFmpegDecoder()
{
    destroy();
}

void FFmpegDecoder::connect()
{
    avformat_network_init();
    av_register_all();


    pFormatCtx = avformat_alloc_context();

    AVDictionary *avdic=NULL;
    char option_key[]="rtsp_transport";
    char option_value[]="tcp";

    av_dict_set(&avdic,option_key,option_value,0);
    char option_key2[]="max_delay";
    char option_value2[]="100";

    av_dict_set(&avdic,option_key2,option_value2,0);

    if (avformat_open_input(&pFormatCtx, path.c_str(), NULL, &avdic) != 0)
    {
        std::cout << "can't open the file." << std::endl;
        bConnected = false;
        return ;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        std::cout << "can't find stream infomation" << std::endl;
        bConnected = false;
        return ;
    }

    videoStream = -1;


    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
    }

    if (videoStream == -1)
    {
        std::cout << "can't find a video stream" << std::endl;
        bConnected = false;
        return ;
    }

    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    pCodecCtx->bit_rate = 0;
    pCodecCtx->time_base.num = 1;
    pCodecCtx->time_base.den = 10;
    pCodecCtx->frame_number = 1;


    if (pCodec == NULL)
    {
        std::cout << "can't find a codec" << std::endl;
        bConnected = false;
        return ;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        std::cout << "can't open a codec" << std::endl;
        bConnected = false;
        return ;
    }

    pFrame = av_frame_alloc();
    pFrameBGR = av_frame_alloc();


    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

    int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width,pCodecCtx->height);

    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameBGR, out_buffer, AV_PIX_FMT_BGR24,
                   pCodecCtx->width, pCodecCtx->height);

    packet = (AVPacket *) malloc(sizeof(AVPacket));
    av_new_packet(packet, pCodecCtx->width * pCodecCtx->height);

    bConnected = true;
}

void FFmpegDecoder::playMedia()
{
    std::chrono::milliseconds duration(2);

    while (av_read_frame(pFormatCtx, packet) >= 0)
    {
        if (packet->stream_index == videoStream)
        {
            int got_picture = 0;
            int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);

            if (ret < 0)
            {
                std::cout << "decode error.\n" << std::endl;
                break ;
            }

            if (got_picture)
            {
                sws_scale(img_convert_ctx,
                          (uint8_t const * const *) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameBGR->data,
                          pFrameBGR->linesize);

                cv::Mat img(pFrame->height,pFrame->width,CV_8UC3,pFrameBGR->data[0]);
                cv::imshow("display",img);
                cv::waitKeyEx(10);
            }
        }
        av_free_packet(packet);
        std::this_thread::sleep_for(duration);
    }

    bConnected = false;
}

void FFmpegDecoder::destroy()
{
    av_free(out_buffer);
    av_free(pFrameBGR);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}

