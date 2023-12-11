FROM gcc:latest

# Install dependencies
RUN apt-get update && apt-get install -y libmysqlcppconn-dev cmake make build-essential

# Copy the current directory contents into the container at /app
COPY . /usr/src/auth

# Set the working directory to /app
WORKDIR /usr/src/auth

# Compile the C++ code using CMake
RUN cmake .

# Build the C++ executable
RUN make

# Specify the command to run on container start
CMD ["./authentication"]