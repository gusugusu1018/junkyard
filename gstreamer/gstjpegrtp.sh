gst-launch-1.0 v4l2src device = "/dev/video0" ! video/x-raw, width=1920, height=1080 ! jpegenc ! rtpjpegpay ! udpsink host=192.168.137.1 port=5000
