#pragma once

#include <iostream>
#include <windows.h>

class eegParser {
public:
	eegParser();

	virtual ~eegParser();

	// Functions
	int parseData();

	int openCOMPort();

	int configurePortSettings();

	int readData();

	bool handleRawData();

	void convertData();

	int closeCOMPort();

private:

	// Create file function

	HANDLE hSerial = CreateFile(L"\\\\.\\COM4", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Configure the COM port settings

	DCB dcbSerialParams = { 0 };
	int l = sizeof(dcbSerialParams);
	int baud_rate = CBR_57600;  // Set the baud rate
	int data_size = 8;          // Set the data size
	int stop_bits = 16;			// Set the stop bits
	DWORD parity = NOPARITY;    // Disable parity checking

	// Read data

	BYTE raw_data_buffer[4096];
	BYTE eeg_data_buffer[179];
	DWORD raw_bytes_read;
	DWORD eeg_bytes_read;
};

