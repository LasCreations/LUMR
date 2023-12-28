export function clearSreen(){
    var profileView = document.getElementById("profile-view");
    var followView = document.querySelector('.follow-view');
    
    profileView.style.display = 'none';
    followView.style.display = 'none';

    var parentElement = document.getElementById('users-container');

    while (parentElement.firstChild) {
        parentElement.removeChild(parentElement.firstChild);
    }
}   