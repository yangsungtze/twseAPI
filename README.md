# twseAPI
Try getting stock status daily from https://openapi.twse.com.tw/v1/swagger.json using C++ and container

g++ should include "-lcurl"
For dependencies see Dockerfile first, will be edited later.

Remember to check directories for Local or Docker
.dockerignore is for preventing COPY locally bulit builds

# Run Locally
mkdir build
cd build
cmake ..
make
./TWSEFetcher


# Run on Docker
docker build -t twse-api-fetcher .
docker run --rm twse-api-fetcher
