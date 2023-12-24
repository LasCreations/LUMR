window.onload = function () {

    var token = {
        token: getToken()
    }

    if (token != null) {
        getProfileData(token);
    } else {
        window.location.href = "/pages/login.html";
    }
};

function getToken() {
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

function getProfileData(token){
    fetch("/user/me", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(token),
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
        // const usernameContainer = document.getElementById('UsernameContainer');
        // usernameContainer.textContent = `${data.username}`;
        // username page-title bio-text

        const usernameLarge = document.querySelector(".username");
        const usernameSmall = document.querySelector(".page-title");
        const bioText = document.querySelector(".bio-text");

        usernameLarge.textContent = `${data.username}`;
        usernameSmall.textContent = `@${data.username}`;
        bioText.textContent = `${data.bio}`;
        var avatar = data.avatarurl;
        var url = "/avatars/" + avatar + ".jpg";
        fetchAndSetImage(url, ".profileImage");
        fetchAndSetImage(url, ".profileViewImage");
    }).catch(error => {
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
            // const imgElement = document.getElementById(elementID);
            const imgElement = document.querySelector(elementID);
            
            imgElement.src = imageUrl;

            // Optional: Revoke the object URL to free up resources
            // URL.revokeObjectURL(imageUrl);
        })
        .catch(error => console.error(`Error fetching image for ${elementId}:`, error));
}

function showUserProfile(){
    const profileDiv = document.getElementById("profile-view");
    profileDiv.style.display = "block";
}