let imageContainer, contentContainer, timestampContainer, notificationDiv, senderContainer, tempTimestampContainer;
let imageElement;

import {getUserProfileData} from '../events/userSearch.js'
import { getToken } from './userdashboard.js';


function setOriginalTimestamp(){
    var elements = document.querySelectorAll('.notification');
    elements.forEach(function (element) {
        var timestamp= element.querySelector('.N-timestampContainer');
        var tempTimestamp= element.querySelector('.N-tempTimestampContainer');
        timestamp.textContent = tempTimestamp.textContent;
    });
}

export function ShowNavNotifications() {

    var notificationAlert = document.querySelector('.circle');
    var notificationView = document.querySelector('.notification-container');

    if (notificationView.style.display === 'block') {
        notificationView.style.display = 'none';
        setOriginalTimestamp();    
    } else {
        notificationView.style.display = 'block';

        var elements = document.querySelectorAll('.notification');
        elements.forEach(function (element) {
            var timestamp= element.querySelector('.N-timestampContainer');
            var sender = element.querySelector('.N-senderContainer');

            timestamp.textContent = (Date.now() - Date.parse(timestamp.textContent.replace("\n", "")))/1000 + " seconds ago.";

            element.addEventListener('click', function (event) {
                event.stopPropagation();
                
                var userID = {
                    username: sender.textContent,
                    password: "",
                    token: getToken()
                };
                getUserProfileData(userID);
                console.log('Clicked on element with sender:', sender.textContent);
                notificationView.style.display = 'none';
                setOriginalTimestamp();
            });
        });
    }

    if (notificationAlert.style.display === 'block' || notificationAlert.style.display === '') {
        notificationAlert.style.display = 'none';
    }
}

export function addNotificationToView(jsonData) {
    var notificationAlert = document.querySelector('.circle');
    if (notificationAlert.style.display === 'none') {
        notificationAlert.style.display = 'block';
    }
    jsonData.forEach(function (currentObject) {
        
        imageContainer = document.createElement('div');
        contentContainer = document.createElement('div');
        timestampContainer = document.createElement('div');
        notificationDiv = document.createElement('div');
        senderContainer = document.createElement('div');
        tempTimestampContainer = document.createElement('div');


        imageContainer.className = 'N-imageContainer';
        contentContainer.className = 'N-contentContainer';
        timestampContainer.className = 'N-timestampContainer';
        senderContainer.className = 'N-senderContainer';
        tempTimestampContainer.className = 'N-tempTimestampContainer';

        notificationDiv.className = 'notification';

        imageElement = document.createElement('img');
        imageElement.className = 'imageElement';

        imageElement.src = "/avatars/" + currentObject.avatarurl + ".jpg";
        contentContainer.textContent = currentObject.content;
        senderContainer.textContent = currentObject.senderID;
        
        timestampContainer.textContent = currentObject.timestamp;
        tempTimestampContainer.textContent = currentObject.timestamp;

        senderContainer.style.display = 'none';
        tempTimestampContainer.style.display = 'none';

        imageContainer.appendChild(imageElement);

        notificationDiv.appendChild(senderContainer);
        notificationDiv.appendChild(tempTimestampContainer);
        notificationDiv.appendChild(imageContainer);
        notificationDiv.appendChild(contentContainer);
        notificationDiv.appendChild(timestampContainer);

        var firstChild = document.querySelector('.notificationBox').firstChild;
        document.querySelector('.notificationBox').insertBefore(notificationDiv, firstChild);
        // parentDiv.insertBefore(newElement, firstChild);

        // document.querySelector('.notificationBox').appendChild(notificationDiv);
    });
}



//timestampContainer.textContent = (Date.now() - Date.parse(currentObject.timestamp.replace("\n", "")))/1000 + " seconds ago.";
        //console.log((Date.now() - Date.parse(currentObject.timestamp.replace("\n", "")))/1000);

/**
 const dateString = "Fri Dec 29 22:49:34 2023\n";
const formattedDateString = dateString.replace("\n", "");
const timestamp = Date.parse(formattedDateString);

// Get the current time in milliseconds since the Unix epoch
const currentTime = Date.now();

// Calculate the difference in milliseconds
const timeDifference = timestamp - currentTime;

// Convert the time difference to seconds
const timeDifferenceInSeconds = timeDifference / 1000;

console.log(`Time difference: ${timeDifferenceInSeconds} seconds`);
 */