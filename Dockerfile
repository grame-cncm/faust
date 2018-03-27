FROM debian:stable-slim
MAINTAINER Vincent Giersch <vincent@flat.io>

RUN mkdir /faust
WORKDIR /faust
COPY . /faust

RUN \
  apt-get update && \
  apt-get install -y build-essential llvm libncurses5-dev libncurses5 libmicrohttpd-dev git cmake && \
  rm -rf /var/lib/apt/lists/*

RUN \
  make && make install && \
  make clean && \
  apt-get purge -y build-essential llvm libncurses5-dev && apt-get autoremove -y

ENTRYPOINT ["/usr/local/bin/faust"]
