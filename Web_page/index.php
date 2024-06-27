<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {

    if (isset($_POST['Username']) and isset($_POST['Password'])) {
        $username = $_POST['Username'];
        $password = $_POST['Password'];
        if (empty($username) or empty($password)) {
            $empty = 1;
        } else {
            if ($username == 'YAHYA' and $password == 'YAHYA') {
				$_SESSION["username"]  = $username ;
                header("Location: ./FOTA_WEB/index.php");
            } else {
                $wrong = 1;
            }
        }
    }
} else {
}
?>
<!doctype html>
<html>

<head>
    <meta charset='utf-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <title>OTA Programmer</title>
	<link rel="icon" href="Logo1.png">
    
</head>

<body oncontextmenu='return false' class='snippet-body'>
    <div class="loginBox">
        <?php
        if (isset($wrong) and $wrong == 1) {
        ?>
            <div class="alert alert-danger" role="alert">
                username or password is wrong
            </div>
        <?php
        } elseif (isset($empty) and $empty == 1) {
        ?>
            <div class="alert alert-danger" role="alert">
                you should enter usernam and password
            </div>
        <?php

        }

        ?>
        <div class="image-div"><img class="user" src="Logo1.png" height="100px" width="100px"></div>
        <h3><i>Sign in here </i></h3>
        <form action="" method="post">
            <div class="inputBox"> <input id="uname" type="text" name="Username" placeholder="Username">
                <input id="pass" type="password" name="Password" placeholder="Password">
            </div> <input type="submit" name="" value="Login">
        </form>
    </div>
    <script type='text/javascript' src='https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-alpha1/dist/js/bootstrap.bundle.min.js'></script>
    <script type='text/javascript' src=''></script>
    <script type='text/javascript' src=''></script>
    <script type='text/Javascript'></script>
</body>

</html>