import User from '../modules/user.js'
import { getInstitutions } from '../api/institutions.js';
import { getDegrees } from '../api/degrees.js';
import {getCourses} from '../api/courses.js';
import {registerUser} from '../api/auth/signupUser.js'

const degreeDivContainer = document.createElement('div');
const courseDivContainer = document.createElement('div');

const form = document.createElement('form');

const passwordLabel = document.createElement('label');
const usernameLabel = document.createElement('label');
const institutionsLabel = document.createElement('label');
const degreeLabel = document.createElement('label');
const yearStartLabel = document.createElement('label');
const yearEndLabel = document.createElement('label');
const firstnameLabel = document.createElement('label');
const lastnameLabel = document.createElement('label');
const confirmPasswordLabel = document.createElement('label');

const usernameInput = document.createElement('input');
const passwordInput = document.createElement('input');
const confirmPasswordInput = document.createElement('input');
const firstnameInput = document.createElement('input');
const lastnameInput = document.createElement('input');

const institutionSelect = document.createElement('select');
const yearStartSelect = document.createElement('select');
const yearEndSelect = document.createElement('select');

const submitButton = document.createElement('button');

let selectedDegrees = [];

var currentYear = new Date().getFullYear(); // Store the current year

export function createSignUpForm() {
    setID();
    setType();
    setName();
    setLabelFor();
    setTextContext();
    configureInstitutionOptionValues();
    configureYearStartOptionValues();
    configureYearEndOptionValues();
    addActionListeners();
    appendChildToForm();

    document.getElementById('signUpForm-container').appendChild(form);
    document.getElementById('signUpForm-container').appendChild(degreeLabel);
    document.getElementById('signUpForm-container').appendChild(degreeDivContainer);
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
    degreeDivContainer.id = 'degreeContainer';
    courseDivContainer.id = 'courseDivContainer';
}

function setTextContext() {
    usernameLabel.textContent = 'Username:';
    passwordLabel.textContent = 'Password:';
    institutionsLabel.textContent = 'College/University';
    degreeLabel.textContent = 'Select Degree/s';
    yearStartLabel.textContent = 'Start Year';
    yearEndLabel.textContent = 'End year (or expected)';
    firstnameLabel.textContent = 'First Name';
    lastnameLabel.textContent = 'Last Name';
    confirmPasswordLabel.textContent = 'Confirm Password';
    submitButton.textContent = 'Signup';
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

function setLabelFor() {
    yearStartLabel.for = 'yearStartSelect';
    yearEndLabel.for = 'yearEndSelect';
    firstnameLabel.for = 'firstname';
    lastnameLabel.for = 'lastname';
    confirmPasswordLabel.for = 'confirmPassword';
    passwordLabel.for = 'password';
    usernameLabel.for = 'username';
    institutionsLabel.for = 'institutionSelect';
}

function configureInstitutionOptionValues() {
    const option = document.createElement('option');
    option.value = " ";
    option.text = " ";
    institutionSelect.appendChild(option);
    getInstitutions(institutionSelect);
}

function configureYearStartOptionValues() {
    /* Populate the first select with 10 years prior to the current year */
    populateYearSelect('yearStartSelect', currentYear - 10, currentYear, yearStartSelect);
}

function configureYearEndOptionValues() {
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
    form.appendChild(usernameLabel);
    form.appendChild(usernameInput);
    form.appendChild(firstnameLabel);
    form.appendChild(firstnameInput);
    form.appendChild(lastnameLabel);
    form.appendChild(lastnameInput);
    form.appendChild(passwordLabel);
    form.appendChild(passwordInput);
    form.appendChild(confirmPasswordLabel);
    form.appendChild(confirmPasswordInput);
    form.appendChild(institutionsLabel);
    form.appendChild(institutionSelect);
    form.appendChild(yearStartLabel);
    form.appendChild(yearStartSelect);
    form.appendChild(yearEndLabel);
    form.appendChild(yearEndSelect);
    form.appendChild(submitButton);
}

export function addDegreesToADiv(degreeJson) {
    degreeDivContainer.innerHTML = ''; //clear div
    selectedDegrees = []; //clear selected array
    console.log(degreeJson);
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
                // console.log('currently in array: ',selectedDegrees[i]);
                getCourses(selectedDegrees[i], institutionSelect.value);
            }
            /*
                After each click clear the courses container
                scan through the current selected degree
                send a request to the server with the current degrees and the university name 
                then get the courses from the server in json
                scan through the json and add them like how I added degrees 
                then add the onclick listener to them and add them the same way i did degrees
            */
        });
    });
}

function handleSignUp() {
    const username = document.getElementById('username').value;
    const firstname = document.getElementById('firstname').value;
    const lastname = document.getElementById('lastname').value;
    const password = document.getElementById('password').value;
    const passwordConfirm = document.getElementById('confirmPassword').value;

    if(password == passwordConfirm){
        const user = new User(firstname, lastname, username, password, "default",institutionSelect.value,0,selectedDegrees,[], yearStartSelect.value,yearEndSelect.value);
        console.log(user);
        registerUser(user);
    }else{
        alert("password does not match");
    }
    
}