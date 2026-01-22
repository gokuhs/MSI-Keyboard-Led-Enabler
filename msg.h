typedef struct msg
{
        long type;
        char val[6] = "\0"; // 0-> modo 1-> color i 2-> color c 3-> color d 4-> intensidad

} MSG;

void sendMessage(char *mensaje);
bool readMessage(char *mensaje, bool blocking);