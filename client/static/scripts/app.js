
import { authenticate } from './api/auth/userIdentification.js'


document.addEventListener('DOMContentLoaded', function () {


    //detect the user browser to test compatability
    var userAgent = navigator.userAgent;

    if (userAgent.indexOf("Chrome") !== -1) {

        console.log("This is Google Chrome");
    } else if (userAgent.indexOf("Firefox") !== -1) {

        console.log("This is Mozilla Firefox");
    } else if (userAgent.indexOf("Safari") !== -1) {
        // Code for Safari
        console.log("This is Safari");
    } else if (userAgent.indexOf("MSIE") !== -1 || userAgent.indexOf("Trident/") !== -1) {
        // Code for Internet Explorer
        console.log("This is Internet Explorer");
    } else if (userAgent.indexOf("Edge") !== -1) {
        // Code for Microsoft Edge
        console.log("This is Microsoft Edge");
    } else {
        // Code for other browsers
        console.log("This is some other browser");
    }

    authenticate();

    const starField = document.querySelector(".stars");

    // Function to generate random number within a range
    function randomRange(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    // Function to create a star and append it to the starField
    function createStar() {
        const star = document.createElement("div");
        star.className = "star";
        star.style.left = `${randomRange(0, 120)}vw`;
        star.style.top = `${randomRange(0, 150)}vh`;
        star.style.animationDuration = `${randomRange(2, 4)}s`;
        starField.appendChild(star);
    }

    // Create a certain number of stars
    const numberOfStars = 800;
    for (let i = 0; i < numberOfStars; i++) {
        createStar();
    }
});




