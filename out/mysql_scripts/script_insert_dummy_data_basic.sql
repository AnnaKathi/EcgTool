# //Dummy-Daten in alle Datenbank eintragen: Grunddefinitionen
#
# //-- Diseases
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Koronare Herzkrankheit');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Angina Pectoris');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Herzklappendefekt');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Herzinfarkt');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Herzschwäche');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Myokarditis');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Tachykardie');
INSERT INTO `ecg`.`diseases` (`Bez`) VALUES ('Bradykardie');

# //-- Orte
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Auto A8');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Zuhause - Arbeitszimmer');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Zuhause - Balkon');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Firma - Arb.platz Anna');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Firma - Kleines Büro');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Firma - Schulungsraum');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Vorraum');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Büro');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Umkleide');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Tanzraum');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Dojang');
INSERT INTO `ecg`.`orte` (`Bez`) VALUES ('Verein - Dojo');

# //-- Researchers
INSERT INTO `ecg`.`researchers` (`Bez`) VALUES ('Anna Stratmann');
INSERT INTO `ecg`.`researchers` (`Bez`) VALUES ('Ralph Breithaupt');
INSERT INTO `ecg`.`researchers` (`Bez`) VALUES ('Gerd Nolden');

# //-- Lagen
INSERT INTO `ecg`.`lagen` (`Bez`) VALUES ('liegend');
INSERT INTO `ecg`.`lagen` (`Bez`) VALUES ('sitzend');
INSERT INTO `ecg`.`lagen` (`Bez`) VALUES ('stehend');
INSERT INTO `ecg`.`lagen` (`Bez`) VALUES ('gehend');

# //-- States
INSERT INTO `ecg`.`states` (`Bez`) VALUES ('in Ruhe');
INSERT INTO `ecg`.`states` (`Bez`) VALUES ('beim Sport');
INSERT INTO `ecg`.`states` (`Bez`) VALUES ('direkt nach Sport');

# //-- Positionens
INSERT INTO `ecg`.`positions` (`Bez`) VALUES ('Brust normal');
INSERT INTO `ecg`.`positions` (`Bez`) VALUES ('Brust eng');
INSERT INTO `ecg`.`positions` (`Bez`) VALUES ('Handgelenke innen');
INSERT INTO `ecg`.`positions` (`Bez`) VALUES ('linkes Handgelenk');
INSERT INTO `ecg`.`positions` (`Bez`) VALUES ('Schläfen');

# //-- Algorithmen
INSERT INTO `ecg`.`algorithms` (`Bez`) VALUES ('Vorabtest Anna 1');
INSERT INTO `ecg`.`algorithms` (`Bez`) VALUES ('Choi 2016');

