FROM ubuntu:xenial

RUN apt-get update

# CircleCI requirements
RUN apt-get install -y \
  git \
  ssh \
  tar \
  gzip \
  ca-certificates

# Our general requirements
RUN apt-get install -y \
  build-essential \
  software-properties-common

# LLVM
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
# Fingerprint: 6084 F3CF 814B 57C1 CF12 EFD5 15CF 4D18 AF4F 7421
RUN apt-add-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-5.0 main" 
RUN apt-get update && apt-get install -y \
  clang-5.0 \
  lldb-5.0 \
  lld-5.0 \
  clang-tidy-5.0 \
  clang-format-5.0

# CMake
RUN wget https://cmake.org/files/v3.9/cmake-3.9.4.tar.gz
RUN tar --extract --gunzip --file cmake-3.9.4.tar.gz
RUN cd cmake-3.9.4 && \
  ./bootstrap &&  \
  make -j2 && \
  make install -j2 
RUN rm cmake-3.9.4.tar.gz && \
  rm -rf cmake-3.9.4

# Coveralls
RUN apt-get install -y python-pip
RUN pip install --upgrade pip
RUN pip install --prefix /usr/local cpp-coveralls

