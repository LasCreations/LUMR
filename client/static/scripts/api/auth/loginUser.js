//Sends user data to server

export function loginUser(username, password) {

    var authData = {
        username: username,
        password: password
    };

    fetch("/user/authenticate/login", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(authData),
    }).then(res => {
        if (res.ok) {
            window.location.href = '/secure/dashboard.html';
        } else {
            console.log("Error logging in");
            throw new Error('Network response was not ok');
        }
    }).catch(error => {
        console.error("Error:", error.message);
    });
}