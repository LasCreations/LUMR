function getSessionID() {
    if (/\S/.test(document.cookie)) {
        return document.cookie;
    } else {
        return null;
    }
}

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
                return res.json(); // Parse the JSON from the response
            } else {
                throw new Error('Network response was not ok');
            }
        })
            .then(data => {
                // Handle the JSON data
                console.log(data);

                // Access the elements where you want to display the specific fields
                const usernameContainer = document.getElementById('UsernameContainer');

                // Update the content of the elements with the specific fields
                usernameContainer.textContent = `${data.username}`;
                var avatar = data.avatarurl;
                var url = "/avatars/" + avatar + ".jpg";
                fetchAndSetImage(url);
            })
            .catch(error => {
                console.error("Error:", error.message);
            });

    }
    //Not authenticated user
    else {
        window.location.href = "/login.html";
        // Value is null, handle accordingly
        alert("User Not Authenticated. Please Login OR SignUp");
        
    }
};


function searchUser(){
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
        if(res.ok){
            console.log("User found");
        }else{
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