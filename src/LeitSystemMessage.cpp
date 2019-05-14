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
const int CAR_STATE_BODY_LENGTH = 3;
const int CLEARANCE_BYTE_POSITION_IN_MESSAGE = 4;

// Message header [Position][Direction][Speed]
char EXAMPLE_CARSTATE_REQ_BODY[CAR_STATE_BODY_LENGTH] = {0xA1, 0x01, 0x01};

// RequestType
const int REGISTER_REQ = 0x01;
const int CAR_STATE_REQ = 0x02;

// Response Type
const int NORMAL_RES = 0x12;
const int CONFIRMATION_RES = 0x11;
const int REJECT_RES = 0x10;

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