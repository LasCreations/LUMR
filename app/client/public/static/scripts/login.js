window.onload = function () {
    if (getSessionID() !== null) {
        // Value is not null, so do something with it
        // console.log("Session ID : ", getSessionID());

        fetch("/auth/user", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
                "Authorization": getSessionID(), // Add the session ID to the Authorization header
            },
        })
        .then(res => {
            if(res.ok){

            }else{

            }
        })
        .catch(error => {
            console.error("Error:", error.message);
        });

    } else {
        // Value is null, handle accordingly
        console.log("No session ID available.");
    }
};


function getSessionID() {
    if (/\S/.test(document.cookie)) {
        return document.cookie;
    } else {
        return null;
    }
}