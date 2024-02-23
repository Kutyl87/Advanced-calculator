FROM alpine:latest
RUN apk add --no-cache git && apk add --no-cache g++ && apk add --no-cache cmake && apk add --no-cache make
WORKDIR /usr/src/app
COPY . . 
WORKDIR /usr/src/app/lib
RUN  mkdir -p build && cd build && cmake -D CMAKE_CXX_COMPILER=g++  .. && make
WORKDIR /usr/src/app/tests
RUN mkdir -p  build && cd build && cmake  -D CMAKE_CXX_COMPILER=g++   .. && make
