function getSessionID() {
    if (/\S/.test(document.cookie)) {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = cookies[i].trim();
            if (cookie.startsWith("sessionID=")) {
                var sessionId = cookie.substring("sessionID=".length);
                console.log(sessionId);
                return sessionId;
            }
        }
    }
    return null;
}

window.onload = function () {

    var sessionID = {
        cookie: getSessionID()
    }

    if (sessionID != null) {
        fetch("/api/users/me", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(sessionID),
        }).then(res => {
            if (res.ok) {
                console.log("User found");
                window.location.href = "/dashboard.html";
            } else {
                console.log("User not found");
            }
        }).catch(error => {
            console.error("Error:", error.message);
        });
    } else {
        
    }
};