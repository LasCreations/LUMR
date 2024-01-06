import User from '../modules/user.js'
import { getInstitutions } from '../api/institutions.js';
import { getDegrees } from '../api/degrees.js';
import { getCourses } from '../api/courses.js';
import { registerUser } from '../api/auth/signupUser.js'


//Div Containers
const degreeDivContainer = document.createElement('div');
const courseDivContainer = document.createElement('div');
const inputDivContainer = document.createElement('div');
const yearDivContainer = document.createElement('div');

//Form
const form = document.createElement('form');

//Headers
const degreeHeading = document.createElement('h1');
const courseHeading = document.createElement('h1');

//Label
const termLabel = document.createElement('label');
const loginLabel = document.createElement('label');

//Links
const termLink = document.createElement('a');
const loginLink = document.createElement('a');

//Inputs
const usernameInput = document.createElement('input');
const passwordInput = document.createElement('input');
const confirmPasswordInput = document.createElement('input');
const firstnameInput = document.createElement('input');
const lastnameInput = document.createElement('input');

//Inputs
const institutionSelect = document.createElement('select');
const yearStartSelect = document.createElement('select');
const yearEndSelect = document.createElement('select');

//Buttons
const submitButton = document.createElement('button');

const signUpFormContainer = document.getElementById('signUpForm-container');

//Storage Arrays
let selectedDegrees = [];
let selectedCourses = [];
let currentCourses = [];

// Store the current year
var currentYear = new Date().getFullYear(); 

export function createSignUpForm() {
    setID();
    setType();
    setName();
    setPlaceHolders();
    setTextContext();
    hideContent();
    configureInstitutionOptionValues();
    configureYearStartOptionValues();
    configureYearEndOptionValues();
    addActionListeners();
    appendChildToForm();

    signUpFormContainer.appendChild(form);
}

function setID() {
    form.id = 'signupForm';

    usernameInput.id = 'username';
    passwordInput.id = 'password';
    confirmPasswordInput.id = 'confirmPassword';
    firstnameInput.id = 'firstname';
    lastnameInput.id = 'lastname';

    institutionSelect.id = 'institutionSelect';
    yearStartSelect.id = 'yearStartSelect';
    yearEndSelect.id = 'yearEndSelect';

    institutionSelect.className = 'classic';
    yearStartSelect.className = 'classic';
    yearEndSelect.className = 'classic';

    submitButton.id = 'submit-btn'

    degreeDivContainer.id = 'degreeContainer';
    courseDivContainer.id = 'courseContainer';
    inputDivContainer.id = 'inputDivContainer';
    yearDivContainer.id = 'yearDivContainer';
}

function setTextContext() {
    termLabel.innerHTML = 'I agree all statements in ';
    loginLabel.innerHTML = 'Already have an account? ';

    termLink.href = '#!';
    termLink.innerHTML = 'Terms of service';

    loginLink.href = '/';
    loginLink.innerHTML = 'Login now';

    degreeHeading.textContent = 'Select Degree/s';
    courseHeading.textContent = 'Select Course/s';
    submitButton.textContent = 'Signup';

}

function setPlaceHolders(){
    usernameInput.placeholder = 'Username';
    firstnameInput.placeholder = 'First Name';
    lastnameInput.placeholder = 'Last Name';
    passwordInput.placeholder = 'Password';
    confirmPasswordInput.placeholder = 'Confirm Password';
}

function setType() {
    form.enctype = 'multipart/form-data';
    usernameInput.type = 'text';
    usernameInput.setAttribute('required', '');    //turns required on
    firstnameInput.type = 'text';
    lastnameInput.type = 'text';
    passwordInput.type = 'password';
    passwordInput.setAttribute('required', '');    //turns required on
    confirmPasswordInput.type = 'password';
    confirmPasswordInput.setAttribute('required', '');    //turns required on
    submitButton.type = 'submit';
}

function setName() {
    usernameInput.name = 'username';
    passwordInput.name = 'password';
    firstnameInput.name = 'firstname';
    lastnameInput.name = 'lastname';
    confirmPasswordInput.name = 'confirmPassword';
    institutionSelect.name = 'institutionSelect';
    yearEndSelect.name = 'yearEndSelect';
    yearStartSelect.name = 'yearStartSelect';
}

function hideContent(){
    degreeHeading.style.display = 'none';
    courseHeading.style.display = 'none';
}

function configureInstitutionOptionValues() {
    const option = document.createElement('option');
    option.value = "University/College";
    option.text = "University/College";
    institutionSelect.appendChild(option);
    getInstitutions(institutionSelect);
}

function configureYearStartOptionValues() {
    const option = document.createElement('option');
    option.value = "Start Year";
    option.text = "Start Year";
    yearStartSelect.appendChild(option);
    /* Populate the first select with 10 years prior to the current year */
    populateYearSelect('yearStartSelect', currentYear - 10, currentYear, yearStartSelect);
}

