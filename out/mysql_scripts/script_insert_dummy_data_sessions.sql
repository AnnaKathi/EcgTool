# //Dummy-Daten in alle Datenbank eintragen: Session-Daten
#
# //-- Subjects, 1=weiblich, 0=männlich
INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`, `Age`, `Sex`) VALUES ('Anna', 'Stratmann', 35, 1);
INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`, `Age`, `Sex`) VALUES ('Manfred', 'Umlauff', 63, 0);
INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`, `Age`, `Sex`) VALUES ('Manuela', 'Stratmann', 56, 1);
INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`, `Age`, `Sex`) VALUES ('Martin', 'Stratmann', 58, 0);

# //-- Sub-Diseases, Diseases 1-8, Subjects 1-4
# //Anna ist gesund, bei Manfred, Martin und Manuela Krankheiten simulieren
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 1);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 5);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 7);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (3, 2);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 3);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 5);

# //-- Sessions, drei Sessions simulieren
INSERT INTO `ecg`.`sessions` (`Orte_ID`, `Stamp`, `Kommentar`) VALUES (12, '2017-05-01 11:02:16', 'Testerfassung mit dem neuen Gerät im Verein');
INSERT INTO `ecg`.`sessions` (`Orte_ID`, `Stamp`, `Kommentar`) VALUES (2,  '2017-05-01 11:35:00', 'Testerfassung mit dem neuen Gerät, Klebeelektroden');
INSERT INTO `ecg`.`sessions` (`Orte_ID`, `Stamp`, `Kommentar`) VALUES (4,  '2017-05-06 12:00:00', 'Testerfassung mit dem alten Gerät, PinOnly statt Klebeelektroden verwendet');

# //-- Session-Researchers
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (1, 1);
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (2, 1);
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (2, 2);
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (2, 3);
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (3, 1);
INSERT INTO `ecg`.`sessionresearchers` (`Sessions_ID`, `Researchers_ID`) VALUES (3, 2);

# //-- EcgData, Manfred liegend2

# //-- Erkennungswerte

