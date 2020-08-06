#!/bin/sh

docker run -v /home/frankw/Git/Pinetime:/app  --user $(id -u):$(id -g) ubuntu/freertos

openocd -f swd-stlink.ocd -f flash-app.ocd
