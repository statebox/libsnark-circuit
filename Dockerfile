FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y \
    wget unzip curl \
    build-essential cmake git libgmp3-dev libprocps4-dev python-markdown libboost-all-dev libssl-dev pkg-config


COPY libsnark-circuit libsnark-circuit

RUN cd libsnark-circuit/depends/ \
    && git submodule add https://github.com/scipr-lab/libsnark \
    && git submodule update --init --recursive \	
    && cd .. && mkdir build && cd build \
    && cmake .. \
    && make

RUN ls -al \
    && cd build && ls -al
	
