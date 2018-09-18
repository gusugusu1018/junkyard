C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0 ksvideosrc device-index=0 ! video/x-raw, width=640, height=480 ! jpegenc ! rtpjpegpay ! udpsink host=127.0.0.1 port=5000

pause
