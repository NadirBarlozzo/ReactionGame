-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: Mar 01, 2018 alle 17:02
-- Versione del server: 10.1.29-MariaDB
-- Versione PHP: 7.2.0

CREATE SCHEMA reactiongame;
USE SCHEMA reactiongame;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `reactiongame`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `giocatore`
--

CREATE TABLE `giocatore` (
  `Gio_ID` int(11) NOT NULL,
  `Gio_Nome` varchar(50) DEFAULT NULL,
  `Gio_Email` varchar(50) NOT NULL,
  `Gio_Cognome` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `giocatore`
--

INSERT INTO `giocatore` (`Gio_ID`, `Gio_Nome`, `Gio_Email`, `Gio_Cognome`) VALUES
(2, 'b', '', ''),
(3, 'c', '', ''),
(4, 'd', '', ''),
(5, 'e', '', ''),
(31, 'nadir', 'nadir.barlozzo@gmail.com', 'barlozzo'),
(32, 'Dyuman', 'dyuman.bulloni@samtrevano.ch', 'Bulloni'),
(33, 'Luca', 'luca.rausa@samtrevano.ch', 'Rausa'),
(34, 'Erik', 'erik.stalliviere@samtrevano.ch', 'Stalliviere');

-- --------------------------------------------------------

--
-- Struttura della tabella `modalita`
--

CREATE TABLE `modalita` (
  `Mod_ID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `modalita`
--

INSERT INTO `modalita` (`Mod_ID`) VALUES
(1),
(2),
(3),
(4),
(5),
(6),
(7),
(8),
(9),
(10),
(11),
(12),
(13),
(14),
(15),
(16),
(17),
(18),
(19),
(20),
(21),
(22),
(23),
(24);

-- --------------------------------------------------------

--
-- Struttura della tabella `utilizza`
--

CREATE TABLE `utilizza` (
  `punteggio` int(11) DEFAULT NULL,
  `Gio_IDGiocatore` int(11) NOT NULL,
  `Mod_IDModalita` int(11) NOT NULL,
  `nr_partita` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `utilizza`
--

INSERT INTO `utilizza` (`punteggio`, `Gio_IDGiocatore`, `Mod_IDModalita`, `nr_partita`) VALUES
(0, 33, 1, 23),
(0, 33, 24, 24),
(0, 33, 24, 25),
(0, 33, 11, 26),
(0, 33, 17, 27),
(0, 33, 8, 28),
(0, 33, 14, 29),
(0, 33, 24, 30),
(0, 33, 24, 31),
(0, 33, 9, 32),
(0, 32, 17, 33),
(0, 34, 12, 34);

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `giocatore`
--
ALTER TABLE `giocatore`
  ADD PRIMARY KEY (`Gio_ID`);

--
-- Indici per le tabelle `modalita`
--
ALTER TABLE `modalita`
  ADD PRIMARY KEY (`Mod_ID`);

--
-- Indici per le tabelle `utilizza`
--
ALTER TABLE `utilizza`
  ADD PRIMARY KEY (`nr_partita`),
  ADD KEY `Gio_IDGiocatore` (`Gio_IDGiocatore`),
  ADD KEY `Mod_IDModalita` (`Mod_IDModalita`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `giocatore`
--
ALTER TABLE `giocatore`
  MODIFY `Gio_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=35;

--
-- AUTO_INCREMENT per la tabella `modalita`
--
ALTER TABLE `modalita`
  MODIFY `Mod_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;

--
-- AUTO_INCREMENT per la tabella `utilizza`
--
ALTER TABLE `utilizza`
  MODIFY `nr_partita` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=35;

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `utilizza`
--
ALTER TABLE `utilizza`
  ADD CONSTRAINT `FK_utlizza_giocatore` FOREIGN KEY (`Gio_IDGiocatore`) REFERENCES `giocatore` (`Gio_ID`),
  ADD CONSTRAINT `FK_utlizza_modalita` FOREIGN KEY (`Mod_IDModalita`) REFERENCES `modalita` (`Mod_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
