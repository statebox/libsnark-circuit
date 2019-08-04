FROM alpine:3.9

RUN apk add --no-cache wget unzip curl cmake make git gmp gmp-dev \ 
    g++ boost-dev openssl openssl-dev pkgconf

COPY libsnark-circuit libsnark-circuit

RUN git init \
    && cd libsnark-circuit/depends/ \
    && git submodule add https://github.com/scipr-lab/libsnark \
    && git submodule update --init --recursive \	
    && cmake -DWITH_PROCPS=OFF .. \
    && make
