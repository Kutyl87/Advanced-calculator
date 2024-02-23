FROM alpine:latest
RUN apk add --no-cache g++ && apk add --no-cache cmake && apk add --no-cache make
WORKDIR /usr/src/app
COPY . . 
WORKDIR /usr/src/app/lib/build
RUN cmake .. 
CMD ["make"]