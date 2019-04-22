namespace {
    namespace Message{
        // 
        const int MESSAGE_LENGTH = 20;

        // standard header config
        const int HEADER_LENGTH = 4;
        const char REGISTER_REQ_HEADER[HEADER_LENGTH] = {0x01,0x00,0x00,0x01};

        // Body config
        const int BODY_LENGTH = MESSAGE_LENGTH - HEADER_LENGTH;

        // Message utils
        bool isResponseFromServer(char* response){ //only first byte is different from request header
            if(response[0]==REGISTER_REQ_HEADER[0]) return false;
            for (int i = 1; i < HEADER_LENGTH; i++)
            {
                if (response[i]!=REGISTER_REQ_HEADER[i])
                {
                    return false;
                }
                
            }
            return true;
        }
    }
}