function getSessionID() {
    if (/\S/.test(document.cookie)) {
        return document.cookie;
    } else {
        return null;
    }
}

window.onload = function () {
    fetchAndSetImage('/avatars/test.jpg', 'avatar1');
    fetchAndSetImage('/avatars/dog.jpg', 'avatar2');
    fetchAndSetImage('/avatars/cat.png', 'avatar3');

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
                const emailContainer = document.getElementById('EmailContainer');
                const passwordContainer = document.getElementById('PasswordContainer');
                const usernameContainer = document.getElementById('UsernameContainer');

                // Update the content of the elements with the specific fields
                emailContainer.textContent = `Email: ${data.email}`;
                passwordContainer.textContent = `Password: ${data.password}`;
                usernameContainer.textContent = `Username: ${data.username}`;

            })
            .catch(error => {
                console.error("Error:", error.message);
            });

    }
    //Not authenticated user
    else {
        // Value is null, handle accordingly
        console.log("No session ID available.");
    }
};

function fetchAndSetImage(url, elementId) {
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
            const imgElement = document.getElementById(elementId);
            imgElement.src = imageUrl;

            // Optional: Revoke the object URL to free up resources
            // URL.revokeObjectURL(imageUrl);
        })
        .catch(error => console.error(`Error fetching image for ${elementId}:`, error));
}

function selectAvatar(avatarId) {
    // Reset all ticks
    const allTicks = document.querySelectorAll('.tick');
    // allTicks.forEach(tick => tick.style.display = 'none');

    // Show the tick for the selected avatar
    // const selectedTick = document.getElementById(`tick${avatarId.charAt(avatarId.length - 1)}`);
    // selectedTick.style.display = 'block';

    // Store the selected avatar ID or perform any other necessary actions
    console.log(`Selected Avatar: ${avatarId}`);
}