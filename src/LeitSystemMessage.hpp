namespace {
    namespace Message{
        // Message 
        const int MESSAGE_LENGTH = 20;

        // Message header [MessType][ClientType][ClientID][ReqID]
        const int REQUEST_ID_POSITION = 3;

        // standard header config 
        const int HEADER_LENGTH = 4;
        const char REGISTER_REQ_HEADER[HEADER_LENGTH] = {0x01,0x00,0x00,0x01};
        const char DEFAULT_CARSTATE_REQ_HEADER[HEADER_LENGTH] = {0x01,0x00,0x00,0x02};

        // Body config
        const int BODY_LENGTH = MESSAGE_LENGTH - HEADER_LENGTH;
        const int CAR_STATE_BODY_LENGTH = 3;

        // Message header [Position][Direction][Speed]        
        char EXAMPLE_CARSTATE_REQ_BODY[CAR_STATE_BODY_LENGTH] = {0xA1,0x01,0x01};

        // RequestType
        const int REGISTER_REQ = 0x01;

        // Message utils
        bool isResponseFromServer(char* response){ //only first byte is different from request header
            return response[REQUEST_ID_POSITION] == REGISTER_REQ;
        }
    }
}