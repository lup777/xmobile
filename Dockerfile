FROM ubuntu:16.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -q
RUN apt-get install -y binutils gcc-avr avr-libc make

RUN mkdir -p /usr/src/app
VOLUME ["/usr/src/app"]
WORKDIR /usr/src/app
RUN cd /usr/src/app

EXPOSE 4444
