rem C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0 ksvideosrc device-path="\\\\\?\\usb\#vid_064e\&pid_9314\&mi_00\#6\&2ddc001a\&0\&0000\#\{6994ad05-93ef-11d0-a3cc-00a0c9223196\}\\global" ! decodebin ! autovideosink

rem C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0 ksvideosrc device-index=0 ! video/x-264,width=320,height=90,framerate=10/1 ! x264enc ! queue ! rtph264pay, config-interval=3, pt=96, mtu=1500 ! queue ! tcpserversink host=127.0.0.1 port=9002

rem C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0 ksvideosrc device-index=0 ! video/x-raw, width=640, height=480 ! jpegenc ! rtpjpegpay ! udpsink host=127.0.0.1 port=5000

rem C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0 ksvideosrc device-index=0 ! video/x-raw, width=640, height=480 , framerate=30/1 ! x264enc ! rtph264pay ! tcpserversink host=127.0.0.1 port=5000

rem C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.exe tcpserversrc host=127.0.0.1 port=5000 ! application/x-rtp,encoding-name=H264,payload=96 ! rtph264depay ! video/x-h264 ! queue ! ffdec_h264 ! queue ! autovideosink

C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.exe -v udpsrc port=9000 caps="application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264" ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink sync=f

pause
