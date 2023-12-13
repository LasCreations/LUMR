//When you enter the page
window.onload = function() {
    getSessionID()
};

document.getElementById("myForm").addEventListener("submit", function (event) {
    event.preventDefault();

    const formData = new FormData(event.target);

    fetch("/login", {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded",
        },
        body: new URLSearchParams(formData).toString(),
    })
    .then(res => {
        if(res.ok){
            console.log("Successful");
            window.location.href = "/dashboard.html";
        }else{
            alert("User couldnt be added");
            console.log("Not Successful");
        }
    })
    .catch(error => {
        console.error("Error:", error.message);
    });
});


function getSessionID(){
    let cookie = document.cookie;

    // Use a regular expression to check if the cookie contains non-whitespace characters
    if (/\S/.test(cookie)) {
        console.log("Cookie is not empty. Value:", cookie);
        // You can perform additional actions here if the cookie is not empty
        
    } else {
        console.log("Cookie is empty.");
        // You can perform additional actions here if the cookie is empty
        return null; // or return an empty string or any other value indicating no cookie
    }
}