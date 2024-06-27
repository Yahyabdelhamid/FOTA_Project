<?php

session_start();
if(isset($_SESSION["username"] )){  
?>
<!DOCTYPE html>
<html>
<head>
    <!-- Title of the webpage -->
<title>OTA Programmer</title>
<!-- Favicon for the webpage -->
<link rel="icon" href="Logo1.png">
<!-- Link to external CSS stylesheet -->

</head>
<body>
    <!-- Logo with a fade-in transition effect -->
   <div class="logo" style="opacity: 0; transition: all 2s;" >
     <img src="22.png" alt="logo">
   </div>
   <span style="color: white;
    margin: 10px;
    padding: 10px 20px;
    background: red;
    border-radius: 14px;
    position: absolute;
    bottom: 10px;
	right : 10px; opacity: 0; transition: all 2s; " class="logout"><a href='./../logout.php' style="
    text-decoration: none;
    color: white;
" ><font face = "Gill sans mt">Log Out</font></a></span>
<style>
.Button1
{
border: 1px solid red;
padding: 10px;
font-size: 17px;
border-radius: 21px;
transition: all 0.5s;
color:white;
background:red;
font-family: 'Raleway', sans-serif;
cursor: pointer;
}

.Button1:hover
{
border: 1px solid red;
color: red;
padding: 10px;
font-size: 17px;
border-radius: 21px;
transition: all 0.5s;
background:white;
font-family: 'Raleway', sans-serif;
}
</style>

<center>
<font face = "Gill sans mt" color = "white"> <!-- Main heading with a fade-in transition effect -->
<br>
<br>
<h1 style="opacity: 0;
    transition: all 2s;" class="one" ><font size = 7 color = "red">PROGRAM&nbsp;YOUR&nbsp;MCU&nbsp;WHERE&nbsp;EVER&nbsp;YOU&nbsp;ARE</font></h1>
<h2 style="opacity: 0;
    transition: all 2s;" class="two"> <i><font color = "orange"></font></i>
<br>
<br>Enjoy the OTA Programming</h2>
</font> 
<h1>
<br> <!-- Form for uploading .hex files with a fade-in transition effect -->
<br>
</h1>
<form action="upload.php" method="POST" enctype="multipart/form-data" style="opacity: 0; transition: all 2s;" class="form">
	<input class="Button1" type="file" name="file" id='file_' style='display: none;'>
	<label for='file_'  style="
    display: inline-block;
    width: auto;
    margin: 0px 20px;
    background: transparent;
    padding: 9px 10px;
    color: white;
    border: 3px solid white;
    border-radius: 22px;
    text-align: left;
	font-family: 'Raleway', sans-serif;
	cursor: pointer;
"> <span style="
    margin-right: 42px;
    background: red;
    padding: 5px 22px;
    border-radius: 13px;           
    margin: 5px 6px 5px 0px;
	font-family: 'Raleway', sans-serif;                      
" >Upload File</span> <span class="file_name">No file chosen</span></label>
	<button class="Button1" type="submit" name="submit">UPLOAD</button>
</form>
</center> 
<!-- Link to external JavaScript file -->
<script src="main.js"></script>

</body>
</html>

<?php

}
else{
header("Location: ./../index.php");
}

?>