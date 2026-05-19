FROM alpine:3.22.4 AS builder

RUN apk add --no-cache cmake git python3 build-base clang20 ninja

WORKDIR /project

COPY deps deps
ENV CPM_SOURCE_CACHE=/project/.cache/cpm


RUN cmake -B /tmp/deps-conf -S ./deps && \
    rm -rf /tmp/deps-conf

COPY data data
COPY include include
COPY src src
COPY tests test
COPY CMakeLists.txt .

RUN cmake -B build -G Ninja -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/app -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON .

RUN cmake --build ./build
RUN cmake --install ./build --prefix /app

FROM alpine:3.22.4

RUN apk add --no-cache zsh

COPY --from=builder /app/ /usr/local

ENTRYPOINT ["/usr/local/bin/systemdpp-run"]
