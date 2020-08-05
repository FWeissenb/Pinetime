#!/bin/sh
export LC_ALL=C.UTF-8
export LANG=C.UTF-8

cd /app && mkdir -p build && cd /app/build/ 

cmake -DARM_NONE_EABI_TOOLCHAIN_PATH=/gcc-arm-none-eabi-9-2020-q2-update -DNRF5_SDK_PATH=/nrf5_sdk -DUSE_OPENOCD=1 /app

make -j pinetime-mcuboot-app

/mcuboot/scripts/imgtool.py create --align 4 --version 1.0.0 --header-size 32 --slot-size 475136 --pad-header /app/build/src/pinetime-mcuboot-app.bin /app/build/image.bin




