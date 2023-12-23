document.getElementById("loginForm").addEventListener("submit", function(event) {
    event.preventDefault();

    var formData = {
        username: document.getElementById("username").value,
        password: document.getElementById("password").value
    };
    
    fetch("/user/login", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
    .then(res => {
        if(res.ok){
            // console.log("User added");
        }else{
            // console.log("Username already exists use another name");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});