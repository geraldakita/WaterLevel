<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "watertank";

$con = mysqli_connect($servername, $username, $password,$dbname);

$ownerid=$_GET['ownerid'];

//echo "Hello";

$sql2= "SELECT water_level, time FROM waterdetails WHERE ownerid = '{$ownerid}' ORDER BY time DESC LIMIT 5";

$q2 = mysqli_query($con,$sql2);

while ($row=mysqli_fetch_object($q2))
{ 
        print "{$row->water_level} {$row->time}"."<br>";

}

?>