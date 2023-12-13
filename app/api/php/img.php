<?php

// Enable CORS
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Allow-Headers: Content-Type");

// Check if a file was uploaded
if (isset($_FILES['inpFile'])) {
    
    // File details
    $file_name = $_FILES['inpFile']['name'];
    $file_temp = $_FILES['inpFile']['tmp_name'];
    $file_size = $_FILES['inpFile']['size'];
    $file_error = $_FILES['inpFile']['error'];

    // Check for errors
    if ($file_error === 0) {

        // Specify the upload directory
        $upload_dir = 'uploads/';

        // Create the directory if it doesn't exist
        if (!is_dir($upload_dir)) {
            mkdir($upload_dir, 0777, true);
        }

        // Generate a unique filename to avoid overwriting
        $file_destination = $upload_dir . uniqid() . '_' . $file_name;

        // Move the file from the temporary location to the destination
        if (move_uploaded_file($file_temp, $file_destination)) {
            echo 'File uploaded successfully.';
        } else {
            echo 'Error uploading file.';
        }

    } else {
        echo 'Error: ' . $file_error;
    }

} else {
    echo 'No file uploaded.';
}

?>

