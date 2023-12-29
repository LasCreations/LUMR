let imageContainer, contentContainer, timestampContainer, notificationDiv;
let imageElement;


export function ShowNavNotifications() {
    var notificationAlert = document.querySelector('.circle');
    var notificationView = document.querySelector('.notification-container');
    
    if (notificationView.style.display === 'block') {
        notificationView.style.display = 'none';
    } else {
        notificationView.style.display = 'block';
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


        imageContainer.className = 'N-imageContainer';
        contentContainer.className = 'N-contentContainer';
        timestampContainer.className = 'N-timestampContainer';
        notificationDiv.className = 'notification';

        imageElement = document.createElement('img');
        imageElement.className = 'imageElement';

        imageElement.src = "/avatars/" + currentObject.avatarurl + ".jpg";
        contentContainer.textContent = currentObject.content;
        timestampContainer.textContent = currentObject.timestamp;

        imageContainer.appendChild(imageElement);

        notificationDiv.appendChild(imageContainer);
        notificationDiv.appendChild(contentContainer);
        notificationDiv.appendChild(timestampContainer);

        document.querySelector('.notificationBox').appendChild(notificationDiv);
    });
}