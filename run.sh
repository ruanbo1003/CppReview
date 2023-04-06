docker build -t cpp_review_base:latest -f docker/Dockerfile-base .
docker build -t cpp_review_app:latest -f docker/Dockerfile .
docker run -it --rm cpp_review_app:latest
