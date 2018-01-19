<?php

echo "<style> td { border: 1px solid black; padding: 5px; } table { border-collapse: collapse; }</style>";

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "reactiongame";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
	die("Connessione fallita: " . $conn->connect_error);
} 

$sql = "SELECT Gio_Nome, punteggio, Mod_ID FROM giocatore, utilizza, modalita WHERE Gio_ID = Gio_IDGiocatore AND Mod_ID = Mod_IDModalita";
$result = $conn->query($sql);

echo "Tabella punteggi: <br>";
echo "<table>";

if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>Nome: " . $row["Gio_Nome"]. "</td><td>Modalità: " . $row["Mod_ID"]. "</td><td>Punteggio: " . $row["punteggio"] . "</td></tr><br>";
    }
} else {
    echo "0 results";
}

echo "</table>";

$conn->close();

?>