<?php
if(isset($_GET['Rx']))
{
    // Open the file in write mode
    $myfile = fopen("status.txt","w");
    
    // Check if file opened successfully
    if ($myfile === false) {
        echo "Error opening file";
    } else {
        if($_GET['Rx'] == 'ok')
        {   
            echo "ok";
            fwrite($myfile, "ok");
            fclose($myfile); // Close the file
        }
        elseif($_GET['Rx'] != 'ok')
        {
            fwrite($myfile, '  ');
            echo "no";
            fclose($myfile); // Close the file
        }
    }
}
?>