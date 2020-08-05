FROM ubuntu:18.04

RUN apt-get update

RUN apt-get update -qq && apt-get install -y wget unzip make gcc g++ git python3 python3-pip

#install cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.1/cmake-3.18.1-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"

#install arm embedded
RUN wget -q https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz -O - | tar -xj

ENV PATH="/gcc-arm-none-eabi-9-2020-q2-update/bin/:${PATH}"

#install nRF5 SDK
RUN wget -q https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/nRF5_SDK_15.3.0_59ac345.zip -O nrf5_sdk.zip && unzip -q nrf5_sdk.zip && mv nRF5_SDK_15.3.0_59ac345 nrf5_sdk && rm nrf5_sdk.zip

#imgtool
RUN git clone https://github.com/JuulLabs-OSS/mcuboot.git && pip3 install -r /mcuboot/scripts/requirements.txt
COPY build.sh /scripts/build.sh

#assume /app is source of repo
CMD chmod +x /scripts/build.sh && /scripts/build.sh


#CMD ls /app
