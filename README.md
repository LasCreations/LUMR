<h1 align="center"><b>Trivᕋal</b></h1>
<br/>
<i>~ Link for live website will be available soon. ~</i>
<br/>

## What is Trivᕋal?
The underlying concept of TrivPal is to create a social environment that combines both the use of direct messaging and blog posting to help users connect with each other. 

## Direct Messaging & Blog Post
TrivPal facilitates communication among users through the use of real-time direct messaging and blogs. Both these features allow persons to both share thoughts, knowledge and experiences through the form of text, audio and images. 
Users will be able to send and accept friend requests. 

## Web Architecture
The project takes the approach of using microservices architecture where it will break down the project into different services.
- `backend` : C++
- `database` : Mysql
- `frontend` : Html, Css, Javascript
	
## Compile
### Using Docker

Building an image
- sudo docker build . -t {name you want to call the image}

Remove an image
- sudo docker rmi -f {image name}

Run an image 
- sudo docker run -p {External Port}:{Container Port} -it {image name}

Check Container status
- sudo docker ps

### Using Docker-Compose

Run in folder where .yaml file is 
<br>
Start up docker compose
- sudo docker-compose up -d

Stop docker compose
- sudo docker-compose down

### Using CMake
- Run the complie script file to build the project




### Task List
- [x] Setup Webserver

- [ ] Design Database Schema
    - [ ] Design Schema
    - [ ] User (userID, password, email)
    - [ ] Message(messageId, receiver, sender, timestamp, content)
    - [ ] Blog(postID, content, userID, timestamp)
    - [ ] Database Queries

- [ ] User Authentication
    - [ ] Signup
    - [ ] Login
    - [ ] Cookies