<?php
$servername= "localhost";
$username="root";
$password="";
$dbname="waterTank";
$con = mysqli_connect($servername,$username,$password,$dbname);

$water_level=$_GET['water_level'];
$location = $_GET['location'];
$ownerID = $_GET['ownerID'];

$sql = "INSERT INTO waterDetails (water_level, location, ownerID)
        VALUES ('{$water_level}','{$location}','{$ownerID}')";

if(mysqli_query($con,$sql)){
    echo "New record created successfully";
} else {
    echo "Failed to record";
    }
?>