import { getToken } from "./followUser.js";


let imageContainer, contentContainer, timestampContainer, notificationDiv;
let imageElement;

export function getNotification() {
    fetch("/user/notification", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({token : getToken()}),
    }).then(res => {
        if (res.ok) {
            console.log("Notification Recieved");
            return res.json(); 
        } else {
            throw new Error('Network response was not ok');
        }
    }).then(data => {
        console.log(data);
        addNotificationToView(data);
        // setTimeout(getNotification, 3000);
      }).catch(error => {
        console.error("Error:", error.message);
    }).finally(() => {
        setTimeout(getNotification, 3000);
    });
  }
  

function addNotificationToView(jsonData){
    
    jsonData.forEach(function(currentObject) {
        imageContainer = document.createElement('div');  
    contentContainer = document.createElement('div');  
    timestampContainer = document.createElement('div');  
    notificationDiv = document.createElement('div'); 


    imageContainer.className = 'N-imageContainer';
    contentContainer.className = 'N-contentContainer';
    timestampContainer.className = 'N-timestampContainer';
    notificationDiv.className = 'notification';

    imageElement = document.createElement('img');
    imageElement.className = 'imageElement';

    imageElement.src = "/avatars/" + currentObject.avatarurl +".jpg";
    contentContainer.textContent = currentObject.content;
    timestampContainer.textContent = currentObject.timestamp;
    
    imageContainer.appendChild(imageElement);

    notificationDiv.appendChild(imageContainer);
    notificationDiv.appendChild(contentContainer);
    notificationDiv.appendChild(timestampContainer);

    document.querySelector('.notificationBox').appendChild(notificationDiv);
    });
}