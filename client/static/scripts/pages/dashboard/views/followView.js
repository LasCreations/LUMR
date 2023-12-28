var imageContainer, usernameContainer, btnContainer, userDiv;
var imageElement, buttonElement;

export function getFollowers() {
    
}

export function getFollowing() {
    
}

function createContainers(){
    userDiv = document.createElement('div'); //main div container
    imageContainer = document.createElement('div');  //Container to hold image
    usernameContainer = document.createElement('div');  //container to hold username
    btnContainer = document.createElement('div'); //container to hold the btn to show Unfollow

    userDiv.className = 'user';
    imageContainer.className = 'F-imageContainer';
    usernameContainer.className = 'F-usernameContainer';
    btnContainer.className = 'F-btnContainer'
}

function createElements(username, src, status){
    var imageElement = document.createElement('img');
    //creating button element
    var buttonElement = document.createElement('button');

    imageElement.className = 'imageElement';
    buttonElement.className = 'buttonElement';

    buttonElement.textContent = 'Follow';
    imageElement.src = "/avatars/avatar1.jpg";
    usernameContainer.textContent = username;
}

function addElementsToContainer(){

}




// var userDiv = document.createElement('div'); //main div container
    
//     var imageContainer = document.createElement('div');  //Container to hold image
//     var usernameContainer = document.createElement('div');  //container to hold username
//     var btnContainer = document.createElement('div'); //container to hold the btn to show Unfollow


//     //assigning class names to div
//     userDiv.className = 'user';
//     imageContainer.className = 'F-imageContainer';
//     usernameContainer.className = 'F-usernameContainer';
//     btnContainer.className = 'F-btnContainer'

//     //creating image element
//     var imageElement = document.createElement('img');
//     //creating button element
//     var buttonElement = document.createElement('button');

//     imageElement.className = 'imageElement';
//     buttonElement.className = 'buttonElement';

//     buttonElement.textContent = 'Follow';
//     imageElement.src = "/avatars/avatar1.jpg";
//     usernameContainer.textContent = username;


    
//     imageContainer.appendChild(imageElement);
//     btnContainer.appendChild(buttonElement);
//     //usernameContainer
    
//     userDiv.appendChild(imageContainer);
//     userDiv.appendChild(usernameContainer);
//     userDiv.appendChild(btnContainer);

//     document.getElementById('users-container').appendChild(userDiv); //append div to container
  