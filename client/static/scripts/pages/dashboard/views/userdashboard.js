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

export function getProfileData(token){
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
            window.location.href = '/'
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        console.log(data);
        
        const usernameLarge = document.querySelector(".username");
        const usernameSmall = document.querySelector(".page-title");
        const bioText = document.querySelector(".bio-text");
        const followerCount = document.querySelector(".follower-count");
        const followingCount = document.querySelector(".following-count");

        followerCount.textContent = `${data.followercount}`;
        followingCount.textContent = `${data.followingcount}`;
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

export function fetchAndSetImage(url, elementID) {
    fetch(url)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            return response.blob(); // Convert the response to a Blob
        })
        .then(blob => {
            
            const imageUrl = URL.createObjectURL(blob); // Create a data URL from the Blob

            const imgElement = document.querySelector(elementID);
            
            imgElement.src = imageUrl;
        })
        .catch(error => console.error(`Error fetching image for ${elementId}:`, error));
}

export function showUserProfile(){
    const followBtn = document.querySelector(".follow-btn");
    const messageBtn = document.querySelector(".message-btn");
    const editBtn = document.querySelector(".edit-btn");
    const profileDiv = document.getElementById("profile-view");
    

    
    profileDiv.style.display = "block";
    editBtn.style.display = "block";
    followBtn.style.display = "none";
    messageBtn.style.display = "none";

    var tokenJson = {
        token: getToken()
    }

    getProfileData(tokenJson);
}

export function showHome(){
    const profileDiv = document.getElementById("profile-view");

    profileDiv.style.display = "none";
}