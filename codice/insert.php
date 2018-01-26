<?php

$score = $_GET['score'];
$modality = $_GET['modality'];

echo "<style> td { border: 1px solid black; padding: 5px; } table { border-collapse: collapse; }</style>";

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "reactiongame";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
	die("Connessione fallita: " . $conn->connect_error);
} 
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
$sql = "INSERT INTO `utilizza` (`punteggio`, `Gio_IDGiocatore`, `Mod_IDModalita`) VALUES ('".$score."', '".($id+1)."', '".$modality."')";
$result = $conn->query($sql);

$conn->close();

?>