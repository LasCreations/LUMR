
const userProfileViewContainer = document.createElement('div');

const avatarContainer  = document.createElement('div');
const rankContainer  = document.createElement('div');
const usernameContainer  = document.createElement('div');
const nameContainer  = document.createElement('div');
const institutionContainer  = document.createElement('div');
const coursesContainer  = document.createElement('div');
const degreeContainer  = document.createElement('div');


const profileTopLevelContainer  = document.createElement('div');
const profileNameContainer  = document.createElement('div');


const profileTopHolder  = document.createElement('div');
const bottomTopHolder  = document.createElement('div');

const usernameHeading = document.createElement('h1');
const nameHeading = document.createElement('h1');
const institutionHeading = document.createElement('small');
const rankHeading = document.createElement('h1');

const avatar = document.createElement('img');

const container = document.getElementById('container');

//firstname, lastname, username, password,  avatar, institutionName, 
//rank, degrees = [], courses = [], yearStart, yearEnd
export function createUserProfile(user){
    setID();
    addDataToComponents(user);

    appendToParentDiv();

    container.appendChild(userProfileViewContainer);
}

function setID() {
    userProfileViewContainer.id = 'userProfileViewContainer';

    avatarContainer.id = 'avatarContainer';
    rankContainer.id = 'rankContainer';
    usernameContainer.id = 'usernameContainer';
    nameContainer.id = 'nameContainer';
    institutionContainer.id = 'institutionContainer';
    coursesContainer.id = 'coursesContainer';
    degreeContainer.id = 'degreeContainer';

    profileTopLevelContainer.id = 'profileTopLevelContainer';
    profileNameContainer.id = 'profileNameContainer';

    profileTopHolder.id = 'profileTopHolder';
    bottomTopHolder.id = 'bottomTopHolder';

    nameHeading.className = 'nameHeading';
    avatar.id = 'avatar';
}

function addDataToComponents(user){

    nameHeading.textContent = user.firstname + " " + user.lastname;
    nameContainer.appendChild(nameHeading);

    usernameHeading.textContent = "@" + user.username;
    usernameContainer.appendChild(usernameHeading);

    rankHeading.textContent = "Rank: " + user.rank;
    rankContainer.appendChild(rankHeading);

    institutionHeading.textContent = user.institutionName + " " + user.yearStart + " - " + user.yearEnd;
    institutionContainer.appendChild(institutionHeading);

   

    user.courses.forEach(function (course) {
        const courseDiv = document.createElement('div');
        courseDiv.className = 'courseDiv';
        courseDiv.textContent = course.name;
        coursesContainer.appendChild(courseDiv);
    });


    user.degrees.forEach(function (degree) {
        const degreeDiv = document.createElement('div');
        degreeDiv.className = 'degreeDiv';
        degreeDiv.textContent = degree.name;
        degreeContainer.appendChild(degreeDiv);
    });

    avatar.src = '/avatars/' + user.avatar + ".jpg";
    
    avatarContainer.appendChild(avatar);
}

function appendToParentDiv(){

    profileNameContainer.appendChild(nameContainer);
    profileNameContainer.appendChild(usernameContainer);

    profileTopLevelContainer.appendChild(avatarContainer);
    profileTopLevelContainer.appendChild(profileNameContainer);


    // userProfileViewContainer.appendChild(profileTopLevelContainer);


    // userProfileViewContainer.appendChild(usernameContainer);
    // userProfileViewContainer.appendChild(rankContainer);
    // userProfileViewContainer.appendChild(institutionContainer);
    // userProfileViewContainer.appendChild(degreeContainer);
    // userProfileViewContainer.appendChild(coursesContainer);

    // userProfileViewContainer.appendChild(rankContainer);
    profileTopHolder.append(profileTopLevelContainer);
    profileTopHolder.append(rankContainer);

    bottomTopHolder.appendChild(institutionContainer);
    bottomTopHolder.appendChild(degreeContainer);
    bottomTopHolder.appendChild(coursesContainer);

    userProfileViewContainer.appendChild(profileTopHolder);
    userProfileViewContainer.appendChild(bottomTopHolder);
}