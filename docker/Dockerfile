
FROM cpp_review_base:latest

WORKDIR /app/bin

RUN mkdir -p /app/build && rm -rf /app/build/*
ADD . /app/build

# delete cached folder, used when build in local machine.
RUN rm -rf /app/build/cmake-build-*

# create the cmake build folder
RUN mkdir -p /app/build/cmake-build-release

# cmake
RUN cd /app/build && cmake -S /app/build/ -B /app/build/cmake-build-release/ && cmake --build /app/build/cmake-build-release

# copy target executable file to /app/bin folder
RUN cp /app/build/cmake-build-release/CppReview /app/bin/CppReview

# docker entrypoint
ENTRYPOINT ["/app/bin/CppReview"]
