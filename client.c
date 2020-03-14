#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
void criptare(char sir[100]){

  for(int i=0;i<strlen(sir);i++)
  {
    switch(sir[i])
    {
      case 'a':
      sir[i]='t';
      break;
      case 'b':
      sir[i]='z';
      break;
      case 'c':
      sir[i]='p';
      break;
      case 'd':
      sir[i]='m';
      break;
      case 'e':
      sir[i]='j';
      break;
      case 'f':
      sir[i]='e';
      break;
      case 'g':
      sir[i]='q';
      break;
      case 'h':
      sir[i]='o';
      break;
      case 'i':
      sir[i]='f';
      break;
      case 'j':
      sir[i]='n';
      break;
      case 'k':
      sir[i]='g';
      break;
      case 'l':
      sir[i]='d';
      break;
      case 'm':
      sir[i]='l';
      break;
      case 'n':
      sir[i]='i';
      break;
      case 'o':
      sir[i]='c';
      break;
      case 'p':
      sir[i]='w';
      break;
      case 'q':
      sir[i]='a';
      break;
      case 'r':
      sir[i]='y';
      break;
      case 's':
      sir[i]='v';
      break;
      case 't':
      sir[i]='u';
      break;
      case 'u':
      sir[i]='s';
      break;
      case 'v':
      sir[i]='k';
      break;
      case 'w':
      sir[i]='x';
      break;
      case 'x':
      sir[i]='h';
      break;
      case 'y':
      sir[i]='b';
      break;
      case 'z':
      sir[i]='r';
      break;
      default:
      sir[i]=sir[i];
      break;
    }
  }
}

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
  int sd;     // descriptorul de socket
  struct sockaddr_in server;  // structura folosita pentru conectare 
  char msg[100];    // mesajul trimis
  char nume_final[100];
  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons (port);
  
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

    int ok = 0, contor = 0;

  printf(ANSI_COLOR_YELLOW "[client]Doriti sa va logati sau sa va inregistrati ?" ANSI_COLOR_RESET "\n" );
  printf(ANSI_COLOR_YELLOW "[client]Pentru a va loga introduceti comanda: " ANSI_COLOR_RED "/Login" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW "[client]Pentru a va inregistra introduceti comanda: " ANSI_COLOR_RED "/Creare_cont" ANSI_COLOR_RESET "\n");
  
  int flagL = 0,flagI =0 , contor_secundar=0, Login = 0, Inregistrare = 0;

  while(flagL == 0 && flagI == 0)
    {
      if(contor_secundar != 0)
        printf(ANSI_COLOR_RED "[client]Ati introdus o comanda gresita!" ANSI_COLOR_RESET "\n");
      bzero (msg, 100);
      printf(ANSI_COLOR_BLUE "[client]Comanda: " ANSI_COLOR_RESET);
      fflush (stdout);
      read (0, msg, 100);
      msg[strlen(msg) - 1 ] = '\0';
      if(strcmp(msg,"/Login") == 0)
        flagL = 1;
      if(strcmp(msg,"/Creare_cont") == 0)
        flagI = 1;
      contor_secundar++;
    }

    contor_secundar = 0;
    write(sd,msg,100);
