namespace
{
namespace Message
{
// Message
const int MESSAGE_LENGTH = 20;

// Message header [MessType][ClientType][ClientID][ReqID]
const int REQUEST_ID_BYTE_POSITION = 3;
const int MESSAGETYPE_BYTE_POSITION = 0;

// standard header config
const int HEADER_LENGTH = 4;
const char REGISTER_REQ_HEADER[HEADER_LENGTH] = {0x01, 0x00, 0x00, 0x01};
const char DEFAULT_CARSTATE_REQ_HEADER[HEADER_LENGTH] = {0x01, 0x00, 0x00, 0x02};

// Body config
const int BODY_LENGTH = MESSAGE_LENGTH - HEADER_LENGTH;
const int CAR_STATE_LENGTH = 6;
const int CAR_STATE_BODY_LENGTH = 3;
const int CLEARANCE_BYTE_POSITION_IN_MESSAGE = 4;

// Message header [Position][Direction][Speed]
//char EXAMPLE_CARSTATE_REQ_BODY[CAR_STATE_LENGTH] = {0x1F, 0x90, 0x39, 0xD6, 0x01, 0x01};

// RequestType
const int REGISTER_REQ = 0x01;
const int CAR_STATE_REQ = 0x02;

// Response Type
const int NORMAL_RES = 0x12;
const int CONFIRMATION_RES = 0x11;
const int REJECT_RES = 0x10;

// RFID config
const int RFID_LENGTH = 4;

const char RFID[20][5][4] =
    {{{0x24, 0x89, 0xB3, 0x93}, {0x1B, 0x72, 0xE0, 0x23}, {0x1B, 0x5E, 0x23, 0x33}, {0x1A, 0xBB, 0x60, 0xC3}, {0x1B, 0xCC, 0x01, 0x03}}, //A0
     {{0x24, 0xA3, 0x53, 0x93}, {0x1B, 0x8F, 0xD7, 0x23}, {0x1B, 0x04, 0xB9, 0x03}, {0x1B, 0x50, 0x19, 0x03}, {0x1A, 0xA8, 0xD1, 0xF2}},
     {{0x24, 0x78, 0x36, 0x93}, {0x1B, 0xBE, 0x17, 0x13}, {0x1B, 0xA0, 0x71, 0x33}, {0x1B, 0x72, 0x12, 0x03}, {0x1A, 0x01, 0x4E, 0xA3}},
     {{0x24, 0x0C, 0x8D, 0x93}, {0x1B, 0x8F, 0xE2, 0x23}, {0x1B, 0x88, 0x9A, 0x23}, {0x1A, 0xFC, 0x62, 0xA3}, {0x1A, 0xA3, 0x2B, 0xA3}},
     {{0x24, 0xF1, 0xEA, 0x83}, {0x1B, 0xB7, 0x0D, 0x33}, {0x1B, 0x7D, 0xD0, 0x23}, {0x20, 0x2D, 0xFC, 0xD1}, {0x1A, 0x03, 0x3C, 0x93}},
     {{0x24, 0x9D, 0xD0, 0x83}, {0x1B, 0x8D, 0xDE, 0x03}, {0x1B, 0x2C, 0x61, 0x23}, {0x24, 0x29, 0xF9, 0x83}, {0x24, 0x80, 0x16, 0x93}},
     {{0x24, 0x4D, 0x4D, 0x93}, {0x1B, 0x47, 0x97, 0x23}, {0x1B, 0xE1, 0xFC, 0x23}, {0x24, 0x1A, 0x6B, 0x93}, {0x24, 0xAE, 0xCC, 0x93}},
     {{0x24, 0xDF, 0xC9, 0x93}, {0x20, 0x1E, 0x72, 0x61}, {0x1B, 0xDC, 0xD6, 0x23}, {0x24, 0xAE, 0xD5, 0x93}, {0x24, 0x35, 0x86, 0x93}},
     {{0x1F, 0xCB, 0x96, 0x66}, {0x20, 0xE9, 0x48, 0x51}, {0x1B, 0xFF, 0xFB, 0x13}, {0x24, 0xC3, 0xBD, 0x93}, {0x24, 0x2A, 0x1D, 0x93}}, //B0
     {{0x2B, 0x90, 0x89, 0x90}, {0x20, 0x14, 0x20, 0x51}, {0x1B, 0x11, 0xD7, 0x13}, {0x25, 0xA9, 0xC2, 0xB6}, {0x1F, 0x90, 0x39, 0xD6}},
     {{0x1F, 0xF3, 0x2A, 0xC6}, {0x2B, 0x9D, 0x25, 0xC0}, {0x1F, 0x42, 0x18, 0x66}, {0x2B, 0xA8, 0xB5, 0x45}, {0x24, 0x9D, 0xDA, 0x83}},
     {{0x1F, 0x6E, 0x1A, 0xA6}, {0x1F, 0x53, 0x65, 0x66}, {0x24, 0x52, 0x1E, 0x93}, {0x25, 0xF2, 0xFC, 0xF0}, {0x24, 0x4A, 0x99, 0x93}},
     {{0x1F, 0xB9, 0x42, 0x66}, {0x1F, 0xE9, 0x77, 0x66}, {0x1F, 0xE3, 0x38, 0x66}, {0x24, 0x70, 0x71, 0x93}, {0x24, 0x2F, 0x54, 0x93}},
     {{0x1F, 0x8B, 0x90, 0x66}, {0x1F, 0x25, 0xCD, 0x56}, {0x1F, 0xD6, 0x61, 0x66}, {0x24, 0x9F, 0x10, 0x93}, {0x24, 0xD1, 0x73, 0x93}},
     {{0x1F, 0x91, 0x85, 0x66}, {0x1F, 0xDC, 0x4E, 0x66}, {0x1F, 0xEC, 0xE5, 0x56}, {0x24, 0x4A, 0x09, 0x93}, {0x24, 0xAD, 0x71, 0x93}}, //C0
     {{0x1F, 0x1C, 0x16, 0x66}, {0x24, 0xC5, 0xE3, 0x83}, {0x1F, 0x1D, 0x2F, 0x66}, {0x1F, 0x01, 0x1B, 0xA6}, {0x2B, 0x30, 0xD4, 0x25}},
     {{0x24, 0x60, 0x8B, 0x93}, {0x1F, 0x6C, 0x82, 0x66}, {0x1F, 0x9F, 0xC9, 0x56}, {0x1F, 0xF1, 0x26, 0xC6}, {0x1F, 0xD6, 0xDC, 0x96}},
     {{0x1F, 0x06, 0x1B, 0xB6}, {0x24, 0x3E, 0x42, 0x93}, {0x1F, 0x01, 0x09, 0x66}, {0x2B, 0xA7, 0x41, 0x35}, {0x2B, 0x50, 0x85, 0x45}},
     {{0x24, 0x9D, 0xBE, 0x93}, {0x24, 0x58, 0x5C, 0x93}, {0x1F, 0xC3, 0xAB, 0x56}, {0x1F, 0x6F, 0x75, 0x66}, {0x1F, 0x35, 0x0C, 0x66}},
     {{0x21, 0x59, 0xE6, 0x62}, {0x24, 0xE6, 0x44, 0x93}, {0x1F, 0x01, 0x8E, 0x56}, {0x1F, 0xFB, 0xF8, 0x56}, {0x1F, 0x54, 0x32, 0x66}}};
// Message utils
bool isRegisterResponseFromServer(char *response)
{ //only first byte is different from request header
    return response[REQUEST_ID_BYTE_POSITION] == REGISTER_REQ && response[MESSAGETYPE_BYTE_POSITION] == NORMAL_RES;
}

bool isDrivePermissionResponseFromServer(char *response)
{ //only first byte is different from request header
    return response[REQUEST_ID_BYTE_POSITION] == CAR_STATE_REQ && response[MESSAGETYPE_BYTE_POSITION] == NORMAL_RES;
}
} // namespace Message
} // namespace