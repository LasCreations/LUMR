
import { createSignUpForm } from './components/signupForm.js'


document.addEventListener('DOMContentLoaded', function () {
    if (window.location.href.includes('/pages/signup.html')) {
        createSignUpForm(); // Call your function when the DOM is fully loaded
    } else if (window.location.href.includes('/pages/dashboard.html')) {
        var data = JSON.parse(atob(decodeURIComponent(window.location.search.replace('?data=', ''))));
        console.log(data);  // Outputs: data from signup
    }
});




