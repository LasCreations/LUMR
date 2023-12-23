function updateButtonVisibility() {
    var checkbox = document.querySelector('.form-check-input');
    var registerButton = document.querySelector('.btn');

    if (checkbox.checked) {
      registerButton.style.display = 'block'; 
    } else {
      registerButton.style.display = 'none'; 
    }
}

document.getElementById("signUpForm").addEventListener("submit", function(event) {
    event.preventDefault();

// function submitform(event){
    event.preventDefault();
    var formData = {
        username: document.getElementById("username").value,
        password: document.getElementById("first-pass").value
    };
    
    fetch("/user/register", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
    .then(res => {
        if(res.ok){
            console.log("User added");
            window.location.href = "/pages/profilesetup.html";
        }else{
            console.log("Username already exists use another name");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});