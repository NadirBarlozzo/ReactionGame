<?php

$score = $_GET['score'];
$modality = $_GET['modality'];

echo "<style> td { border: 1px solid black; padding: 5px; } table { border-collapse: collapse; }</style>";

$servername = "localhost";
$username = "root";
$password = "";
//$password = "root1";
$dbname = "reactiongame";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
	die("Connessione fallita: " . $conn->connect_error);
}

$f_contents = file("nouns.txt"); 
$name = $f_contents[rand(0, count($f_contents) - 1)];

$sql = "INSERT INTO `giocatore` (`Gio_Nome`) VALUES ('".$name."')";
$result = $conn->query($sql);

$sql2 = "SELECT Gio_ID FROM giocatore ORDER BY Gio_ID DESC LIMIT 1";
$result2 = $conn->query($sql2);
$id = 0;

if ($result2->num_rows > 0) {
    while($row = $result2->fetch_assoc()) {
        $id = $row['Gio_ID'];
    }
} else {
    echo "0 results";
}

$sql = "INSERT INTO `utilizza` (`punteggio`, `Gio_IDGiocatore`, `Mod_IDModalita`, `nr_partita`) VALUES ('".$score."', '".($id)."', '".$modality."', 667)";
$result = $conn->query($sql);

$conn->close();

?>