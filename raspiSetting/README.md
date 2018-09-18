# how to disabloe on board wifi
```
sudo vim /etc/modprobe.d/raspi-blacklist.conf
blacklist brcmfmac
blacklist brcmutil
```

# Changed core freq for uart serial connection
```
sudo vim /boot/config.txt
enable_uart=1
dtoverlay=pi3-miniuart-bt
```

# Changed /boot/cmdline.txt
```
delete console=ttyAMA0,115200 khdboc=ttyAMA0,115200
```

# stop and disalbe remain deamon 
```
sudo systemctl stop hciuart.service
sudo systemctl disable hciuart.service
sudo systemctl stop serial-getty@ttyAMA0.service
sudo systemctl disable serial-getty@ttyAMA0.service
```

```
sudo raspi-config
sudo apt update
sudo apt -y upgrade
sudo apt-get -y dist-upgrade
sudo apt install vim tmux git build-essential raspberrypi-kernel-headers gcc-4.8 wiringpi vlc
uname -a
cat /etc/debian_version
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 60
```

wifi adapterのdriverを取得する。
```
cd
unzip gw-450d2_driver_linux_v3002.zip
tar xf mt7610u_wifi_sta_v3002_dpo_20130916.tar.bz2
git clone https://gist.github.com/moutend/cb35a37297910c99d3e2 gist
```

modified this patch

```
diff --git a/rt_linux.c.patch b/rt_linux.c.patch
index 0d18126..b8824e5 100644
--- a/rt_linux.c.patch
+++ b/rt_linux.c.patch
@@ -8,7 +8,7 @@ diff -ru mt7610u_wifi_sta_v3002_dpo_20130916.orig/os/linux/rt_linux.c mt7610u_wi
 -	if (osfd->f_op && osfd->f_op->read) {
 -		return osfd->f_op->read(osfd, pDataPtr, readLen, &osfd->f_pos);
 +	if (osfd->f_op) {
-+		return __vfs_read(osfd, pDataPtr, readLen, &osfd->f_pos);
++		return kernel_read(osfd, pDataPtr, readLen, &osfd->f_pos);
  	} else {
  		DBGPRINT(RT_DEBUG_ERROR, ("no file read method\n"));
  		return -1;
```

```
cd mt7610u_wifi_sta_v3002_dpo_20130916
make
sudo make install
sudo reboot
cd /etc/network/interfaces.d
vim ifcfg-ra0
```
```
allow-hotplug ra0
iface ra0 inet manual
	wpa-conf /etc/wpa_supplicant/wpa_supplicant-ra0.conf
```


## If you want to use static IP
```
vim dhcpcd.conf

interface ra0
ssid ***
static ip_address=192.168.*.*/24
static routers=192.168.*.1
static domain_name_servers=192.168.*.1

interface wlan0
ssid ***
static ip_address=192.168.*.*/24
static routers=192.168.*.1
static domain_name_servers=192.168.*.1
```

```
sudo apt install bootchart
#cmdline.txtにinit=/sbin/bootchartdを追加
sudo bootchart
# /var/log/bootchart.tgzをubuntuに持って行き調べる。
```

IPアドレスがわからないときのSSH接続にむけて
```
sudo vim /etc/hostname
sudo vim /etc/hosts
ssh pi@dir3pi.local
```

# Golang Settings
```
wget https://golang.org/dl/go1.11.linux-armv6l.tar.gz
sudo tar -C /usr/local -xzf go1.11.linux-armv6l.tar.gz
echo export PATH=$PATH:/usr/local/go/bin >> ~/.bashrc
echo export GOPATH=/home/pi/.go >> ~/.bashrc
source ~/.bashrc
go get -d -u gobot.io/x/gobot/...
```
