//
// Created by Kenneth Dow on 28/11/21.
//

#include "OscMessageAdapter.h"

OscMessageAdapter::OscMessageAdapter(OSCMessage &message) : _message(message) {

}

bool OscMessageAdapter::dispatch(RecipientAddress &address) {
    if (_message.fullMatch(address.pattern, address.offset)) {
        address.callback(address.context, *this, address.offset);
        return true;
    } else {
        return false;
    }
}

bool OscMessageAdapter::route(RecipientAddress &address) {
    int match_offset = _message.match(address.pattern, address.offset);
    if (match_offset > 0) {
        address.callback(address.context, *this, match_offset + address.offset);
        return true;
    } else {
        return false;
    }
}

uint8_t OscMessageAdapter::getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset) {
    char addr[32];
    uint8_t DefaultOffset = 1; //offset to account for "/"
    uint8_t NewOffset = DefaultOffset + offset;
    _message.getAddress(addr, NewOffset);
    //Serial.printf("Address received at getAddressAsUint8_t: %s\n", addr);

    Handle = atoi(addr);
    //Serial.printf("Handle received:  %i\n", Handle);

    NewOffset++;
    if (Handle > 9) { NewOffset++; } //number of digits
    if (Handle > 99) { NewOffset++; }

    return NewOffset;
}

void OscMessageAdapter::empty() {
    _message.empty();
}

void OscMessageAdapter::fill(uint8_t byteStream) {
    _message.fill(byteStream);
}

bool OscMessageAdapter::fullMatch(const char *pattern, int offset) {
    return _message.fullMatch(pattern, offset);
}

bool OscMessageAdapter::hasError() {
    return _message.hasError();
}

int OscMessageAdapter::getDataLength(int position) {
    return _message.getDataLength(position);
}

int32_t OscMessageAdapter::getInt(int position) {
    return _message.getInt(position);
}

int OscMessageAdapter::getString(int position, char *buffer, int length) {
    return _message.getString(position, buffer, length);
}

bool OscMessageAdapter::isInt(int sample) {
    return _message.isInt(sample);
}

bool OscMessageAdapter::isString(int position) {
    return _message.isString(position);
}

void OscMessageAdapter::send(WiFiUDP &udp) {
    _message.send(udp);
}

bool OscMessageAdapter::setAddress(const char *_address) {
    char * addressMemory = (char *) malloc( (strlen(_address) + 1) * sizeof(char) );
    if (addressMemory == NULL) {
        Serial.println("malloc in Adapter->setAddress failed");
    }
    _message.setAddress(_address);
    if(_message.hasError()) {
        Serial.println(_message.getError());
        return false;
    }
    return true;
}

int OscMessageAdapter::match(const char *pattern, int offset) {
    return _message.match(pattern, offset);

}


















