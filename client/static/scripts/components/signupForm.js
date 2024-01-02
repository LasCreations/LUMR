import User from '../modules/user.js'

export function createSignUpForm() {

    const form = document.createElement('form');
    form.id = 'signupForm';

    //Username label
    const usernameLabel = document.createElement('label');
    usernameLabel.for = 'username';
    usernameLabel.textContent = 'Username:';
    form.appendChild(usernameLabel);

    //Username input
    const usernameInput = document.createElement('input');
    usernameInput.type = 'text';
    usernameInput.id = 'username';
    usernameInput.name = 'username';
    form.appendChild(usernameInput);

    //Password label
    const passwordLabel = document.createElement('label');
    passwordLabel.for = 'password';
    passwordLabel.textContent = 'Password:';
    form.appendChild(passwordLabel);

    //Password input
    const passwordInput = document.createElement('input');
    passwordInput.type = 'password';
    passwordInput.id = 'password';
    passwordInput.name = 'password';
    form.appendChild(passwordInput);

    const roleSelect = document.createElement('select');
    roleSelect.id = 'role';
    roleSelect.name = 'role';

    // Add options to the select element
    const options = ['Admin', 'User', 'Guest'];
    options.forEach(optionValue => {
        const option = document.createElement('option');
        option.value = optionValue.toLowerCase();
        option.text = optionValue;
        roleSelect.appendChild(option);
    });
    form.appendChild(roleSelect);


    // Submit button
    const submitButton = document.createElement('button');
    submitButton.type = 'button'; // Use 'button' to prevent form submission for this example
    submitButton.textContent = 'Signup';
    submitButton.addEventListener('click', handleSignUp);
    form.appendChild(submitButton);

    // Append the form to the 'app' div
    document.getElementById('signUpForm-container').appendChild(form);
}

function handleSignUp() {

    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;

    console.log('Login clicked with username:', username, 'and password:', password);
}