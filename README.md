## tests of cpp

### run in docker
- build base image to reduce the build time
  ```
  docker build -t cpp_review_base:latest -f docker/Dockerfile-base .
  ```
- build app image
  ```
  docker build -t cpp_review_app:latest -f docker/Dockerfile .
  ```
- run the built images
  ```
  docker run -it --rm cpp_review_app:latest
  ```
  


