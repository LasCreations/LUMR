import {getToken, followUser} from './events/followUser.js'

import {searchUserProfile} from './events/userSearch.js'

import setUpMenu from './responsive/responsive.js'
import { clearSreen } from './events/clearScreen.js'
import {getProfileData, showUserProfile, showHome} from './views/userdashboard.js'

import {getFollowers, getFollowing} from './views/followView.js' 

window.onload = function () {
    var token = {
        token: getToken()
    }

    if (token != null) {
        getProfileData(token);
    } else {
        window.location.href = "/pages/login.html";
    }

    // addUser('Bc39');
    // addUser('LasCapone');
    // addUser('some');
};

setUpMenu();

const searchbutton = document.getElementById('search-btn');
searchbutton.addEventListener('click', searchUserProfile);

const homeDiv = document.querySelector('.option1');
homeDiv.addEventListener('click', showHome);

const ProfileDiv = document.querySelector('.option2');
ProfileDiv.addEventListener('click', function() {
    clearSreen();
    showUserProfile();
});

const followBtn = document.querySelector('.follow-btn');
followBtn.addEventListener('click', followUser);