//*****************************************************************************************************************************************

    while(ok == 0 && flagL == 1){

    if(contor != 0){

      printf (ANSI_COLOR_RED  "[client]Datele sunt gresite!" ANSI_COLOR_RESET "\n");
      printf (ANSI_COLOR_YELLOW  "[client]Doriti sa va inregistrati ?" ANSI_COLOR_RESET "\n");
      bzero (msg, 100);
      read (0, msg, 100);
      msg[strlen(msg) - 1 ] = '\0';

      if (write (sd, msg, 100) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
      }

      if(strcmp(msg,"Da")==0)
          Login = 1;

    }
    else
    {
        printf (ANSI_COLOR_CYAN  "[client]LOGARE!" ANSI_COLOR_RESET "\n");
    }
    if(Login == 1)
      break;

    contor = contor + 1;

    int okn = 1;
    while(okn == 1)
    {
        if(contor_secundar != 0)
            printf (ANSI_COLOR_RED  "[client]Numele contine caractere invalide!" ANSI_COLOR_RESET "\n");


        bzero (msg, 100);
        printf ("[client]Introduceti un nume: ");
        fflush (stdout);
        okn = 0;
        read (0, msg, 100);
        msg[strlen(msg) - 1 ] = '\0';
        for (int i=0;i<strlen(msg);i++)
          if(!((msg[i]>='A' && msg[i]<'Z') || (msg[i]>='a' && msg[i]<'z')))
            okn = 1;
        contor_secundar ++; 

    }
      if (write (sd, msg, 100) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
      }
    strcpy(nume_final,msg);
    int  oke = 1; contor_secundar = 0; 
    while(oke == 1)
    {
        if(contor_secundar != 0)
          printf(ANSI_COLOR_RED "[client]Ati introdus o adresa de email gresita!" ANSI_COLOR_RESET "\n");
        bzero (msg, 100);
        printf ("[client]Introduceti un email: ");
        fflush (stdout);

        read (0, msg, 100);
        msg[strlen(msg) - 1 ] = '\0';

        if(strstr(msg,"@gmail.com"))
          oke = 0;
        contor_secundar ++ ;

    }
      if (write (sd, msg, 100) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
      }

      bzero (msg, 100);
    printf ("[client]Introduceti o parola: ");
    fflush (stdout);

    char pass[100];
    strcpy(pass,"jb!a");
    read (0, msg, 100);
    msg[strlen(msg) - 1 ] = '\0';
    strcat(pass,msg);
    strcat(pass,"-yi");
    criptare(pass);
      if (write (sd, pass, 100) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
        return errno;
      }


    if (read (sd, msg, 100) < 0)
      {
        perror ("[client]Eroare la read() de la server.\n");
        return errno;
      }
      ok = atoi(msg);
    }

//***************************************************************************************************************************************
    while(Login == 1 || flagI == 1)
    {

//nume***************************************************************************************************************************************************************
        int vf = 0,ci = 0;
        while(vf == 0)
        {
            if(ci!=0)
                printf (ANSI_COLOR_RED  "[client]Numele este deja folosit!" ANSI_COLOR_RESET "\n");
            else
              {
                  printf (ANSI_COLOR_CYAN  "[client]INREGISTRARE!" ANSI_COLOR_RESET "\n");
              }
            int okn = 1;
            contor_secundar == 0;
            while(okn == 1)
            {
                if(contor_secundar != 0)
                    printf (ANSI_COLOR_RED  "[client]Numele contine caractere invalide!" ANSI_COLOR_RESET "\n");


                bzero (msg, 100);
                printf ("[client]Introduceti un nume: ");
                fflush (stdout);
                okn = 0;
                read (0, msg, 100);
                msg[strlen(msg) - 1 ] = '\0';
                for (int i=0;i<strlen(msg);i++)
                  if(!((msg[i]>='A' && msg[i]<'Z') || (msg[i]>='a' && msg[i]<'z')))
                  {    
                      okn = 1;
                      contor_secundar ++; 
                  }
            }
              //printf ("[client]AM TRECUT DE ACEST PAS\n");
            if (write (sd, msg, 100) <= 0)
            {
              perror ("[client]Eroare la write() spre server.\n");
              return errno;
            }
            strcpy(nume_final,msg);
            if (read (sd, msg, 100) < 0)
            {
              perror ("[client]Eroare la read() de la server.\n");
              return errno;
            }

            //printf("[client]Mesajul este: %s \n",msg);
            vf = atoi(msg);
            ci++;

        }
        printf (ANSI_COLOR_GREEN "[client]Nume valid."  ANSI_COLOR_RESET "\n");
//email**********************************************************************************************************************************************************
        vf = 0;
        ci=0;
        while(vf == 0)
        {
            int  oke = 1; contor_secundar = 0; 
            if(ci!=0)
                printf (ANSI_COLOR_RED  "[client]Email-ul este deja folosit!" ANSI_COLOR_RESET "\n");
            while(oke == 1)
            {
                if(contor_secundar != 0)
                  printf(ANSI_COLOR_RED "[client]Ati introdus o adresa de email gresita!" ANSI_COLOR_RESET "\n");
                bzero (msg, 100);
                printf ("[client]Introduceti un email: ");
                fflush (stdout);

                read (0, msg, 100);
                msg[strlen(msg) - 1 ] = '\0';

                if(strstr(msg,"@gmail.com"))
                  oke = 0;
                contor_secundar ++ ;

            }

            if (write (sd, msg, 100) <= 0)
            {
              perror ("[client]Eroare la write() spre server.\n");
              return errno;
            }

            if (read (sd, msg, 100) < 0)
            {
              perror ("[client]Eroare la read() de la server.\n");
              return errno;
            }
            ci++;
            vf = atoi(msg);

        }
        printf (ANSI_COLOR_GREEN "[client]Email valid."  ANSI_COLOR_RESET "\n"); 
//parola***************************************************************************************************************************************************
        int okp = 0;
        contor_secundar = 0;
        while(okp == 0 )
        {
          if(contor_secundar != 0)
                printf(ANSI_COLOR_RED "[client]Parolele nu sunt la fel!" ANSI_COLOR_RESET "\n");      
          char parola1[100], parola2[100];
           

          bzero (parola1, 100);
          printf ("[client]Introduceti o parola: ");
          fflush (stdout);
          read (0, parola1, 100);
          parola1[strlen(parola1) - 1 ] = '\0';

          bzero (parola2, 100);
          printf ("[client]Repetati parola: ");
          fflush (stdout);
          read (0, parola2, 100);
          parola2[strlen(parola2) - 1 ] = '\0';

          if(strcmp(parola1,parola2) == 0)
          {

            printf(ANSI_COLOR_GREEN "[client]Parolele se potrivesc!" ANSI_COLOR_RESET "\n"); 
            okp = 1;
            char pass[100];
            strcpy(pass,"jb!a");
            strcat(pass,parola1);
            strcat(pass,"-yi");
            criptare(pass);
              if (write (sd, pass, 100) <= 0)
              {
                perror ("[client]Eroare la write() spre server.\n");
                return errno;
              }


          }
          contor_secundar++;
          printf (ANSI_COLOR_CYAN  "[client]Contul a fost creat cu succes!" ANSI_COLOR_RESET "\n");

        }
        
        Login = 0;
        flagI = 0;

 }
