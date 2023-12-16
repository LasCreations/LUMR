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

function getSessionID() {
    if (/\S/.test(document.cookie)) {
        return document.cookie;
    } else {
        return null;
    }
}



fetch('/avatars/test.jpg')
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
        const imgElement = document.getElementById('avatar1');
        imgElement.src = imageUrl;

        // Optional: Revoke the object URL to free up resources
        // URL.revokeObjectURL(imageUrl);
    })
    .catch(error => console.error('Error fetching image:', error));





    fetch('/avatars/dog.jpg')
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
        const imgElement = document.getElementById('avatar2');
        imgElement.src = imageUrl;

        // Optional: Revoke the object URL to free up resources
        // URL.revokeObjectURL(imageUrl);
    })
    .catch(error => console.error('Error fetching image:', error));


    fetch('/avatars/cat.png')
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
        const imgElement = document.getElementById('avatar3');
        imgElement.src = imageUrl;

        // Optional: Revoke the object URL to free up resources
        // URL.revokeObjectURL(imageUrl);
    })
    .catch(error => console.error('Error fetching image:', error));