function configureYearEndOptionValues() {
    const option = document.createElement('option');
    option.value = "Year End (Expected)";
    option.text = "Year End (Expected)";
    yearEndSelect.appendChild(option);
    /* Populate the second select with 10 years from the current year */
    populateYearSelect('yearEndSelect', currentYear, currentYear + 10, yearEndSelect);
}

function populateYearSelect(selectId, startYear, endYear, select) {
    var selectElement = document.getElementById(selectId);
    for (var year = startYear; year <= endYear; year++) {
        var option = document.createElement('option');
        option.value = year;
        option.text = year;
        select.appendChild(option);
    }
}

function addActionListeners() {
    institutionSelect.addEventListener('change', function () {
        selectedDegrees = []; //clear selected array
        getDegrees(institutionSelect.value)
    });

    form.addEventListener('submit', function (event) {
        event.preventDefault(); // Prevent the default form submission
        handleSignUp();
    });
}

function appendChildToForm() {


    inputDivContainer.appendChild(usernameInput);
    inputDivContainer.appendChild(firstnameInput);
    inputDivContainer.appendChild(lastnameInput);
    inputDivContainer.appendChild(passwordInput);
    inputDivContainer.appendChild(confirmPasswordInput);
    form.appendChild(inputDivContainer);
    
    form.appendChild(institutionSelect);

    yearDivContainer.appendChild(yearStartSelect);
    yearDivContainer.appendChild(yearEndSelect);
    form.appendChild(yearDivContainer);

    form.appendChild(degreeHeading);
    form.appendChild(degreeDivContainer);
    form.appendChild(courseHeading);
    form.appendChild(courseDivContainer);

    termLabel.appendChild(termLink);

    form.appendChild(termLabel);


    form.appendChild(submitButton);

    loginLabel.appendChild(loginLink);
    form.appendChild(loginLabel);
}

export function addDegreesToADiv(degreeJson) {
    degreeHeading.style.display = 'block';
    degreeDivContainer.innerHTML = ''; //clear div
    selectedDegrees = []; //clear selected array
    // console.log(degreeJson);
    degreeJson.forEach(function (currentObject) {
        const degreeDiv = document.createElement('div');
        degreeDiv.className = 'degreeDiv';
        degreeDiv.textContent = currentObject.name;
        degreeDivContainer.appendChild(degreeDiv);
    });

    var elements = document.querySelectorAll('.degreeDiv');
    elements.forEach(function (element) {
        element.addEventListener('click', function () {
            element.classList.toggle('degree-selected');
            const textContent = element.textContent;

            const index = selectedDegrees.indexOf(textContent); // Check if the text is already in the array

            if (index === -1) {
                selectedDegrees.push(textContent); // If not in the array, add it
            } else {
                selectedDegrees.splice(index, 1); // If already in the array, remove it
            }
            console.clear();
            for (let i = 0; i < selectedDegrees.length; i++) {
                getCourses(selectedDegrees[i], institutionSelect.value); //get courses from current selected degrees
            }
        });
    });
}

export function addCoursesToADiv(courseJson) {
    courseHeading.style.display = 'block';
    selectedCourses = []; //clear selected array
    courseJson.forEach(function (currentObject) {
        const index = currentCourses.indexOf(currentObject.course); // Check if the text is already in the array
        if(index === -1){  //not in array
            const courseDiv = document.createElement('div');
            courseDiv.className = 'courseDiv';
            courseDiv.textContent = currentObject.course;
            currentCourses.push(currentObject.course);
            courseDivContainer.appendChild(courseDiv);
        }
    });

    var elements = document.querySelectorAll('.courseDiv');
    elements.forEach(function (element) {
        element.addEventListener('click', function () {
            element.classList.toggle('course-selected');
            const textContent = element.textContent;
            const index = selectedCourses.indexOf(textContent); // Check if the text is already in the array
            if (index === -1) {
                selectedCourses.push(textContent); // If not in the array, add it
            } else {
                selectedCourses.splice(index, 1); // If already in the array, remove it
            }
        });
    });
}

function handleSignUp() {
    const username = document.getElementById('username').value;
    const firstname = document.getElementById('firstname').value;
    const lastname = document.getElementById('lastname').value;
    const password = document.getElementById('password').value;
    const passwordConfirm = document.getElementById('confirmPassword').value;

    if (password == passwordConfirm) {
        const user = new User(firstname, lastname, username, password, "default", institutionSelect.value, 0, selectedDegrees, selectedCourses, yearStartSelect.value, yearEndSelect.value);
        console.log(user);
        registerUser(user);
    } else {
        alert("password does not match");
    }
}