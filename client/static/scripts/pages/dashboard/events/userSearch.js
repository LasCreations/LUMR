function searchUserProfile() {

    var searchFieldValue = document.getElementById("searchField").value;

    if (searchFieldValue === "") {
        console.log("The input field is empty");
    } else {
        var userID = {
            username: searchFieldValue,
            password: "",
            token: getToken()
        };
        getUserProfileData(userID);
    }
}

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

function getUserProfileData(userID) {
    fetch("/user/search", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(userID),
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
        
        const followBtn = document.querySelector(".follow-btn");
        const messageBtn = document.querySelector(".message-btn");
        const editBtn = document.querySelector(".edit-btn");
        const profileDiv = document.getElementById("profile-view");

        profileDiv.style.display = "block";
        editBtn.style.display = "none";


        followBtn.style.display = "block";
        messageBtn.style.display = "block";

        if(data.status == true){
            followBtn.textContent = 'Following';
        }else{
            followBtn.textContent = 'Follow';
        }


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

        // fetchAndSetImage(url, ".profileImage");
        fetchAndSetImage(url, ".profileViewImage");
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

