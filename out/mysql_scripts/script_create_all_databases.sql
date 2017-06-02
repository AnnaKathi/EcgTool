CREATE DATABASE `ecg`

USE `ecg`

CREATE TABLE AlgRpeaks (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE AlgFeatures (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE Diseases (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE Features (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  ECGData_ID INTEGER UNSIGNED NOT NULL,
  AlgRpeaks_ID INTEGER UNSIGNED NOT NULL,
  AlgFeatures_ID INTEGER UNSIGNED NOT NULL,
  Features VARCHAR(1024) NOT NULL,
  PRIMARY KEY(ID),
  INDEX Features_FKIndex1(AlgRpeaks_ID),
  INDEX Features_FKIndex2(AlgFeatures_ID),
  INDEX Features_FKIndex3(ECGData_ID)
)

CREATE TABLE Lagen (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE Orte (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE Positions (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE Researchers (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE SessionResearchers (
  Sessions_ID INTEGER UNSIGNED NOT NULL,
  Researchers_ID INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY(Sessions_ID, Researchers_ID),
  INDEX Sessions_has_Researchers_FKIndex1(Sessions_ID),
  INDEX Sessions_has_Researchers_FKIndex2(Researchers_ID)
)

CREATE TABLE Sessions (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Orte_ID INTEGER UNSIGNED NOT NULL,
  Stamp DATETIME NOT NULL,
  Kommentar LONGTEXT NULL,
  PRIMARY KEY(ID),
  INDEX Sessions_FKIndex1(Orte_ID)
)

CREATE TABLE States (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Bez VARCHAR(50) NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE SubDiseases (
  Subjects_ID INTEGER UNSIGNED NOT NULL,
  Diseases_ID INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY(Subjects_ID, Diseases_ID),
  INDEX Subjects_has_Diseases_FKIndex1(Subjects_ID),
  INDEX Subjects_has_Diseases_FKIndex2(Diseases_ID)
)

CREATE TABLE Subjects (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Vorname VARCHAR(50) NOT NULL,
  Nachname VARCHAR(50) NOT NULL,
  Age INTEGER UNSIGNED NOT NULL,
  Sex BOOL NOT NULL,
  PRIMARY KEY(ID)
)

CREATE TABLE ECGData (
  ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  Sessions_ID INTEGER UNSIGNED NOT NULL,
  Subjects_ID INTEGER UNSIGNED NOT NULL,
  Positions_ID INTEGER UNSIGNED NOT NULL,
  States_ID INTEGER UNSIGNED NOT NULL,
  Lagen_ID INTEGER UNSIGNED NOT NULL,
	Werte LONGTEXT NOT NULL,
  PRIMARY KEY(ID),
  INDEX ECGData_FKIndex2(Lagen_ID),
  INDEX ECGData_FKIndex3(States_ID),
  INDEX ECGData_FKIndex4(Positions_ID),
  INDEX ECGData_FKIndex5(Subjects_ID),
  INDEX ECGData_FKIndex6(Sessions_ID)
)

