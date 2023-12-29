let imageContainer, contentContainer, timestampContainer, notificationDiv;
let imageElement;

export function ShowNavNotifications(){
    var notificationView = document.querySelector('.notification-container');
    if (notificationView.style.display === 'block') {
        notificationView.style.display = 'none';
    } else {
        notificationView.style.display = 'block';
    }
}

// export function addNotificationToView(jsonData){
//     imageContainer = document.createElement('div');  
//     contentContainer = document.createElement('div');  
//     timestampContainer = document.createElement('div');  
//     notificationDiv = document.createElement('div'); 


//     imageContainer.className = 'N-imageContainer';
//     contentContainer.className = 'N-contentContainer';
//     timestampContainer.className = 'N-timestampContainer';
//     notificationDiv.className = 'notification';

//     imageElement = document.createElement('img');
//     imageElement.className = 'imageElement';

//     imageElement.src = "/avatars/" + jsonData.avatarurl +".jpg";
//     contentContainer.textContent = `${jsonData.content}`;
//     timestampContainer.textContent = `${jsonData.timestamp}`;
    
//     imageContainer.appendChild(imageElement);

//     notificationDiv.appendChild(imageContainer);
//     notificationDiv.appendChild(contentContainer);
//     notificationDiv.appendChild(timestampContainer);

//     document.querySelector('.notificationBox').appendChild(notificationDiv);
// }

// var userDiv = document.createElement('div'); //main div container

//     var imageContainer = document.createElement('div');  //Container to hold image
//     var usernameContainer = document.createElement('div');  //container to hold username
//     var btnContainer = document.createElement('div'); //container to hold the btn to show Unfollow


//     //assigning class names to div
//     userDiv.className = 'user';
//     imageContainer.className = 'F-imageContainer';
//     usernameContainer.className = 'F-usernameContainer';
//     btnContainer.className = 'F-btnContainer'

//     //creating image element
//     var imageElement = document.createElement('img');
//     //creating button element
//     var buttonElement = document.createElement('button');

//     
//     buttonElement.className = 'buttonElement';

//     if (status == true) {
//         buttonElement.textContent = 'Following'
//     } else {
//         buttonElement.textContent = 'Follow'
//     }
//     imageElement.src = src;
//     usernameContainer.textContent = username;



//     imageContainer.appendChild(imageElement);
//     btnContainer.appendChild(buttonElement);

//     userDiv.appendChild(imageContainer);
//     userDiv.appendChild(usernameContainer);
//     userDiv.appendChild(btnContainer);

//     document.getElementById('users-container').appendChild(userDiv);