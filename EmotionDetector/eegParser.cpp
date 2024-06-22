#include "eegParser.hpp"

eegParser::eegParser() {

}

eegParser::~eegParser() {

}

// Functions

int eegParser::parseData() {
    this->openCOMPort();
    this->configurePortSettings();
    while (true) {
        if (this->handleRawData()) {
            this->convertData();
        } else {
            this->closeCOMPort();
        }
    }
    // TO DO: add closeCOMPort function;
}

int eegParser::openCOMPort() {
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open COM port!" << std::endl;
        return 1;
    }
}

int eegParser::configurePortSettings() {

    dcbSerialParams.DCBlength = l;

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to get COM port state!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = baud_rate;
    dcbSerialParams.ByteSize = data_size;
    dcbSerialParams.StopBits = stop_bits;
    dcbSerialParams.Parity = parity;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to configure COM port!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
}

int eegParser::readData() {
    if (!ReadFile(hSerial, raw_data_buffer, sizeof(raw_data_buffer), &raw_bytes_read, NULL) || !ReadFile(hSerial, eeg_data_buffer, sizeof(eeg_data_buffer), &eeg_bytes_read, NULL)) {
        std::cerr << "Failed to read from COM port." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    // TO DO: fill both buffers
    // TO DO: identify type of pack
}

bool eegParser::handleRawData() {
    this->readData();
    // TO DO: check every checksum
}

void eegParser::convertData() {
    this->readData();
    // TO DO: convert eeg data
    std::cout << "Data read from COM port (hex): ";
    for (DWORD i = 0; i < eeg_bytes_read; i++) {
        std::cout << std::hex << (int) eeg_data_buffer[i] << " ";
    }
}

int eegParser::closeCOMPort() {
    CloseHandle(hSerial);
    return 0;
}
