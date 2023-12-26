import {updateButtonVisibility, selectAvatar, registerUser} from './events/registerUser.js'
import {createAvatarLayout} from './events/setup.js'


window.onload = function () {
    createAvatarLayout();
};



const checkBox = document.querySelector('.form-check-input');
checkBox.addEventListener('change',updateButtonVisibility);


document.getElementById("signUpForm").addEventListener("submit", function(event) {
    event.preventDefault();
    registerUser();
});  


const avatar1 = document.querySelector('.avatar1');
const avatar2 = document.querySelector('.avatar2');
const avatar3 = document.querySelector('.avatar3');
const avatar4 = document.querySelector('.avatar4');
const avatar5 = document.querySelector('.avatar5');
const avatar6 = document.querySelector('.avatar6');
const avatar7 = document.querySelector('.avatar7');
const avatar8 = document.querySelector('.avatar8');
const avatar9 = document.querySelector('.avatar9');
const avatarA = document.querySelector('.avatarA');
const avatarB = document.querySelector('.avatarB');
const avatarC = document.querySelector('.avatarC');

avatar1.addEventListener('click', function() {
    selectAvatar("avatar1");
});

avatar2.addEventListener('click', function() {
    selectAvatar("avatar2");
});

avatar3.addEventListener('click', function() {
    selectAvatar("avatar3");
});

avatar4.addEventListener('click', function() {
    selectAvatar("avatar4");
});

avatar5.addEventListener('click', function() {
    selectAvatar("avatar5");
});

avatar6.addEventListener('click', function() {
    selectAvatar("avatar6");
});

avatar7.addEventListener('click', function() {
    selectAvatar("avatar7");
});

avatar8.addEventListener('click', function() {
    selectAvatar("avatar8");
});

avatar9.addEventListener('click', function() {
    selectAvatar("avatar9");
});

avatarA.addEventListener('click', function() {
    selectAvatar("avatarA");
});

avatarB.addEventListener('click', function() {
    selectAvatar("avatarB");
});

avatarC.addEventListener('click', function() {
    selectAvatar("avatarC");
});


