document.getElementById("myForm").addEventListener("submit", function(event) {
    event.preventDefault();

    // Get form data
    var formData = {
        username: document.getElementById("username").value,
        email: document.getElementById("email").value,
        password: document.getElementById("password").value,
        avatarurl: "irutu"
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
            window.location.href = "/dashboard.html";
        }else{
            console.log("User couldnt be added");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});