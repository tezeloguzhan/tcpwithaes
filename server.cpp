#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>  
#include <unistd.h>
#include <iostream>

using namespace std;

class Server{
    socklen_t clientlength;
    
    int sockfd;
    int port;
    struct sockaddr_in SunucuBilgileri,MusteriBilgileri;
    public:
        Server(int portnumber){
            port=portnumber;
            sockfd=socket(AF_INET, SOCK_STREAM, 0);
            if(sockfd==-1)
                cout<<"soket acilmadi";
            else
                cout<<"soket acildi\n";
            SunucuBilgileri.sin_family=AF_INET;
            SunucuBilgileri.sin_addr.s_addr=htonl(INADDR_ANY);
            SunucuBilgileri.sin_port = htons(port);
            int kontrol=bind(sockfd,(struct sockaddr *)&SunucuBilgileri,sizeof(SunucuBilgileri));
            if(kontrol<0)
                cout<<"IP ADRES KONTROL ET"  ; 
            else
                cout<<"SOKET OK\n" ;    

	   

        };

        void Listen(){
            listen(sockfd,5);
            clientlength=sizeof(MusteriBilgileri);
            int kabul=accept(sockfd,(struct sockaddr*)&MusteriBilgileri,&clientlength);
            if(kabul==-1)
                cout<<"Baglantı Kabul Edilmedi";
            else
                cout<<"Bağlantı Kabul Edildi\n";
        }

       

        void sendMessage(const char *metin){
            
            int mesaj_yazildi=write(sockfd, metin, strlen(metin));
            if(mesaj_yazildi<0)
                cout<<"MESAJ YAZILAMADI/n";
        }

        char * receiveMessage(){
            char metin[1024] = "\n";
            int mesaj_okundu = read(sockfd, metin, 1024);
            cout << "server len : " << mesaj_okundu << endl;
            if(mesaj_okundu < 0){
               perror("error : "); 
                cout<<"MESAJ OKUNAMADI\n";
            }
            cout<<metin;
            cout << "log : here " << endl;            
        }
};



int main(){
    
    Server server(5000);
    server.Listen();
    string gelenmesaj=server.receiveMessage();
    cout<<gelenmesaj;
    server.sendMessage("Merhaba Ben Sunucu");
    

}