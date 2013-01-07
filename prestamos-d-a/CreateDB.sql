GRANT SELECT, INSERT, UPDATE, DELETE ON *.* TO 'php'@'localhost' IDENTIFIED BY 'f00';

CREATE DATABASE IF NOT EXISTS DALoans;

USE DALoans;

CREATE TABLE Users(name VARCHAR(16) NOT NULL PRIMARY KEY, password VARCHAR(64) NOT NULL);

CREATE TABLE Loans(auto_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, loan_date INT UNSIGNED NULL, return_date INT UNSIGNED NULL, client VARCHAR(64) NOT NULL, lender VARCHAR(64) NOT NULL REFERENCES Usuarios(nombre), item VARCHAR(64) NOT NULL, type VARCHAR(64) NULL);

INSERT INTO Users VALUES("jairo", password("bruno roco"));
INSERT INTO Users VALUES("pilar", password("bruno roco"));
INSERT INTO Users VALUES("alejandro", password("bruno roco"));
INSERT INTO Users VALUES("juan", password("bruno roco"));
INSERT INTO Users VALUES("edgar", password("bruno roco"));
INSERT INTO Users VALUES("marian", password("bruno roco"));