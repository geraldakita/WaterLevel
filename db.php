<?php

    $servername= "localhost";
    $username="root";
    $password="";
    $dbname="iotlab4";
    $con = mysqli_connect($servername,$username,$password,$dbname);

    if (!isset($_GET['ID'])) 
    die(" ID not specified");
if ($_GET['ID']=='')
    die(" ID is blank");
if (!is_numeric($_GET['ID'] ) )
    die(" ID is not numeric");

$data=array();        

$q=mysqli_query($con,"select * from lab4 where ID={$_GET['ID']}");    

$row=mysqli_fetch_object($q);
while ($row)
{         
    echo "ID: ";
    echo "{$row->ID}\n";
    echo "Temperature: ";
    echo "{$row->temperature}\n";
    echo "Humidity: ";
    echo "{$row->humidity}";
    $row=mysqli_fetch_object($q);
}       

    


?>
