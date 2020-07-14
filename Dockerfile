FROM ubuntu:20.04

MAINTAINER Marcel Bruckner "mbruckner94@gmail.com"

WORKDIR /usr/src/libopengl

COPY examples/ examples/
COPY external/ external/
COPY include/ include/
COPY lib/ lib/
COPY shaders/ shaders/
COPY tests/ tests/
COPY LICENSE .
COPY WORKSPACE .

RUN apt-get update \
  && apt-get install -y -qq --no-install-recommends \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6 \
    curl \
    gnupg \
    wget \
    libglfw3-dev \
    libglm-dev \
    libglu1-mesa-dev \
    freeglut3-dev \
    mesa-common-dev

ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=graphics,utility,compute

RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | \
    tee /etc/apt/sources.list.d/bazel.list && \
    wget https://bazel.build/bazel-release.pub.gpg --no-check-certificate
RUN apt-key add bazel-release.pub.gpg
RUN apt-get update && apt-get install -y -qq --no-install-recommends bazel

RUN rm -rf /var/lib/apt/lists/*

RUN bazel build //...
