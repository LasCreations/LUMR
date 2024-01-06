import { createSignUpForm } from '../../components/authForm.js'

export function authenticate(){
    fetch('/user/authenticate').then(res => {
        if (res.ok) {
            if (window.location.href.includes('/secure/dashboard.html')) {
                var data = JSON.parse(atob(decodeURIComponent(window.location.search.replace('?data=', ''))));
                console.log(data);  // Outputs: data from signup
            }else{
                //encode data and then redirect
                window.location.href = "/secure/dashboard.html";
            }
        } else {
            if (!window.location.href.includes('/secure/dashboard.html')) {
                createSignUpForm();
            }else{
                window.location.href = "/";
                createSignUpForm();
            }
        }
    }).then(data => {
        
    }).catch(error => {
        console.error("Error:", error.message);
    });
}