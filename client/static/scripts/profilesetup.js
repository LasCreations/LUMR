var avatar = "default";

window.onload = function (){
    fetchAndSetImage('/avatars/avatar1.jpg', 'avatar1');
    fetchAndSetImage('/avatars/avatar2.jpg', 'avatar2');
    fetchAndSetImage('/avatars/avatar3.jpg', 'avatar3');
    fetchAndSetImage('/avatars/avatar4.jpg', 'avatar4');
    fetchAndSetImage('/avatars/avatar5.jpg', 'avatar5');
    fetchAndSetImage('/avatars/avatar6.jpg', 'avatar6');
    fetchAndSetImage('/avatars/avatar7.jpg', 'avatar7');
    fetchAndSetImage('/avatars/avatar8.jpg', 'avatar8');
    fetchAndSetImage('/avatars/avatar9.jpg', 'avatar9');
    fetchAndSetImage('/avatars/avatarA.jpg', 'avatarA');
    fetchAndSetImage('/avatars/avatarB.jpg', 'avatarB');
    fetchAndSetImage('/avatars/avatarC.jpg', 'avatarC');
}

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
    // Show the tick for the selected avatar
    const selectedTick = document.getElementById(`tick${avatarId.charAt(avatarId.length - 1)}`);

    if (selectedTick.style.display === 'block') {
        // If the selected tick is already visible, hide it (toggle off)
        selectedTick.style.display = 'none';
        // Optionally, you may want to reset or clear the selected avatar ID here
        console.log(`Deselected Avatar: ${avatarId}`);
    } else {
        // Reset all ticks
        const allTicks = document.querySelectorAll('.tick');
        allTicks.forEach(tick => tick.style.display = 'none');

        // Show the tick for the selected avatar
        selectedTick.style.display = 'block';

        avatar = avatarId;
        // Store the selected avatar ID or perform any other necessary actions
        console.log(`Selected Avatar: ${avatarId}`);
    }
}

document.getElementById("myForm").addEventListener("submit", function(event) {
    event.preventDefault();

    // Get form data
    var formData = {
        username: document.getElementById("username").value,
        email: document.getElementById("email").value,
        password: document.getElementById("password").value,
        avatarurl: avatar
    };
    
    fetch("/api/auth/register", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
    .then(res => {
        if(res.ok){
            console.log("User added");
            window.location.href = "/dashboard.html";
        }else{
            const errorDiv = document.getElementById('error');
            errorDiv.style.display = 'block';
            errorDiv.style.textAlign = 'center';
            errorDiv.style.alignItems = 'center';
            errorDiv.style.justifyContent = 'center';
            errorDiv.style.display = 'flex';
            console.log("User couldnt be added");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});