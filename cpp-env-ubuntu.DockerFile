# Build and run:
#   docker build -t cpp-env-ubuntu:1.0 -f cpp-env-ubuntu.DockerFile. .

FROM ubuntu:20.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y build-essential \
      gcc \
      g++ \
      gdb \
      clang \
      make \
      ninja-build \
      autoconf \
      automake \
      libtool \
      locales-all \
      dos2unix \
      rsync \
      tar \
      python \
      python-dev \
      wget \
      nano \
      libssl-dev \
  && apt-get clean

RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.3/cmake-3.24.3.tar.gz

RUN tar -zxvf cmake-3.24.3.tar.gz

RUN cd cmake-3.24.3 \
  && ./bootstrap \
  && make \
  && make install 

RUN cd /

RUN ln /usr/local/bin/cmake /usr/bin/cmake \
  && ln -s /usr/local/share/cmake-3.24/ /usr/share/cmake-3.24

RUN wget https://sourceware.org/pub/valgrind/valgrind-3.20.0.tar.bz2

RUN tar -xvf valgrind-3.20.0.tar.bz2

RUN cd valgrind-3.20.0 \
  && ./autogen.sh \
  && ./configure \
  && make \
  && make install 


