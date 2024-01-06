
import { createSignUpForm } from './components/signupForm.js'


document.addEventListener('DOMContentLoaded', function () {
    if (window.location.href.includes('/pages/signup.html')) {
        createSignUpForm(); // Call your function when the DOM is fully loaded
    } else if (window.location.href.includes('/pages/dashboard.html')) {
        var data = JSON.parse(atob(decodeURIComponent(window.location.search.replace('?data=', ''))));
        console.log(data);  // Outputs: data from signup
    }else{
        fetch('/user/authenticate').then(res => {
            if (res.ok) {
                
            } else {
               
            }
        }).then(data => {
            
        }).catch(error => {
            console.error("Error:", error.message);
        });
    }
    
    
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
        star.style.animationDuration = `${randomRange(2, 6)}s`;
        starField.appendChild(star);
    }

    // Create a certain number of stars
    const numberOfStars = 700;
    for (let i = 0; i < numberOfStars; i++) {
        createStar();
    }
});




