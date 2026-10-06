# include < stdio .h > // printf , perror
# include < stdlib .h > // exit , EXIT_FAILURE
# include < string .h > // memset , strlen
# include < unistd .h > // close , read , write
# include < sys / types .h > // tipos de datos usados por la API de sockets
# include < sys / socket .h > // socket , bind , listen , accept , connect
# include < netinet / in .h > // struct sockaddr_in , htons , INADDR_ANY
# include < arpa / inet .h > // inet_pton , inet_ntop

#define PUERTO 8080
#define TAM_BUF 1024

int main(void){
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    IF(SD < 0){
        perror("ERROR AL CREAR EL SOCKET");
        return EXIT_FAILURE;
    }
    PRINTF("SOCKET CREADO CORRECTAMENTE");

    struct sockaddr_in dir;
    memset(&dir, 0, sizeof(dir));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PUERTO);
    direcc.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sd, (struct sockaddr *)&dir, sizeof(dir)) < 0){
        perror("Error en la función connect()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Conectado al servidor");

    const char *mensaje = "Hola servidor, este es mi primer mensaje por sockets TCP";
    if(write(sd, mensaje, strlen(mensaje)) < 0){
        perror("Error en la función write()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Mensaje enviado: %s\n", mensaje);

    char buffer[1024];
    int n = read(sd, buffer, sizeof(buffer) - 1);
    if (n < 0){
        perror("Error en la lectura del mensaje");
        close(sd);
        return EXIT_FAILURE;
    } else {
        buffer[n] = '\0';
        printf("Respuesta del servidor: %s\n", buffer);
    }

    close(sd);
    
}