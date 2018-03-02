<?php
	ob_start();
	session_start();
	require_once 'dbconnect.php';
	
	// it will never let you open index(login) page if session is set
	if (isset($_SESSION['user']) != "") {
		header("Location: home.php");
		exit;
	}
	
	$name = "";
	$surname = "";
	$email = "";
	$nameError = "";
	$surnameError = "";
	$emailError = "";
	
	$error = false;
	
	if(isset($_POST['btn-login'])) {	
		
		// prevent sql injections/ clear user invalid inputs
		$email = trim($_POST['email']);
		$email = strip_tags($email);
		$email = htmlspecialchars($email);
				
		if(empty($email)){
			$error = true;
			$emailError = "Please enter your email address.";
		} else if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
			$error = true;
			$emailError = "Please enter valid email address.";
		}
		
		if (!$error) {
			
			$query = "SELECT `Gio_ID`, `Gio_Email` FROM `giocatore` WHERE `Gio_Email`='$email'";
			$result = $conn->query($query);
			$row = $result->fetch_assoc();
			$count = $result->num_rows;
			
			if($count == 1) {
				$_SESSION['user'] = $row['Gio_ID'];
								
				$query = "INSERT INTO `utilizza` (`punteggio`, `Gio_IDGiocatore`, `Mod_IDModalita`) VALUES (0,".($row['Gio_ID']).", 24)";
				$conn->query($query);
				
				$query = "SELECT `nr_partita` FROM `utilizza` ORDER BY `nr_partita` DESC LIMIT 1";
				$result = $conn->query($query);
				$row = $result->fetch_assoc();
				
				$_SESSION['game'] = $row['nr_partita'];
				
				header("Location: home.php");
			} else {
				$errMSG = "Incorrect Credentials, Try again...";
			}
				
		}
		
	}
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Coding Cage - Login & Registration System</title>
<link rel="stylesheet" href="assets/css/bootstrap.min.css" type="text/css"  />
<link rel="stylesheet" href="style.css" type="text/css" />
</head>
<body>

<div class="container">

	<div id="login-form">
    <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" autocomplete="off">
    
    	<div class="col-md-12">
        
        	<div class="form-group">
            	<h2 class="">Sign In.</h2>
            </div>
        
        	<div class="form-group">
            	<hr />
            </div>
            
            <?php
			if (isset($errMSG)) {
			?>
				<div class="form-group">
            	<div class="alert alert-danger">
				<span class="glyphicon glyphicon-info-sign"></span> <?php echo $errMSG; ?>
                </div>
            	</div>
            <?php
			}
			?>
            
            <div class="form-group">
            	<div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-envelope"></span></span>
            	<input type="email" name="email" class="form-control" placeholder="Your Email" value="<?php echo $email; ?>" maxlength="40" />
                </div>
                <span class="text-danger"><?php echo $emailError; ?></span>
            </div>
                        
            <div class="form-group">
            	<hr />
            </div>
            
            <div class="form-group">
            	<button type="submit" class="btn btn-block btn-primary" name="btn-login">Sign In</button>
            </div>
            
            <div class="form-group">
            	<hr />
            </div>
            
            <div class="form-group">
            	<a href="register.php">Sign Up Here...</a>
            </div>
        
        </div>
   
    </form>
    </div>	

</div>

</body>
</html>
<?php ob_end_flush(); ?>