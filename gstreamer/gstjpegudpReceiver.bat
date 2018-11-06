C:\gstreamer\1.0\x86_64\bin\gst-launch-1.0.exe udpsrc port=5000 ! application/x-rtp,encoding-name=JPEG,payload=26 ! rtpjpegdepay ! jpegdec ! autovideosink

pause