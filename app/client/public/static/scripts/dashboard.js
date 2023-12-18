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
                return res.json(); // Parse the JSON from the response
            } else {
                console.log("User not found");
                throw new Error('Network response was not ok');
            }
        }).then(data => {
            console.log(data);
            const usernameContainer = document.getElementById('UsernameContainer');
            usernameContainer.textContent = `${data.username}`;
            var avatar = data.avatarurl;
            var url = "/avatars/" + avatar + ".jpg";
            fetchAndSetImage(url);
        }).catch(error => {
            console.error("Error:", error.message);
        });
    } else {
        window.location.href = "/login.html";
    }
};

function searchUser() {
    var formData = {
        username: document.getElementById("username").value
    };

    fetch("/friend/search", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
        .then(res => {
            if (res.ok) {
                console.log("User found");
            } else {
                console.log("User not found");
            }
        })
        .catch(error => {
            console.error("Error:", error.message);
        });
}

function fetchAndSetImage(url) {
    fetch(url)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            return response.blob(); // Convert the response to a Blob
        })
        .then(blob => {
            // Create a data URL from the Blob
            const imageUrl = URL.createObjectURL(blob);

            // Set the image source
            const imgElement = document.getElementById("profileImage");
            imgElement.src = imageUrl;

            // Optional: Revoke the object URL to free up resources
            // URL.revokeObjectURL(imageUrl);
        })
        .catch(error => console.error(`Error fetching image for ${elementId}:`, error));
}

function Logout() {
    window.location.href = "/login.html";
}