
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PORT 2024

extern int errno;

int main ()
{
    struct sockaddr_in server;  // structura folosita de server
    struct sockaddr_in from;
    char msg[100];      //mesajul primit de la client
    char msgrasp[100]=" ";        //mesaj de raspuns pentru client
    int sd, contor_secundar;         //descriptorul de socket

    /* crearea unui socket */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("[server]Eroare la socket().\n");
        return errno;
    }

    /* pregatirea structurilor de date */
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));

    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;
    /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    /* utilizam un port utilizator */
    server.sin_port = htons (PORT);

    /* atasam socketul */
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
        perror ("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen (sd, 1) == -1)
    {
        perror ("[server]Eroare la listen().\n");
        return errno;
    }

    /* servim in mod concurent clientii... */
    while (1)
    {
        int client;
        int length = sizeof (from);

        printf ("[server]Asteptam la portul %d...\n",PORT);
        fflush (stdout);

        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        client = accept (sd, (struct sockaddr *) &from, &length);

        /* eroare la acceptarea conexiunii de la un client */
        if (client < 0)
        {
            perror ("[server]Eroare la accept().\n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            close(client);
            continue;
        } else if (pid > 0) {
            // parinte
            close(client);
            while(waitpid(-1,NULL,WNOHANG));
            continue;
        } else 
        if (pid == 0) {
            // copil

            close(sd);
            int ok = 0, okn,oke,okp,stop;
            char verifica [1000],punct[3];
            punct[0]='.';
            punct[1]='\0';
//verific daca face login sau creare cont..................................................................................................
            char flag[100];

            bzero (flag, 100);
            printf ("[server]\n");
            fflush (stdout);

            if (read (client, flag, 100) <= 0)
            {
                perror ("[server]Eroare la read() de la client.\n");
                continue;       
            }
            printf("[server]Acesta ese mesajul %s\n",flag);

// Program Login...............................................................................................................................
            contor_secundar = 0;
            while(ok == 0 && strcmp (flag,"/Login") == 0) {

            okn = oke = okp = 0;
            if(contor_secundar != 0)
            {
                bzero (msg, 100);
                printf ("[server]Asteptam sa vedem daca reincercam logarea...\n");
                fflush (stdout);
                if (read (client, msg, 100) <= 0)
                    {
                        perror ("[server]Eroare la read() de la client.\n");
                        continue;       
                    }
                if(strcmp(msg,"Da") == 0 )
                    strcpy(flag,"/Creare_cont");
            }
            if(strcmp (flag,"/Creare_cont") == 0)
                break;

            bzero (msg, 100);
            printf ("[server]Asteptam numele...\n");
            fflush (stdout);

            if (read (client, msg, 100) <= 0)
            {
                perror ("[server]Eroare la read() de la client.\n");
                continue;       
            }

            bzero(verifica,1000);
            stop = 0;

            strcpy(verifica, msg);
            strcat(verifica, punct);
            bzero (msg, 100);
            printf ("[server]Asteptam emailul...\n");
            fflush (stdout);
            if (read (client, msg, 100) <= 0)
            {
                perror ("[server]Eroare la read() de la client.\n");
                close (client); 
                continue;       
            }
            strcat(verifica, msg);
            strcat(verifica, punct);
            bzero (msg, 100);
            printf ("[server]Asteptam parola...\n");
            fflush (stdout);
            if (read (client, msg, 100) <= 0)
            {
                perror ("[server]Eroare la read() de la client.\n");
                close (client); 
                continue;       
            }
             msg[strlen(msg) - 1 ] = '\0';
            strcat(verifica, msg);
            printf ("[server]Datele au fost receptionate...%s\n", verifica);
            
            stop = 0;

            FILE *f;
            char intrare[10000];
            f = fopen("useriemailparole.txt", "r");
            while(fgets(intrare,10000,f) != NULL)
            {
                if(strstr(intrare,verifica) != NULL)
                {
                    stop = 1;
                    break;
                }
            }
            fclose(f);

            if(stop == 1)
              {
                    bzero (msgrasp, 100);
                    msgrasp[0]='1';
                    msgrasp[1]='\0';
              }
            else
                {
                    bzero (msgrasp, 100);
                    msgrasp[0]='0';
                    msgrasp[1]='\0';
                }

            intrare[0]='\0';

            printf("[server]Trimitem mesajul inapoi...%s\n",msgrasp);

            if (write (client, msgrasp, 100) <= 0)
            {
                perror ("[server]Eroare la write() catre client.\n");
                continue;       
            }
            else
                printf ("[server]Mesajul a fost trasmis cu succes.\n");

            ok = atoi(msgrasp);
            contor_secundar++;
        }  
//Creare cont****************************************************************************************************************************************************
            if(strcmp (flag,"/Creare_cont") == 0  ){

            verifica[0] = '\0';
//Nume...................................................................................................................................................
            int stop = 0;
            FILE *f;

            while(stop == 0)
            {
                if (read (client, msg, 100) <= 0)
                {
                    perror ("[server]Eroare la read() de la client.\n");
                    close (client); 
                    continue;       
                }

                stop = 1;
                char intrare[10000];
                f = fopen("username.txt", "r");
                while(fgets(intrare,10000,f) != NULL)
                {
                    if(strstr(intrare,msg) != NULL)
                    {
                        stop = 0;
                        break;
                    }
                }
                fclose(f);
                // printf("***\n");
                    
                if(stop == 1)
                {
                    strcpy(verifica, msg);
                    strcat(verifica, punct);
                    f = fopen("username.txt", "a");
                    fprintf(f, "%s\n",msg);
                    fclose(f);

                    msgrasp[0] = '1';
                    msgrasp[1] = '\0';
                    if (write (client, msgrasp, 100) <= 0)
                    {
                        perror ("[server]Eroare la write() catre client.\n");
                        continue;       
                    }

                }
                else
                {
                    msgrasp[0] = '0';
                    msgrasp[1] = '\0';
                    if (write (client, msgrasp, 100) <= 0)
                    {
                        perror ("[server]Eroare la write() catre client.\n");
                        continue;       
                    }

                }


            }
            stop = 0;
//EMAIL*********************************************************************************
              while(stop == 0)
            {

                if (read (client, msg, 100) <= 0)
                {
                    perror ("[server]Eroare la read() de la client.\n");
                    close (client); 
                    continue;       
                }

                stop = 1;
                char intrare[10000];
                f = fopen("passw.txt", "r");
                while(fgets(intrare,10000,f) != NULL)
                {
                    if(strstr(intrare,msg) != NULL)
                    {
                        stop = 0;
                        break;
                    }
                }
                fclose(f);
                // printf("***\n");
                    
                if(stop == 1)
                {
                    strcat(verifica, msg);
                    strcat(verifica, punct);
                    f = fopen("passw.txt", "a");
                    fprintf(f, "%s\n",msg);
                    fclose(f);
                    msgrasp[0] = '1';
                    msgrasp[1] = '\0';
                    if (write (client, msgrasp, 100) <= 0)
                    {
                        perror ("[server]Eroare la write() catre client.\n");
                        continue;       
                    }


                }
                else
                {
                    msgrasp[0] = '0';
                    msgrasp[1] = '\0';
                    if (write (client, msgrasp, 100) <= 0)
                    {
                        perror ("[server]Eroare la write() catre client.\n");
                        continue;       
                    }

                }


            }
            stop = 0;

            if (read (client, msg, 100) <= 0)
                {
                    perror ("[server]Eroare la read() de la client.\n");
                    close (client); 
                    continue;       
                }
            printf("[client]Parola este: %s\n",msg);


            
            strcat(verifica, msg);
            printf("[server]Astea sunt datele: %s \n", verifica);
            f = fopen("useriemailparole.txt", "a");
            fprintf(f, "%s\n",verifica);
            fclose(f);
        }
//Citest numele userului
        char nume_final[100];
        read(client, nume_final,100);
//Am terminat de citit
        char flagR[100];
        int rasp;

//Intru in logica comenzii
        while(1){
        //Citest flag-ul
        read(client,flagR,100);
        rasp = atoi(flagR);
        printf("%s",flagR);
            if(rasp == 1) //Daca e  /Afiseaza_conversatie
            {
                printf("****");
                int stop = 0;
                char nick[100];

                while(stop != 1)
                {
                    read(client,nick,100); //Citest un nume
                    FILE * f;

                    f = fopen("username.txt", "r");
                    char intrare[10000];
                    
                    while(fgets(intrare,10000,f) != NULL)
                    {
                        if(strstr(intrare,nick) != NULL)
                        {
                            stop = 1;
                            break;
                        }
                    }
                    fclose(f);

                    if(strcmp(nume_final,nick) == 0)
                    {
                        msg[0]='1';
                        msg[1]='\0';
                        write(client,msg,100);
                        stop = 3;
                    }
                    else
                        if(stop == 1)
                        {
                            msg[0]='2';
                            msg[1]='\0';
                            write(client,msg,100);
                        }
                        else
                        {
                            msg[0]='3';
                            msg[1]='\0';
                            write(client,msg,100);
                            stop = 2;
                        }

                }
                
                char creare_fisier[1000],intrare[1000];
               read(client,creare_fisier,1000);
               printf("%s\n",creare_fisier);
               FILE * f = fopen(creare_fisier,"a");
               fclose(f);
               FILE * fin = fopen(creare_fisier,"r");
               int opreste = 0;
                while(fgets(intrare,10000,fin) != NULL)
                    {
                        write(client, intrare,1000);
                        printf("%s\n",intrare );
                    }
                intrare[0]='1';
                intrare[1]='\0';
                 printf("%s\n",intrare );


                write(client, intrare,1000);
                fclose(fin);


                   
            }
            if(rasp == 2) //Daca e  /Afiseaza_conversatie
            {
                //printf("****");
                int stop = 0;
                char nick[100];

                while(stop != 1)
                {
                    read(client,nick,100); //Citest un nume
                    FILE * f;

                    f = fopen("username.txt", "r");
                    char intrare[10000];
                    
                    while(fgets(intrare,10000,f) != NULL)
                    {
                        if(strstr(intrare,nick) != NULL)
                        {
                            stop = 1;
                            break;
                        }
                    }
                    fclose(f);

                    if(strcmp(nume_final,nick) == 0)
                    {
                        msg[0]='1';
                        msg[1]='\0';
                        write(client,msg,100);
                        stop = 3;
                    }
                    else
                        if(stop == 1)
                        {
                            msg[0]='2';
                            msg[1]='\0';
                            write(client,msg,100);
                        }
                        else
                        {
                            msg[0]='3';
                            msg[1]='\0';
                            write(client,msg,100);
                            stop = 2;
                        }

                }
                
               char creare_fisier[1000],creare_fisier_secundar[1000],intrare[1000];
               read(client,creare_fisier,1000);
               read(client,creare_fisier_secundar,1000);
               printf("%s\n",creare_fisier);
               printf("%s\n",creare_fisier_secundar);

               read(client,msg,100);
               
                FILE * fin_secundar;
                fin_secundar =  fopen(creare_fisier,"a");
                fclose(fin_secundar);
                
                FILE * fin = fopen(creare_fisier,"a");
                fprintf(fin,"[");
                fprintf(fin,"%s",nume_final);
                fprintf(fin,"]");
                fprintf(fin,": ");
                fprintf(fin, "%s\n",msg);
                fclose(fin);
                printf("\n");

                fin_secundar =  fopen(creare_fisier_secundar,"a");
                fclose(fin_secundar);
                
                fin = fopen(creare_fisier_secundar,"a");
                fprintf(fin,"[");
                fprintf(fin,"%s",nume_final);
                fprintf(fin,"]");
                fprintf(fin,": ");
                fprintf(fin, "%s\n",msg);
                fclose(fin);
                printf("\n");

                char auxiliar[100],aux_msg[20],nume_scriere[100];
                strcpy(auxiliar,"[");
                strcat(auxiliar,nume_final);
                strcat(auxiliar,"]: ");

                for(int i = 0; i < 15; i++)
                {
                    if(i > strlen(msg) - 1 )
                    {
                        aux_msg[i] = '\0';
                        break;
                    }
                    else
                        aux_msg[i] = msg[i];
                }
                strcpy(nume_scriere,nick);

                printf("%s\n",aux_msg);
                strcat(nume_scriere,".txt");
                fin = fopen(nume_scriere,"a");
                fprintf(fin,"%s",auxiliar);
                fprintf(fin,"%s",aux_msg);
                fprintf(fin,"...");
                fprintf(fin,"\n");
                fprintf(fin,"\n");
                fclose(fin);




                   
            }
             if(rasp == 3) //Daca e  /Afiseaza_conversatie
            {
               
                int stop = 0;
                char nick[100];

                while(stop != 1)
                {
                    read(client,nick,100); //Citest un nume
                    FILE * f;

                    f = fopen("username.txt", "r");
                    char intrare[10000];
                    
                    while(fgets(intrare,10000,f) != NULL)
                    {
                        if(strstr(intrare,nick) != NULL)
                        {
                            stop = 1;
                            break;
                        }
                    }
                    fclose(f);

                    if(strcmp(nume_final,nick) == 0)
                    {
                        msg[0]='1';
                        msg[1]='\0';
                        write(client,msg,100);
                        stop = 3;
                    }
                    else
                        if(stop == 1)
                        {
                            msg[0]='2';
                            msg[1]='\0';
                            write(client,msg,100);
                        }
                        else
                        {
                            msg[0]='3';
                            msg[1]='\0';
                            write(client,msg,100);
                            stop = 2;
                        }

                }
                
               char creare_fisier[1000],intrare[1000];
               read(client,creare_fisier,1000);
               printf("%s\n",creare_fisier);
               FILE * f = fopen(creare_fisier,"w");
              fclose(f);
                   
            }

            if(rasp == 4) //Daca e  /Afiseaza_conversatie
            {
                printf("****");
                int stop = 0;
                char nick[100];
                char intrare[1000];
               FILE * fin = fopen("username.txt","r");
               int opreste = 0;
                while(fgets(intrare,10000,fin) != NULL)
                    {
                        write(client, intrare,1000);
                        printf("%s\n",intrare );
                    }
                intrare[0]='1';
                intrare[1]='\0';
                write(client, intrare,1000);
                fclose(fin);



                   
            }
            if(rasp == 5)
            {
                char sunt_obosit[1000];
                char creare_fisier[1000],intrare[1000];
               read(client,creare_fisier,1000);
               printf("%s\n",creare_fisier);
               FILE * f = fopen(creare_fisier,"a");
               fclose(f);
               FILE * fin = fopen(creare_fisier,"r");
               int opreste = 0;
                while(fgets(intrare,10000,fin) != NULL)
                    {
                        write(client, intrare,1000);
                        printf("%s\n",intrare );
                    }
                intrare[0]='1';
                intrare[1]='\0';
                 printf("%s\n",intrare );

                write(client, intrare,1000);
                fclose(fin);

                f = fopen(creare_fisier,"a");
                fclose(f);

                f = fopen(creare_fisier,"w");
                fclose(f);
            }



        }

            close (client);
            exit(0);
        }

    }               /* while */
}               /* main */