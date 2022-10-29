<?php
    $servername= "localhost";
    $username="root";
    $password="";
    $dbname="waterTank";
    $con = mysqli_connect($servername,$username,$password,$dbname);

    $first_name =$_GET['first_name'];
    $last_name =$_GET['last_name'];
    $ownerID = $_GET['ownerID'];

    $handler = "SELECT ownerID FROM ownerDetails WHERE ownerID={$_GET['ownerID']}";
    $sql = "INSERT INTO ownerDetails (first_name, last_name, ownerID)
    VALUES ('{$first_name}','{$last_name}','{$ownerID}')";

     $dl = mysqli_query($con,$handler);
     if($dl){
         if(mysqli_num_rows($dl) == 1){
             echo "Onwer already in database";
         } else{
             if(mysqli_query($con,$sql)){
                 echo "New record created successfully";
             } else {
                 echo "Failed to record";
                 exit(1);
             }
         }
     }

?>