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

function getProfileData(){
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
        fetchAndSetImage(url, "profileImage");
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

window.onload = function () {

    var sessionID = {
        cookie: getSessionID()
    }

    if (sessionID != null) {
        getProfileData();
    } else {
        window.location.href = "/login.html";
    }
};

function searchUser() {
    const usernameContainer = document.getElementById('UsernameContainer');
    var formData = {
        userID: usernameContainer.textContent,
        username: document.getElementById("username").value
    };

    fetch("/api/search/user", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
        .then(res => {
            if (res.ok) {
                console.log("User found");
                return res.json(); // Parse the JSON from the response
            } else {
                console.log("User not found");
                const UserCardContainer = document.getElementById('user-search');
                UserCardContainer.style.display = 'none';
                throw new Error('Network response was not ok');
            }
        }).then(data => {
            console.log(data);

            const usernameContainer = document.getElementById('search-username');
            var button = document.querySelector('.follow-btn');

            usernameContainer.textContent = `${data.username}`;
            var isFriend = data.status;
            var avatar = data.avatarurl;

            if (isFriend) {
                button.textContent = 'Following';
            } else {
                button.textContent = 'Follow';
            }


            var url = "/avatars/" + avatar + ".jpg";
            fetchAndSetImage(url, "searchImage");



            const UserCardContainer = document.getElementById('user-search');
            UserCardContainer.style.padding = '20px';
            UserCardContainer.style.textAlign = 'center';
            UserCardContainer.style.justifyContent = 'center';
            UserCardContainer.style.display = 'flex';
            UserCardContainer.style.flexDirection = 'column';
            UserCardContainer.style.display = 'block';
        })
        .catch(error => {
            console.error("Error:", error.message);
        });
}

function fetchAndSetImage(url, elementID) {
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
            const imgElement = document.getElementById(elementID);
            imgElement.src = imageUrl;

            // Optional: Revoke the object URL to free up resources
            // URL.revokeObjectURL(imageUrl);
        })
        .catch(error => console.error(`Error fetching image for ${elementId}:`, error));
}

function addUser() {
    const requestIDContainer = document.getElementById('search-username');
    const usernameContainer = document.getElementById('UsernameContainer');
    var button = document.querySelector('.follow-btn');


    if (button.textContent === 'Follow') {
        var searchData = {
            userID: usernameContainer.textContent,
            searchID: requestIDContainer.textContent
        };

        fetch("/api/follow/user", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(searchData),
        })
            .then(res => {
                if (res.ok) {
                    console.log("User added");
                    button.textContent = 'Following';
                } else {
                    console.log("User not added");
                    throw new Error('Network response was not ok');
                }
            })
            .catch(error => {
                console.error("Error:", error.message);
            });
    } else {
        button.textContent = 'Following';
    }


}

function Logout() {
    window.location.href = "/login.html";
}