import {getToken, followUser} from './events/followUser.js'

import {searchUserProfile} from './events/userSearch.js'

import setUpMenu from './responsive/responsive.js'
import { clearSreen } from './events/clearScreen.js'
import {getProfileData, showUserProfile, showHome} from './views/userdashboard.js'

import {getFollowers, getFollowing} from './views/followView.js' 

window.onload = function () {
    clearSreen(); //CLEARS SCREEN

    var token = {
        token: getToken()
    }

    if (token != null) {
        getProfileData(token);
    } else {
        window.location.href = "/pages/login.html";
    }
};

setUpMenu();

const searchbutton = document.getElementById('search-btn');
searchbutton.addEventListener('click', function() {
    clearSreen();
    searchUserProfile();
});

const homeDiv = document.querySelector('.option1');
homeDiv.addEventListener('click', function() {
    clearSreen();
    showHome();
});

const ProfileDiv = document.querySelector('.option2');
ProfileDiv.addEventListener('click', function() {
    clearSreen();
    showUserProfile();
});

const followBtn = document.querySelector('.follow-btn');
followBtn.addEventListener('click', followUser);


const followerCountView = document.querySelector('.follower-count');
followerCountView.addEventListener('click', function() {
    clearSreen();
    var followView = document.querySelector('.follow-view');
    followView.style.display = 'block';
    getFollowers();
});

const followingCountView = document.querySelector('.following-count');
followingCountView.addEventListener('click', function() {
    clearSreen();
    var followView = document.querySelector('.follow-view');
    followView.style.display = 'block';
    getFollowing();
});

// function fetchData() {
//     // Your fetch request code goes here
//     fetch('/get/notification')
//       .then(response => response.json())
//       .then(data => {
//         // Handle the fetched data as needed
//         console.log(data);
//       })
//       .catch(error => {
//         // Handle errors from the fetch request
//         console.error('Error fetching data:', error);
//       });
//   }
  
// //Call the function on load of the window 

//   // Set up an interval to call fetchData every 1000 milliseconds (1 second)
//   const intervalId = setInterval(fetchData, 3000);