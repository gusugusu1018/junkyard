for /f "tokens=1-3 delims=/" %%a in ("%date%") do echo %%a%%b%%c
netsh interface ip show interfaces
netsh wlan set hostednetwork mode=allow
netsh wlan set hostednetwork ssid=SSID
netsh wlan set hostednetwork key=PASS keyUsage=persistent
netsh wlan start hostednetwork

pause
