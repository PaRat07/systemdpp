FROM alpine:3.24.0 AS builder

RUN apk add --no-cache cmake git python3 build-base clang20 ninja asciidoctor gcompat libstdc++

RUN wget https://www.fastbuild.org/downloads/v1.20/FASTBuild-Linux-x64-v1.20.zip && unzip FASTBuild-Linux-x64-v1.20.zip -d /opt/fastbuild && \
    rm FASTBuild-Linux-x64-v1.20.zip

RUN chmod +x /opt/fastbuild/fbuild /opt/fastbuild/fbuildworker

RUN ln -s /opt/fastbuild/fbuild /usr/local/bin/fbuild
RUN ln -s /opt/fastbuild/fbuildworker /usr/local/bin/fbuildworker

WORKDIR /project

COPY deps deps
ENV CPM_SOURCE_CACHE=/project/.cache/cpm
ENV FASTBUILD_CACHE_PATH=/project/.cache/fbuild
ENV FASTBUILD_CACHE_MODE=rw

RUN mkdir -p /project/.cache/fbuild

RUN cmake -B build -S ./deps && rm -rf build

RUN cmake -B build -S ./deps -G FASTBuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" && \
    cmake --build build --target deps_cache && \
    rm -rf build

COPY data data
COPY include include
COPY src src
COPY tests test
COPY CMakeLists.txt .

RUN cmake -B build -G FASTBuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" .

RUN cmake --build ./build
RUN cmake --install ./build --prefix /app

FROM alpine:3.22.4

RUN apk add --no-cache zsh man-pages mandoc

RUN echo -e "autoload -Uz compinit\ncompinit" | tee /etc/zsh/zshrc

COPY --from=builder /app/ /usr/local

ENTRYPOINT ["/usr/local/bin/_systemdpp-run"]
