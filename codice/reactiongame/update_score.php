<?php

$score = $_GET['score'];

$servername = "localhost";
$username = "root";
$password = "";
//$password = "root1";
$dbname = "reactiongame";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
	die("Connessione fallita: " . $conn->connect_error);
}

$sql = "SELECT `nr_partita` FROM `utilizza` ORDER BY `nr_partita` DESC LIMIT 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();

$sql = "UPDATE `utilizza` SET `punteggio` = ".$score." WHERE `nr_partita` = ".$row['nr_partita'];
$result = $conn->query($sql);

$conn->close();

?>