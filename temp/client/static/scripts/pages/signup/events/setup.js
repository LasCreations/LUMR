
export function createAvatarLayout(){
    
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

// document.getElementById("myForm").addEventListener("submit", function(event) {
//     event.preventDefault();

//     var genderElement = document.querySelector('.classic');
//     var genderValue = genderElement.value;

//     // Get form data
//     var formData = {
//         email: document.getElementById("email").value,
//         bio: document.getElementById("bio").value,
//         gender: genderValue,
//         avatarurl: avatar,
//         token: getToken()
//     };
    
//     fetch("/user/profile/create", {
//         method: "POST",
//         headers: {
//             "Content-Type": "application/json",
//         },
//         body: JSON.stringify(formData),
//     })
//     .then(res => {
//         if(res.ok){
//             console.log("Profile added");
//             window.location.href = "/pages/dashboard.html";
//         }else{
//             console.log("Profile couldnt be added");
//         }
//     })
//     .catch(error => {
//         console.error("Error:", error.message);
//     });
// });