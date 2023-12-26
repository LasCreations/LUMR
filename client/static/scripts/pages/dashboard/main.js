import {getToken, followUser, sendFollowRequest} from './events/followUser.js'

import {searchUserProfile} from './events/userSearch.js'

import setUpMenu from './responsive/responsive.js'

import {getProfileData, fetchAndSetImage, showUserProfile, showHome} from './views/userdashboard.js'


window.onload = function () {
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
searchbutton.addEventListener('click', searchUserProfile);

const homeDiv = document.querySelector('.option1');
homeDiv.addEventListener('click', showHome);

const ProfileDiv = document.querySelector('.option2');
ProfileDiv.addEventListener('click', showUserProfile);

const followBtn = document.querySelector('.follow-btn');
followBtn.addEventListener('click', followUser);
