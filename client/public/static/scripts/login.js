document.getElementById("myForm").addEventListener("submit", function(event) {
    event.preventDefault();

    // Get form data
    var formData = {
        username: document.getElementById("username").value,
        password: document.getElementById("password").value,
    };
    
    fetch("/api/auth/login", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(formData),
    })
    .then(res => {
        if(res.ok){
            // console.log("User added");
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