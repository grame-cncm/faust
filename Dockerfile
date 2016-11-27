FROM debian:stable-slim
MAINTAINER Vincent Giersch <vincent@flat.io>

RUN mkdir /faust
WORKDIR /faust
COPY . /faust

RUN \
  apt-get update && \
  apt-get install -y build-essential libssl-dev llvm libncurses5-dev libssl1.0.0 libncurses5 && \
  rm -rf /var/lib/apt/lists/* && \
  make && make install && \
  make -C tools/faust2appls install && \
  make clean && \
  apt-get purge -y build-essential libssl-dev llvm libncurses5-dev && apt-get autoremove -y

ENTRYPOINT ["/usr/local/bin/faust"]
