var username = "";
var password = "";
var confirmPassword = "";
var email = "";
var bio = "";
var avatar = "default";

export function updateButtonVisibility() {
    var checkbox = document.querySelector('.form-check-input');
    var registerButton = document.querySelector('.register-btn');

    if (checkbox.checked) {
        registerButton.disabled = false; 
    } else {
        registerButton.disabled = true;
    }
}

export function selectAvatar(avatarId) {
    
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

         
        selectedTick.style.display = 'block';  // Show the tick for the selected avatar

        avatar = avatarId;
        console.log(`Selected Avatar: ${avatarId}`);
    }
}

export function registerUser(){
    const formPassword = document.getElementById("password").value;
    const formConfirmPassword = document.getElementById("confirmPassword").value;
    if( formPassword == formConfirmPassword ){
        var userInformation = {
            avatar: avatar,
            password: formPassword,
            email: document.getElementById("email").value,
            bio: document.getElementById("bio").value,
            username: document.getElementById("username").value,
            gender: document.querySelector('.classic').value
        };
        console.log(JSON.stringify(userInformation));
    }else{
        alert("passwords dont match");
    }
}

// document.getElementById("signUpForm").addEventListener("submit", function(event) {
//     event.preventDefault();

//     var formData = {
//         username: document.getElementById("username").value,
//         password: document.getElementById("first-pass").value
//     };
    
//     fetch("/user/register", {
//         method: "POST",
//         headers: {
//             "Content-Type": "application/json",
//         },
//         body: JSON.stringify(formData),
//     })
//     .then(res => {
//         if(res.ok){
//             console.log("User added");

//             var signupContainer = document.querySelector('.container');
//             var setupContainer = document.querySelector('.setup-container');

//             signupContainer.style.display = 'none';
//             setupContainer.style.display = 'block';
//         }else{
//             console.log("Username already exists use another name");
//         }
//     })
//     .catch(error => {
//         console.error("Error:", error.message);
//     });
// });

