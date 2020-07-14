#!/bin/bash
sudo docker run \
  --rm \
  -it \
  --gpus all \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -e QT_X11_NO_MITSHM=1 \
  --privileged \
  brucknem/libopengl \
  bash


