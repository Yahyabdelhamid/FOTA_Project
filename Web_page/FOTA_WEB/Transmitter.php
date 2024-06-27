<?php
ob_start();
ini_set('max_execution_time',300);

$handle = fopen("uploads/hex.txt", "r");
$counter=41;
$End=0;
/* open the file in write mode*/
	$myfile=fopen("status.txt","w");
	fwrite($myfile,"  ");
	fclose($myfile);
	
	
while (1) 
{
	/* open the file in write mode*/
	$myfile=fopen("status.txt","r");
	$value=fgets($myfile);
	if($value=='ok')
	{
		$record = fopen("record.txt", "w");
		while($counter--)
		{
			
		
			if(($line = fgets($handle)) == false)
			{
				$End=1;
				$mc=fopen("mc_check.txt","w");
				fwrite($mc,"0");
				fclose($mc);
				fwrite($record,"#");
				break;
			}
			//$line = fgets($handle);
			echo "$line"."<br>";
			fwrite($record,$line);// process the line read.
			
		}
		if($End==1)break;

		fwrite($record,"@");
		fclose($record);
			
		fclose($myfile);
		$myfile=fopen("status.txt","w");
		fwrite($myfile,"   ");
		fclose($myfile);
		
		
	}
	$counter=41;
	
}
header("LOCATION: Done.php");
ob_end_flush();
?>