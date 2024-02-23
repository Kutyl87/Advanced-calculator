FROM alpine:latest
RUN apk add --no-cache git && apk add --no-cache g++ && apk add --no-cache cmake && apk add --no-cache make
WORKDIR /usr/src/Characters
COPY . . 
WORKDIR /usr/src/Characters/build
RUN   cmake -D CMAKE_CXX_COMPILER=g++ ..
CMD ["make"]
