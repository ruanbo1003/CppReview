
## run
### docker
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
### shell
  1. first build the base docker image to reduce build time
  ```
    docker build -t cpp_review_base:latest -f docker/Dockerfile-base .
  ```
  2. run script
  ```
    ./run.sh
  ```

## errors when build
  1. apt-get update: The repository is not signed  
     update docker version

