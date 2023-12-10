FROM gcc:latest

# Install dependencies
RUN apt-get update && apt-get install -y libmysqlcppconn-dev cmake make build-essential

# Copy the current directory contents into the container at /app
COPY server /usr/src/TrivPalHttpServer/server
COPY client /usr/src/TrivPalHttpServer/server
COPY CMakeLists.txt /usr/src/TrivPalHttpServer
COPY main.cpp /usr/src/TrivPalHttpServer

# Set the working directory to /app
WORKDIR /usr/src/TrivPalHttpServer

# Compile the C++ code using CMake
RUN cmake .

# Build the C++ executable
RUN make

# Specify the command to run on container start
CMD ["./TrivPalServer"]