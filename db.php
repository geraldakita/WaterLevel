<?php
    header('Access-Control-Allow-Origin: *');
    
    $servername= "localhost";
    $username="root";
    $password="";
    $dbname="watertank";
    $con = mysqli_connect($servername,$username,$password,$dbname);

    if (!isset($_GET['id'])) 
    die(" id not specified");
if ($_GET['id']=='')
    die(" id is blank");
if (!is_numeric($_GET['id'] ) )
    die(" id is not numeric");

$data=array();        

$q=mysqli_query($con,"select * from waterdetails where id={$_GET['id']}");    

$row=mysqli_fetch_object($q);
while ($row)
{         
    echo "id: ";
    echo "{$row->id}\n";
    echo "OwnerID: ";
    echo "{$row->ownerID}\n";
    echo "Water Level: ";
    echo "{$row->water_level}\n";
    echo "Location: ";
    echo "{$row->location}\n";
    echo "Time/Date: ";
    echo "{$row->time}";
    $row=mysqli_fetch_object($q);
}       

    


?>
