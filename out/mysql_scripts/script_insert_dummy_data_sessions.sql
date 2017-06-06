# //Dummy-Daten in alle Datenbank eintragen: Session-Daten
#
# //-- Subjects, 1=weiblich, 0=männlich
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Age`, `Sex`) VALUES ('Anna', 'Stratmann', 35, 1);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Age`, `Sex`) VALUES ('Manfred', 'Umlauff', 63, 0);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Age`, `Sex`) VALUES ('Manuela', 'Stratmann', 56, 1);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Age`, `Sex`) VALUES ('Martin', 'Stratmann', 58, 0);

# //-- Sub-Diseases, Diseases 1-8, Subjects 1-4
# //Anna ist gesund, bei Manfred, Martin und Manuela Krankheiten simulieren
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 1);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 5);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 7);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (3, 2);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 3);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 5);

# //-- Sessions, drei Sessions simulieren

# //-- Session-Researchers

# //-- EcgData, Manfred liegend2

# //-- Erkennungswerte

