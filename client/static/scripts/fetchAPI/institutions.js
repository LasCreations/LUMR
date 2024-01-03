export function getInstitutions(institutionSelect) {
    fetch('/institutions').then(res => {
        if (res.ok) {
            console.log("Institutions Data recieved");
            return res.json();
        } else {
            console.log("Institutions Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        data.forEach(function (currentObject) {
            const option = document.createElement('option');
            option.value = currentObject.name;
            option.text = currentObject.name;
            institutionSelect.appendChild(option);
        });
    }).catch(error => {
        console.error("Error:", error.message);
    });
}

export function getDegrees(institution ,degreeSelect) {  
    fetch("/degree", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({name: institution}),
    }).then(res => {
        if (res.ok) {
            console.log("Degree Data recieved");
            return res.json(); 
        } else {
            console.log("Degree Data not recieved");
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        degreeSelect.innerHTML = ''; //clear seclect
        data.forEach(function (currentObject) {
            const option = document.createElement('option');
            option.value = currentObject.name;
            option.text = currentObject.name;
            degreeSelect.appendChild(option);
        });
    }).catch(error => {
        console.error("Error:", error.message);
    });
}


