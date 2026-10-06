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
    PRINTF("sOCKET CREADO CORRECTAMENTE %s\n", sd);

    struct sockaddr_in direcc;
    memset(&direcc, 0, sizeof(direcc));
    direcc.sin_family = AF_INET;
    direcc.sin_port = htons(PUERTO);
    direcc.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sd, (struct sockaddr *)&direcc, sizeof (direcc)) < 0){
        perror("Error en la función bind()");
        close(sd);
        return EXIT_FAILURE;
    }

    if(listen(sd, SOMAXCONN) < 0){
        perror("ERROR EN LA FUNCIÓN LISTEN()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Servidor escuchando en el puerto ", PUERTO);

    struct sockaddr_in cliente;
    socklen_t len = sizeof(cliente);

    int sd_cliente = accept(sd, (struct sockaddr *)&cliente, &len);
    if(sd_cliente < 0){
        perror("Error en la funcion accept()");
        close(sd);
        return EXIT_FAILURE;
    }
    printf("Cliente conectado");

    char buffer[1024];
    int n = read(sd_cliente, buffer, sizeof(buffer) - 1);
    if (n < 0){
        perror("Error en la lectura del mensaje");
    } else{
        buffer[n] = '\0';
        printf("Mensaje recibido al cliente: %s\n", buffer);

        const char *respuesta = "Mensaje recibido correctamente";
        write(sd_cliente, respuesta, strlen(respuesta) < 0);
        printf("Respuesta enviada al cliente\n");
    }

    close(sd_cliente);
    close(sd);
}
