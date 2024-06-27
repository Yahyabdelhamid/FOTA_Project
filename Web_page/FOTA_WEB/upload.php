<?php

file_put_contents("record.txt", "");


if (isset($_POST['submit']))
{
	$file=$_FILES['file'];
	
	$fileName   =$_FILES['file']['name'];
	$fileTmpName=$_FILES['file']['tmp_name'];
	$fileSize   =$_FILES['file']['size'];
	$fileError  =$_FILES['file']['error'];
	$fileType   =$_FILES['file']['type'];
	
	$fileExt = explode('.',$fileName) ; 
	$fileActualExt = strtolower(end($fileExt));
	
	$allowed = array('hex');
	
	if(in_array($fileActualExt, $allowed))
	{
		if ($fileError === 0)
		{
			if ($fileSize < 100000)
			{  
				// Deleting all the files inside the given folder 
				array_map('unlink', array_filter( 
				(array) array_merge(glob("uploads/*")))); 
  
				// Rename the new file and save it alone in "uploads" folder
				$fileNameNew = "hex"."."."txt" ;
				$fileDestination='uploads/'.$fileNameNew;
				move_uploaded_file($fileTmpName, $fileDestination);
				$myfile=fopen("mc_check.txt","w");
				fwrite($myfile,"1");
				fclose($myfile);
				header("Location: Transmitter.php");
				
			}
			else
			{
				echo "Your file is too big" ;
				//put an image
				$myfile=fopen("mc_check.txt","w");fwrite($myfile,"0");fclose($myfile);
			}
			
		}
		else
		{
				echo "Error Uploading your file " ;
				$myfile=fopen("mc_check.txt","w");fwrite($myfile,"0");fclose($myfile);
				//put an image
		}
	}
	else
	{
		echo "Invalid file type" ;
		$myfile=fopen("mc_check.txt","w");fwrite($myfile,"0");fclose($myfile);
		//put an image
	}

}