<body>
	<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<input type="text" name="name">
		<input type=""
	</form>
</body>
<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "reactiongame";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
	die("Connessione fallita: " . $conn->connect_error);
}

$conn->close();

?>