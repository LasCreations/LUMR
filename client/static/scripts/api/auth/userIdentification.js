
import { createSignUpForm } from '../../components/authForm.js'

export function authenticate(){
    fetch('/user/authenticate').then(res => {
        if (res.ok) {
            //get json object and encode it
            window.location.href = "/secure/dashboard.html";
        } else {
            createSignUpForm(); // Call your function when the DOM is fully loaded
        }
    }).then(data => {
        
    }).catch(error => {
        console.error("Error:", error.message);
    });
}