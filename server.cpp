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
            sockfd=socket(AF_INET,SOCK_STREAM,0);
            if(sockfd==-1)
                cout<<"soket acilmadi";
            SunucuBilgileri.sin_family=AF_INET;
            SunucuBilgileri.sin_addr.s_addr=htonl(INADDR_ANY);
            SunucuBilgileri.sin_port=htons(port);
            int kontrol=bind(sockfd,(struct sockaddr *)&SunucuBilgileri,sizeof(SunucuBilgileri));

            if(kontrol<0)
                cout<<"IP ADRES KONTROL ET"  ;       

	   

        };

        void Listen(){
            listen(sockfd,5);
            clientlength=sizeof(MusteriBilgileri);
            int kabul=accept(sockfd,(struct sockaddr*)&MusteriBilgileri,&clientlength);
            if(kabul==-10)
                cout<<"Baglantı Kabul Edilmedi";
            else
                cout<<"Bağlantı Kabul Edildi";
        }

        void connection(){
            int dogrulama=connect(sockfd,(struct sockaddr*)&SunucuBilgileri,sizeof(SunucuBilgileri));
            if(dogrulama<0)
                cout<<"baglantı problemi";
            else 
                cout<<"Baglandi";
        }

        void sendMessage(const char *metin){
            
            int mesaj_yazildi=write(sockfd,metin,200);
            if(mesaj_yazildi<0)
                cout<<"MESAJ YAZILAMADI";
        }

        char * receiveMessage(){
            char metin[200];
            int mesaj_okundu=read(sockfd,metin,200);
            if(mesaj_okundu<0)
                cout<<"MESAJ OKUNAMADI";
        }
};



int main(){
    Server server(4444);
    server.Listen();
    string gelenmesaj=server.receiveMessage();
    server.sendMessage("Merhaba Ben Sunucu");


}