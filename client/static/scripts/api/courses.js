export function getCourses(degree, institution){
    
    var data = {
        degree : degree,
        institution : institution
    }

    // console.log(data);

    fetch("/courses", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(data),
    }).then(res => {
        if (res.ok) {
            console.log("Courses Data recieved");
            return res.json(); 
        } else {
            console.log("Courses Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        console.log(data);
    }).catch(error => {
        console.error("Error:", error.message);
    });
}