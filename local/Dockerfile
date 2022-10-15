FROM blipshare/vcpkg:latest

# install libraries using vcpkg
RUN ./vcpkg/vcpkg install fmt oatpp sqlite3 oatpp-sqlite oatpp-swagger

COPY . /app

WORKDIR /app

RUN mkdir build && \
    cmake -B ./build -S . -GNinja -DCMAKE_CXX_COMPILER=g++ -DARM32V7=OFF -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    cmake --build build

EXPOSE 11002

CMD ["/bin/sh", "-c", "./deploy/data_service"]

