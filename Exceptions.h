#pragma once
class Exceptions
{
public: std::string error = "";
};

class InputFileError : public Exceptions
{
public: std::string error = "";
};

class ShipDataInvalid : public InputFileError
{
public: std::string error = "\nThe input file contains invalid ship data!\nPlease ensure that the data on the file is valid before restarting the program!\n\n";
};

class FileNotFound : public InputFileError
{
public: std::string error = "\nThe input file could not be found and/or opened!\nPlease ensure that the file exists and has read/write privileges!\n\n";
};

class ItemOutOfBounds : public InputFileError
{
public: std::string error = "The input file could not be found and/or opened!";
};

class ObjectCollisionDetected : public InputFileError
{
public: std::string error = "The input file could not be found and/or opened!";
};

class MissingObjects : public InputFileError
{
public: std::string error = "\nThe input file is missing ships or ship data!\nPlease ensure that there are 5 ships in the input csv file.\n\n";
};