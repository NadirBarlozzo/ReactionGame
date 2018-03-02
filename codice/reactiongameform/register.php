<?php
	ob_start();
	session_start();
	
	if(isset($_SESSION['user'])!= ""){
		header("Location: home.php");
	}

	$name = "";
	$surname = "";
	$email = "";
	$nameError = "";
	$surnameError = "";
	$emailError = "";
	
	include_once 'dbconnect.php';

	$error = false;

	if (isset($_POST['btn-signup'])) {
		
		// clean user inputs to prevent sql injections
		$name = trim($_POST['name']);
		$name = strip_tags($name);
		$name = htmlspecialchars($name);
		
		$email = trim($_POST['email']);
		$email = strip_tags($email);
		$email = htmlspecialchars($email);
		
		$surname = trim($_POST['surname']);
		$surname = strip_tags($surname);
		$surname = htmlspecialchars($surname);
		
		// basic name validation
		if (empty($name)) {
			$error = true;
			$nameError = "Please enter your full name.";
		} else if (strlen($name) < 3) {
			$error = true;
			$nameError = "Name must have atleat 3 characters.";
		} else if (!preg_match("/^[a-zA-Z ]+$/",$name)) {
			$error = true;
			$nameError = "Name must contain alphabets and space.";
		}
		
		if (empty($surname)) {
			$error = true;
			$surnameError = "Please enter your full name.";
		} else if (strlen($surname) < 3) {
			$error = true;
			$surnameError = "Name must have atleat 3 characters.";
		} else if (!preg_match("/^[a-zA-Z ]+$/",$surname)) {
			$error = true;
			$surnameError = "Name must contain alphabets and space.";
		}
		
		//basic email validation
		if (!filter_var($email,FILTER_VALIDATE_EMAIL)) {
			$error = true;
			$emailError = "Please enter valid email address.";
		} else {
			// check email exist or not
			$query = "SELECT `Gio_Email` FROM `giocatore` WHERE `Gio_Email`='$email'";
			$result = $conn->query($query);
			
			$count = $result->num_rows;
			if($count != 0){
				$error = true;
				$emailError = "Provided Email is already in use.";
			}
		}
		
		if(!$error) {
			
			$query = "INSERT INTO `giocatore` (`Gio_Nome`, `Gio_Email`, `Gio_Cognome`) VALUES ('".$name."', '".$email."', '".$surname."')";
			$res = $conn->query($query);
				
			if ($res) {
				$errTyp = "success";
				$errMSG = "Successfully registered, you may login now";
				unset($name);
				unset($email);
				unset($surname);
				header("Location: home.php");		
			} else {
				$errTyp = "danger";
				$errMSG = "Something went wrong, try again later...";	
			}	
				
		}
		
		
	}
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Reactiongame - Login & Registration</title>
<link rel="stylesheet" href="assets/css/bootstrap.min.css" type="text/css"  />
<link rel="stylesheet" href="style.css" type="text/css" />
</head>
<body>

<div class="container">

	<div id="login-form">
    <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" autocomplete="off">
    
    	<div class="col-md-12">
        
        	<div class="form-group">
            	<h2 class="">Sign Up.</h2>
            </div>
        
        	<div class="form-group">
            	<hr />
            </div>
            
            <?php
			if (isset($errMSG)) {	
			?>
				<div class="form-group">
            	<div class="alert alert-<?php echo ($errTyp=="success") ? "success" : $errTyp; ?>">
				<span class="glyphicon glyphicon-info-sign"></span> <?php echo $errMSG; ?>
                </div>
            	</div>
            <?php
			}
			?>
            
            <div class="form-group">
            	<div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>
            	<input type="text" name="name" class="form-control" placeholder="Enter Name" maxlength="50" value="<?php echo $name ?>"/>
                </div>
                <span class="text-danger"><?php echo $nameError; ?></span>
            </div>
            
			<div class="form-group">
            	<div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>
            	<input type="text" name="surname" class="form-control" placeholder="Enter Surname" maxlength="50"/>
                </div>
                <span class="text-danger"><?php echo $surnameError; ?></span>
            </div>
			
            <div class="form-group">
            	<div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-envelope"></span></span>
            	<input type="email" name="email" class="form-control" placeholder="Enter Your Email" maxlength="50" value="<?php echo $email ?>"/>
                </div>
                <span class="text-danger"><?php echo $emailError; ?></span>
            </div>
            
            <div class="form-group">
            	<hr />
            </div>
            
            <div class="form-group">
            	<button type="submit" class="btn btn-block btn-primary" name="btn-signup">Sign Up</button>
            </div>
            
            <div class="form-group">
            	<hr />
            </div>
            
            <div class="form-group">
            	<a href="index.php">Sign in Here...</a>
            </div>
        
        </div>
   
    </form>
    </div>	

</div>

</body>
</html>
<?php ob_end_flush(); ?>