//******************************************************************************************************************************************************************    
    printf (ANSI_COLOR_GREEN "[client]Bine ati venit!"  ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Acum ca v-ati conectat, puteti sa executati comenzi in cadrul aplicatiei." ANSI_COLOR_RESET "\n" );
    printf(ANSI_COLOR_YELLOW "[client]Pentru trimite un nou mesaj, folositi comanda " ANSI_COLOR_RED "/Trimit_mesaj" ANSI_COLOR_YELLOW ", dupa urmariti pasii indicati de server." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Pentru a sterge o connversatie, folositi comanda " ANSI_COLOR_RED "/Sterge_conversatie" ANSI_COLOR_YELLOW ", dupa urmariti pasii indicati de server." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Pentru a afisa o connversatie, folositi comanda " ANSI_COLOR_RED "/Afiseza_conversatie" ANSI_COLOR_YELLOW ", dupa urmariti pasii indicati de server." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Pentru a afisa lista cu userii aplicatiei, folositi comanda " ANSI_COLOR_RED "/Afiseza_useri" ANSI_COLOR_YELLOW ", dupa urmariti pasii indicati de server." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Pentru a inchide aplicatia, folositi comanda " ANSI_COLOR_RED "/Inchide_aplicatia" ANSI_COLOR_YELLOW "." ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "[client]Pentru a afisa mesajele necitie, folositi comanda " ANSI_COLOR_RED "/Afiseaza_necitite" ANSI_COLOR_YELLOW "." ANSI_COLOR_RESET "\n");

    while(1)
    {

        contor_secundar = 0;
        int flagTM = 0, flagSC = 0, flagAC = 0, flagAU = 0,flagEND =0, flagAfis = 0;
        while(flagTM == 0 && flagSC == 0 && flagAC == 0 && flagAU == 0 && flagEND == 0 && flagAfis == 0)
          {
            if(contor_secundar != 0)
              printf(ANSI_COLOR_RED "[client]Ati introdus o comanda gresita!" ANSI_COLOR_RESET "\n");
            bzero (msg, 100);
            printf(ANSI_COLOR_BLUE "[client]Ce comanda doriti sa executati: " ANSI_COLOR_RESET);
            fflush (stdout);
            read (0, msg, 100);
            msg[strlen(msg) - 1 ] = '\0';
            if(strcmp(msg,"/Trimit_mesaj") == 0)
              flagTM = 1;
            if(strcmp(msg,"/Sterge_conversatie") == 0)
              flagSC = 1;
            if(strcmp(msg,"/Afiseaza_conversatie") == 0)
              flagAC = 1;
            if(strcmp(msg,"/Afiseaza_useri") == 0)
              flagAU = 1;
            if(strcmp(msg,"/Inchide_aplicatia") == 0)
              flagEND = 1;
            if(strcmp(msg,"/Afiseaza_necitite") == 0)
              flagAfis = 1;
            contor_secundar++;
          }

          write(sd,nume_final,100);

          if(flagAC == 1)
          {

            FILE * f;
            contor_secundar = 0;
            int stop = 0,egale=0; 
            char intrare[10000];
            char flagF[100];

            flagF[0] = '1';
            flagF[1] = '\0';
            write(sd,flagF,100);
            
            while(stop != 2 )
            {
                

                if(stop == 3)
                 printf(ANSI_COLOR_RED "[client]Userul specificat nu exista" ANSI_COLOR_RESET "\n");

                if(stop == 1)
                  printf(ANSI_COLOR_RED "[client]Userul specificat sunteti dumneavoastra" ANSI_COLOR_RESET "\n");

                bzero (msg, 100);
                printf(ANSI_COLOR_BLUE "[client]Introduceti numele user-ului: " ANSI_COLOR_RESET);
                fflush (stdout);
                read (0, msg, 100);
                
                msg[strlen(msg) - 1 ] = '\0'; 

                write(sd,msg,100);

                char verificare_stop[100];
                read(sd,verificare_stop,100);
                stop  = atoi(verificare_stop);
                contor_secundar ++;
            }
            char creare_fisier[1000];
            strcpy(creare_fisier,nume_final);
            strcat(creare_fisier,"_");
            strcat(creare_fisier,msg);
            strcat(creare_fisier,".txt");


            write(sd,creare_fisier,1000);

            printf(ANSI_COLOR_GREEN "[client]Conversatia de la ultima stergere: " ANSI_COLOR_RESET "\n");

            int stop_scriere = 1;
            int intru_bucla = 1;
            intrare[0] = '\0';
            while(stop_scriere == 1)
            {
                read(sd,intrare,1000);
                if(intrare[0]=='1' && intrare[1]=='\0')
                {
                  stop_scriere = 0;
                }
                else
                {
                  intru_bucla = 0;
                  printf("%s",intrare);
                }
            }
            if(intru_bucla == 1)
              printf(ANSI_COLOR_RED "[client]Nu aveti nici un mesaj cu aceasta persoana!" ANSI_COLOR_RESET "\n");
            //printf("\n");



           }


          
          if(flagTM == 1)
          {

            FILE * f;
            contor_secundar = 0;
            int stop = 0,egale=0; 
            char intrare[10000];
            char flagF[100];

            flagF[0] = '2';
            flagF[1] = '\0';
            write(sd,flagF,100);
            
            while(stop != 2 )
            {
                

                if(stop == 3)
                 printf(ANSI_COLOR_RED "[client]Userul specificat nu exista" ANSI_COLOR_RESET "\n");

                if(stop == 1)
                  printf(ANSI_COLOR_RED "[client]Userul specificat sunteti dumneavoastra" ANSI_COLOR_RESET "\n");

                bzero (msg, 100);
                printf(ANSI_COLOR_BLUE "[client]Introduceti numele user-ului: " ANSI_COLOR_RESET);
                fflush (stdout);
                read (0, msg, 100);
                
                msg[strlen(msg) - 1 ] = '\0'; 

                write(sd,msg,100);

                char verificare_stop[100];
                read(sd,verificare_stop,100);
                stop  = atoi(verificare_stop);
                contor_secundar ++;
            }
            char creare_fisier[1000],creare_fisier_secund[1000];
            strcpy(creare_fisier,nume_final);
            strcat(creare_fisier,"_");
            strcat(creare_fisier,msg);
            strcat(creare_fisier,".txt");

            strcpy(creare_fisier_secund,msg);
            strcat(creare_fisier_secund,"_");
            strcat(creare_fisier_secund,nume_final);
            strcat(creare_fisier_secund,".txt");

            bzero (msg, 100);
            printf(ANSI_COLOR_BLUE "[client]Introduceti mesajul pe care vreti sa il transmiteti (1 - 100 caractere): \n " ANSI_COLOR_RESET);
            fflush (stdout);
            read (0, msg, 100);

            write(sd,creare_fisier,1000);
            write(sd,creare_fisier_secund,1000);

            write(sd,msg,100);    
            printf("\n");
            printf(ANSI_COLOR_GREEN "[client]Mesajul a fost trimis cu succes \n " ANSI_COLOR_RESET);


           }

           if(flagSC == 1)
          {

            FILE * f;
            contor_secundar = 0;
            int stop = 0,egale=0; 
            char intrare[10000];
            char flagF[100];

            flagF[0] = '3';
            flagF[1] = '\0';
            write(sd,flagF,100);
            
            while(stop != 2 )
            {
                

                if(stop == 3)
                 printf(ANSI_COLOR_RED "[client]Userul specificat nu exista" ANSI_COLOR_RESET "\n");

                if(stop == 1)
                  printf(ANSI_COLOR_RED "[client]Userul specificat sunteti dumneavoastra" ANSI_COLOR_RESET "\n");

                bzero (msg, 100);
                printf(ANSI_COLOR_BLUE "[client]Introduceti numele user-ului: " ANSI_COLOR_RESET);
                fflush (stdout);
                read (0, msg, 100);
                
                msg[strlen(msg) - 1 ] = '\0'; 

                write(sd,msg,100);

                char verificare_stop[100];
                read(sd,verificare_stop,100);
                stop  = atoi(verificare_stop);
                contor_secundar ++;
            }
            char creare_fisier[1000];
            strcpy(creare_fisier,nume_final);
            strcat(creare_fisier,"_");
            strcat(creare_fisier,msg);
            strcat(creare_fisier,".txt");


            write(sd,creare_fisier,1000);

            printf(ANSI_COLOR_GREEN "[client]Conversatia a fost stearsa!" ANSI_COLOR_RESET "\n");

           }
            if(flagAU == 1)
          {

            FILE * f;
            contor_secundar = 0;
           // int stop = 0,egale=0; 
            char intrare[10000];
            char flagF[100];

            flagF[0] = '4';
            flagF[1] = '\0';
            write(sd,flagF,100);
            
            printf(ANSI_COLOR_GREEN "[client]Lista userilor inregistrati: " ANSI_COLOR_RESET "\n");
            
            intrare[0] = '\0';
            int stop_scriere = 1;
            while(stop_scriere == 1)
            {
                read(sd,intrare,1000);
                if(intrare[0]=='1' && intrare[1]=='\0')
                {
                  stop_scriere = 0;
                }
                else
                  printf("%s",intrare);
            }

          //;printf("\n");



           }
           int opr = 0;
           if(flagEND == 1)
           {
              break;
              //pritnf("\n");
              
              
           }
           if(flagAfis == 1)
           {
            int stop_scriere = 1;
            FILE * f;
            char intrare[10000];
            char flagF[100];

            flagF[0] = '5';
            flagF[1] = '\0';
            write(sd,flagF,100);
            
            intrare[0] = '\0';\
            strcpy(intrare,nume_final);
            strcat(intrare,".txt");
            //printf("$$$$$$%s\n",intrare);
            write(sd,intrare,1000);
            int intru_bucla = 0;
            intrare[0] = '\0';
            while(stop_scriere == 1)
            {
                read(sd,intrare,1000);
                if(intrare[0]=='1' && intrare[1]=='\0')
                {
                  stop_scriere = 0;
                }
                else
                {
                  printf("%s",intrare);
                  intru_bucla = 1;
                }
            }
            if(intru_bucla == 0)
               printf(ANSI_COLOR_RED "[client]Nu aveti mesaje necitite!" ANSI_COLOR_RESET "\n");

            //printf("\n");

           }

          contor_secundar = 0;
          //write(sd,msg,100);
    }
  

    /* inchidem conexiunea, am terminat */
    close (sd);
}