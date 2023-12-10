FROM gcc:latest

# Install dependencies
RUN apt-get update && apt-get install -y libmysqlcppconn-dev cmake make build-essential

# Copy the current directory contents into the container at /app
COPY . /usr/src/PageServing

# Set the working directory to /app
WORKDIR /usr/src/PageServing

# Compile the C++ code using CMake
RUN cmake .

# Build the C++ executable
RUN make

# Specify the command to run on container start
CMD ["./pager-serving-service"]