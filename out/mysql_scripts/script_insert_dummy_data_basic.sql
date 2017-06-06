# //Dummy-Daten in alle Datenbank eintragen: Grunddefinitionen
#
# //-- Diseases
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Koronare Herzkrankheit');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Angina Pectoris');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzklappendefekt');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzinfarkt');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzschwäche');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Myokarditis');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Tachykardie');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Bradykardie');

# //-- Orte
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Auto A8');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Zuhause - Arbeitszimmer');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Zuhause - Balkon');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Firma - Arb.platz Anna');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Firma - Kleines Büro');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Firma - Schulungsraum');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Vorraum');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Büro');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Umkleide');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Tanzraum');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Dojang');
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Dojo');

# //-- Researchers
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Anna Stratmann');
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Ralph Breithaupt');
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Gerd Nolden');

# //-- Lagen
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('liegend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('sitzend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('stehend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('gehend');

# //-- States
INSERT INTO `ecg`.`states` (`Name`) VALUES ('in Ruhe');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('in Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach leichter Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach mäßiger Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach viel Bewegung');

# //-- Positionens
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Brust normal');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Brust eng');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Handrücken');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Rücken');

# //-- Algorithmen
INSERT INTO `ecg`.`algrpeaks` (`Name`) VALUES ('rpeaksAnna');
INSERT INTO `ecg`.`algrpeaks` (`Name`) VALUES ('rpeaksChoi');

INSERT INTO `ecg`.`algfeatures` (`Name`) VALUES ('featChoi');
INSERT INTO `ecg`.`algfeatures` (`Name`) VALUES ('featRandomPoints');

