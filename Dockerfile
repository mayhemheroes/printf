# Build Stage
FROM --platform=linux/amd64 ubuntu:20.04 as builder

## Add source code to the build stage.
ADD . /printf
WORKDIR /printf

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y clang

## TODO: ADD YOUR BUILD INSTRUCTIONS HERE.
RUN clang -fsanitize=fuzzer fuzz_printf.c printf.c -o fuzz_printf

#Package Stage
FROM --platform=linux/amd64 ubuntu:20.04

## TODO: Change <Path in Builder Stage>
COPY --from=builder /printf/fuzz_printf /
