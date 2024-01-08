import { createSignUpForm } from '../../components/authForm.js'
import {decoder} from '../../dashboard/dashboard-manager.js'

export function dashboardAuthenticate() {
    fetch('/user/authenticate').then(res => {
        if (res.ok) {
            return res.json();
        }else{
            window.location.href = '/';
            return Promise.reject('Authentication failed');
        }
    }).then(data => {
        //encode to base 64
        var base64EncodedString = btoa(JSON.stringify(data));
        //use encodeURIComponent to make it url safe
        var urlSafeBase64 = encodeURIComponent(base64EncodedString);
        history.replaceState(null, null, '/secure/dashboard.html?data=' + urlSafeBase64);
        decoder();
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

export function siteEntryAuthenticate(){
    fetch('/user/authenticate').then(res => {
        if (res.ok) {
            return res.json();
        }else{
            createSignUpForm();
            return Promise.reject('Authentication failed');
        }
    }).then(data => {
        //encode to base 64
        var base64EncodedString = btoa(JSON.stringify(data));
        //use encodeURIComponent to make it url safe
        var urlSafeBase64 = encodeURIComponent(base64EncodedString);
        window.location.href = '/secure/dashboard.html?data=' + urlSafeBase64;
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

// fetch('/user/authenticate').then(res => {
//     if (res.ok) {
//         return res.json();
//     }
//     else {
//         // if (!window.location.href.includes('/secure/dashboard.html')) {
//         //     createSignUpForm();
//         // } else {
//         //     window.location.href = "/";
//         //     createSignUpForm();
//         // }
//         // return Promise.reject('Authentication failed');
//     }
//      // Return a rejected promise to skip the next 'then' block
// }).then(data => {
//     //encode to base 64
//     var base64EncodedString = btoa(JSON.stringify(data));
//     //use encodeURIComponent to make it url safe
//     var urlSafeBase64 = encodeURIComponent(base64EncodedString);

//     if (window.location.href.includes('/secure/dashboard.html')) {
//         //changes the url to a current state
//         history.pushState(null, null, '/secure/dashboard.html?data=' + urlSafeBase64);
//     } else {
//         window.location.href = '/secure/dashboard.html?data=' + urlSafeBase64;
//     }
//     // console.log(data);
// }).catch(error => {
//     console.error("Error:", error.message);
// });