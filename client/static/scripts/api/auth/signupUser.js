//Sends user data to server


export function registerUser(user){
    fetch("/register/user", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(user),
    }).then(res => {
        if (res.ok) {
            //encode to base 64
            var base64EncodedString = btoa(JSON.stringify(user));
            //use encodeURIComponent to make it url safe
            var urlSafeBase64 = encodeURIComponent(base64EncodedString);
            
            window.location.href = '/secure/dashboard.html?data=' + urlSafeBase64;
        } else {
            console.log("Error registering");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
       
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

