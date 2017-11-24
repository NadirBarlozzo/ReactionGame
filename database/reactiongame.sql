-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Versione server:              10.1.22-MariaDB - mariadb.org binary distribution
-- S.O. server:                  Win32
-- HeidiSQL Versione:            9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Dump della struttura del database reactiongame
CREATE DATABASE IF NOT EXISTS `reactiongame` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `reactiongame`;

-- Dump della struttura di tabella reactiongame.giocatore
CREATE TABLE IF NOT EXISTS `giocatore` (
  `Gio_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Gio_Nome` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Gio_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

-- L’esportazione dei dati non era selezionata.
-- Dump della struttura di tabella reactiongame.modalita
CREATE TABLE IF NOT EXISTS `modalita` (
  `Mod_ID` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`Mod_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;

-- L’esportazione dei dati non era selezionata.
-- Dump della struttura di tabella reactiongame.utilizza
CREATE TABLE IF NOT EXISTS `utilizza` (
  `punteggio` int(11) DEFAULT NULL,
  `Gio_IDGiocatore` int(11) NOT NULL,
  `Mod_IDModalita` int(11) NOT NULL,
  PRIMARY KEY (`Gio_IDGiocatore`,`Mod_IDModalita`),
  KEY `Gio_IDGiocatore` (`Gio_IDGiocatore`),
  KEY `Mod_IDModalita` (`Mod_IDModalita`),
  CONSTRAINT `FK_utlizza_giocatore` FOREIGN KEY (`Gio_IDGiocatore`) REFERENCES `giocatore` (`Gio_ID`),
  CONSTRAINT `FK_utlizza_modalita` FOREIGN KEY (`Mod_IDModalita`) REFERENCES `modalita` (`Mod_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- L’esportazione dei dati non era selezionata.
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
