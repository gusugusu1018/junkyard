#bin/sh
#gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec ! autovideosink
#gst-launch-1.0 udpsrc port=5000 caps="application/x-rtp"media=(string)video, clock-rate=(int)90000,encoding-name=(string)H264! gdpdepay ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink
#gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,encoding-name=H264,payload=26 ! gdpdepay ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink
#gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,media=video,encoding-name=H264 ! queue ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink
gst-launch-1.0 udpsrc port=5000 ! application/x-rtp,media=video,encoding-name=H264 ! queue ! rtph264depay ! avdec_h264 ! autovideosink

