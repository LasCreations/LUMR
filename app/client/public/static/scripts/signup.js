document.getElementById("myForm").addEventListener("submit", function(event) {
    event.preventDefault();

    // Get form data
    var formData = {
        username: document.getElementById("username").value,
        email: document.getElementById("email").value,
        password: document.getElementById("password").value
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
            alert("User added");
            window.location.href = "/dashboard.html";
        }else{
            alert("User couldnt be added");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});