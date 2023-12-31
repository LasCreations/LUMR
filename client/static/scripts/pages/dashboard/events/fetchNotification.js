import { getToken } from "./followUser.js";
import {addNotificationToView} from '../views/notificationView.js'

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
  

