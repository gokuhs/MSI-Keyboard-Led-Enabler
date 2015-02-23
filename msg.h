typedef struct msg {
        long type;
        char  val[6] ="\0"; //0-> modo 1-> color i 2-> color c 3-> color d 4-> intensidad

} MSG;

void sendMesage(char * mensaje);
void ReadMesage(char * mensaje);