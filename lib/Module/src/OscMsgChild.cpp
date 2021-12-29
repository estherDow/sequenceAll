//
// Created by Kenneth Dow on 28/11/21.
//

#include "OscMsgChild.h"

OscMsgChild::OscMsgChild(OSCMessage &message) : _message(message) {

}

bool OscMsgChild::dispatch(RecipientAddress &address) {
    if (_message.fullMatch(address.pattern, address.offset)) {
        address.callback(address.context, *this, address.offset);
        return true;
    } else {
        return false;
    }
}

bool OscMsgChild::route(RecipientAddress &address) {
    int match_offset = _message.match(address.pattern, address.offset);
    if (match_offset > 0) {
        address.callback(address.context, *this, match_offset + address.offset);
        return true;
    } else {
        return false;
    }
}

uint8_t OscMsgChild::getAddressAsUint8_t(uint8_t &Handle, uint8_t &offset) {
    char addr[32];
    uint8_t DefaultOffset = 1; //offset to account for "/"
    uint8_t NewOffset = DefaultOffset + offset;
    _message.getAddress(addr, NewOffset);
    Serial.printf("Address received at getAddressAsUint8_t: %s\n", addr);

    Handle = atoi(addr);
    Serial.printf("Handle received:  %i\n", Handle);

    NewOffset++;
    if (Handle > 9) { NewOffset++; } //number of digits
    if (Handle > 99) { NewOffset++; }

    return NewOffset;
}

void OscMsgChild::empty() {
    _message.empty();
}

void OscMsgChild::fill(uint8_t byteStream) {
    _message.fill(byteStream);
}

bool OscMsgChild::fullMatch(const char *pattern, int offset) {
    return _message.fullMatch(pattern, offset);
}

bool OscMsgChild::hasError() {
    return _message.hasError();
}

int OscMsgChild::getDataLength(int position) {
    return _message.getDataLength(position);
}

int32_t OscMsgChild::getInt(int position) {
    return _message.getInt(position);
}

int OscMsgChild::getString(int position, char *buffer, int length) {
    return _message.getString(position, buffer, length);
}

bool OscMsgChild::isInt(int sample) {
    return _message.isInt(sample);
}

bool OscMsgChild::isString(int position) {
    return _message.isString(position);
}

void OscMsgChild::send(WiFiUDP &udp) {
    _message.send(udp);
}


















