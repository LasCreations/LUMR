window.onload = function () {
    //Authenticated user
    if (getSessionID() !== null) {
        fetch("/user/auth", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
        }).then(res => {
                if (res.ok) {
                    window.location.href = "/dashboard.html"; // Redirect User to the dashboard
                } else {
                    throw new Error('Network response was not ok');
                }
            }).catch(error => {
                console.error("Error:", error.message);
            });

    }
    //Not authenticated user
    else {
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