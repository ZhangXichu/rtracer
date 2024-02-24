# Use Ubuntu 22.04 LTS as the base image
FROM ubuntu:22.04

# Set environment variables to avoid user interaction during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtk-3-dev \ 
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libtbb2 libtbb-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libeigen3-dev \
    libtheora-dev \
    libvorbis-dev \
    libxvidcore-dev \
    libx264-dev \
    sphinx-common \
    yasm \
    libfaac-dev \
    libopencore-amrnb-dev \
    libopencore-amrwb-dev \
    libopenexr-dev \
    libgstreamer-plugins-base1.0-dev \
    libavutil-dev \
    libavfilter-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Download OpenCV and OpenCV_contrib
RUN git clone https://github.com/opencv/opencv.git /opt/opencv && \
    git clone https://github.com/opencv/opencv_contrib.git /opt/opencv_contrib

# Checkout the latest version or specific tag
WORKDIR /opt/opencv
RUN git checkout master

WORKDIR /opt/opencv_contrib
RUN git checkout master

# Create a build directory
WORKDIR /opt/opencv
RUN mkdir build

# Configure the build with CMake
WORKDIR /opt/opencv/build
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..

# Compile and install
RUN make -j$(nproc)
RUN make install

# Set the working directory back to the root
WORKDIR /

# Command to run when starting the container
CMD ["bash"]