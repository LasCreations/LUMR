let imageContainer, usernameContainer, btnContainer, userDiv;
let imageElement, buttonElement;

import { getToken } from './userdashboard.js'

export function getFollowers() {
    fetch("/user/followers", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ token: getToken() }),
    }).then(res => {
        if (res.ok) {
            console.log("Data recieved");
            return res.json(); // Parse the JSON from the response
        } else {
            console.log("Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        data.forEach(function (user) {
            createFollowView(user.username, "/avatars/" + user.avatarurl + ".jpg", user.status);
        });
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

export function getFollowing() {
    fetch("/user/following", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ token: getToken() }),
    }).then(res => {
        if (res.ok) {
            console.log("Data recieved");
            return res.json(); // Parse the JSON from the response
        } else {
            console.log("Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        data.forEach(function (user) {
            createFollowView(user.username, "/avatars/" + user.avatarurl + ".jpg", user.status);
        });
    }).catch(error => {
        console.error("Error:", error.message);
    });

}



function createFollowView(username, src, status) {
    var userDiv = document.createElement('div'); //main div container

    var imageContainer = document.createElement('div');  //Container to hold image
    var usernameContainer = document.createElement('div');  //container to hold username
    var btnContainer = document.createElement('div'); //container to hold the btn to show Unfollow


    //assigning class names to div
    userDiv.className = 'user';
    imageContainer.className = 'F-imageContainer';
    usernameContainer.className = 'F-usernameContainer';
    btnContainer.className = 'F-btnContainer'

    //creating image element
    var imageElement = document.createElement('img');
    //creating button element
    var buttonElement = document.createElement('button');

    imageElement.className = 'imageElement';
    buttonElement.className = 'buttonElement';

    if (status == true) {
        buttonElement.textContent = 'Following'
    } else {
        buttonElement.textContent = 'Follow'
    }
    imageElement.src = src;
    usernameContainer.textContent = username;



    imageContainer.appendChild(imageElement);
    btnContainer.appendChild(buttonElement);

    userDiv.appendChild(imageContainer);
    userDiv.appendChild(usernameContainer);
    userDiv.appendChild(btnContainer);

    document.getElementById('users-container').appendChild(userDiv);
}

