#bin/sh
#S1=host ip address
gst-launch-1.0 v4l2src device = "/dev/video0" ! video/x-raw, width=640, height=480 ! jpegenc ! rtpjpegpay ! udpsink host=$1 port=5000

