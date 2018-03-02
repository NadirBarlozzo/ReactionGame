<?php 
	ob_start();
	session_start();
	require_once 'dbconnect.php';

	$query = "SELECT * FROM `utilizza` WHERE `Gio_IDGiocatore`=".$_SESSION['user']." AND `nr_partita`=".$_SESSION['game'];
	$result = $conn->query($query);
	$row = $result->fetch_assoc();
	$currentMod = null;
	
	if($row['Mod_IDModalita'] != 24) {
		$currentMod = $row['Mod_IDModalita'];
		echo('<div class="row">
				<div class="col-lg-12">
					<p>Stai giocando alla modalità <b>'.$currentMod.'</b>, buona fortuna!</p>
				</div>
			</div>');
		echo("<style> #start { display: none; }</style>");
	}
?>