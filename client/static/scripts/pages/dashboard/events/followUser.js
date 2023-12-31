export function getToken() {
    if (/\S/.test(document.cookie)) {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = cookies[i].trim();
            if (cookie.startsWith("Token=")) {
                var token = cookie.substring("Token=".length);
                console.log(token);
                return token;
            }
        }
    }
    return null;
}

export function followUser(){
    var followRequest = {
        username: document.querySelector(".username").textContent,
        token: getToken()
    };
    sendFollowRequest(followRequest);
}

export function sendFollowRequest(followRequest) {
    fetch("/user/follow", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(followRequest),
    }).then(res => {
        if (res.ok) {
            console.log("Request Successful");

            const followBtn = document.querySelector(".follow-btn");
            const followerCount = document.querySelector(".follower-count");

            var count = parseInt(followerCount.textContent) + 1;
            followerCount.textContent = count;
            followBtn.textContent = 'Following';

        } else {
            console.log("Request not successful");
            throw new Error('Network response was not ok');
        }
    }).catch(error => {
        console.error("Error:", error.message);
    });
}