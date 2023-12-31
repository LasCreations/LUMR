export function clearSreen(){
    var profileView = document.getElementById("profile-view");
    var followView = document.querySelector('.follow-view');
    var notificationView = document.querySelector('.notification-container');
    var notificationAlert = document.querySelector('.circle');
    
    profileView.style.display = 'none';
    followView.style.display = 'none';
    notificationView.style.display = 'none';
    notificationAlert.style.display = 'none';


    var parentElement = document.getElementById('users-container');

    while (parentElement.firstChild) {
        parentElement.removeChild(parentElement.firstChild);
    }
}   