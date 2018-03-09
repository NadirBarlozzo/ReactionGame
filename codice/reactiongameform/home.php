<?php
	ob_start();
	session_start();
	require_once 'dbconnect.php';	
		
	// if session is not set this will redirect to login page
	if(!isset($_SESSION['user'])) {
		header("Location: index.php");
		exit;
	}
	// select loggedin users detail
	$query = "SELECT * FROM `giocatore` WHERE `Gio_ID`=".$_SESSION['user'];
	$result = $conn->query($query);
	$row = $result->fetch_assoc();
					
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Welcome - <?php echo $row['Gio_Email']; ?></title>
<link rel="stylesheet" href="assets/css/bootstrap.min.css" type="text/css"  />
<link rel="stylesheet" href="style.css" type="text/css" />
</head>
<body>
	<nav class="navbar navbar-default navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="https://github.com/NadirBarlozzo/ReactionGame">ReactionGame</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav navbar-right">
            <li class="dropdown">
              <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
			  <span class="glyphicon glyphicon-user"></span>&nbsp;<?php echo $row['Gio_Email']; ?>&nbsp;<span class="caret"></span></a>
              <ul class="dropdown-menu">
                <li><a href="logout.php?logout"><span class="glyphicon glyphicon-log-out"></span>&nbsp;Esci</a></li>
              </ul>
            </li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav> 

	<div id="wrapper">
		<div class="container">
			<div class="page-header">
				<h3>Benvenuto <?php echo $row['Gio_Nome']; ?></h3>
			</div>
			<div class="row" id="start">
				<div class="col-lg-12">
					<p>Per iniziare a giocare scegli la modalità premendo il relativo bottone sul telecomando.</p>
				</div>
			</div>
			<script>
	
			setInterval(function() {
				xmlhttp = new XMLHttpRequest();
				xmlhttp.onreadystatechange = function() {
		            if (this.readyState == 4 && this.status == 200) {
		                document.getElementById("content").innerHTML = this.responseText;
		            }
		        };
		        xmlhttp.open("GET","update.php");
		        xmlhttp.send();

			}, 5000)
	
			</script>
			<div id="content"></div>

			<div class="row" id="end" style="display:none">
				<div class="col-lg-12">
					<p>Complimenti, hai totalizzato punti nella tua partita.</p>
					<form action="home.php" method="get">
					  <input type="submit" value="Gioca ancora">
					</form>
				</div>
			</div>
		</div>
	</div>    
    <script src="assets/jquery-1.11.3-jquery.min.js"></script>
    <script src="assets/js/bootstrap.min.js"></script>
</body>
</html>
<?php ob_end_flush(); ?>