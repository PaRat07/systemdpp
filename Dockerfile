FROM alpine:3.22.4 AS builder

RUN apk add --no-cache cmake git python3 build-base

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

RUN cmake -B build  -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/app .

RUN cmake --build ./build

FROM scratch

COPY --from=builder /app/ /app/

ENTRYPOINT [ "/app/systemdpp-ctl" ]
