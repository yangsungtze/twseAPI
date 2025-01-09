# Stage 1: Build
FROM ubuntu:22.04 AS build

# Install build tools and dependencies
RUN apt-get update && apt-get install -y cmake g++ curl libcurl4-openssl-dev

# Set working directory
WORKDIR /app

# Copy source files into the container
COPY . .

# Build the application
RUN rm -rf build && mkdir build && cd build && cmake .. && make

# Stage 2: Runtime
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && apt-get install -y libcurl4 && apt-get clean

# Set working directory
WORKDIR /app

# Copy the built application from the build stage
COPY --from=build /app/build/TWSEAPIFetcher .

# Specify the command to run the application
CMD ["./TWSEAPIFetcher"]
