import { getToken } from "../dashboard/events/followUser.js";

window.onload = function () {
    if (getToken() != null) {
        isAuthenticated();
    }
};

document.getElementById("loginForm").addEventListener("submit", function(event) {
    event.preventDefault();

    var formData = {
        username: document.getElementById("username").value,
        password: document.getElementById("password").value
    };
    
    fetch("/user/login", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
    .then(res => {
        if(res.ok){
            window.location.href = "/pages/dashboard.html";
        }else{
            alert("Incorrect Password Or Username ... Please Try Again");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});

function isAuthenticated(){
    fetch("/user/me", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({token: getToken()}),
    }).then(res => {
        if (res.ok) {
            window.location.href = "/pages/dashboard.html"; 
        }
    }).catch(error => {
        console.error("Error:", error.message);
    });
}