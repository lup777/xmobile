docker run -it --name docker-avr -p 4444:4444 -v "$(pwd)/DruidFw":/usr/src/app --privileged -v /dev/bus/usb:/dev/bus/usb docker-avr /bin/bash
