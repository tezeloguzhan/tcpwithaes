#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>  
#include <unistd.h>
#include <iostream>

using namespace std;

class Client{

    
    int sockfd;
    int port;
    struct sockaddr_in SunucuBilgileri;
    public:
        Client(int portnumber){
            port=portnumber;
            sockfd=socket(AF_INET,SOCK_STREAM,0);
            if(sockfd==-1)
                cout<<"soket acilmadi";
            SunucuBilgileri.sin_family=AF_INET;
            SunucuBilgileri.sin_addr.s_addr=htonl(INADDR_ANY);
            SunucuBilgileri.sin_port=htons(port);

        };

        void connection(){
            int dogrulama=connect(sockfd,(struct sockaddr*)&SunucuBilgileri,sizeof(SunucuBilgileri));
            if(dogrulama<0)
                cout<<"baglantı problemi";
            else 
                cout<<"Baglandi\n\n";
        }

        void sendMessage(const char *metin){
            
            int mesaj_yazildi = write(sockfd, metin, sizeof(metin));
            cout<<"log send message lend : " << mesaj_yazildi  << std::endl;
            if(mesaj_yazildi<0)
                cout<<"MESAJ YAZILAMADI";
            
            
            
        }

        char  receiveMessage(){
            char metin[1024];
            int mesaj_okundu=read(sockfd,metin,1024);
            if(mesaj_okundu<0)
                cout<<"MESAJ OKUNAMADI";
            
            
        }



};

int main(){
    
    Client a(5000);
    a.connection();
    a.sendMessage("Merhaba Ben Oguzhan");
    cout<< a.receiveMessage();
    
     
    
    }


