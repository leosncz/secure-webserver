#include <iostream>
#include <string>
#include "httplib.h"
#include "plusaes.hpp"
using namespace std;
using namespace httplib;

class client
{
public:
 void start()
 {
   cout << "-------Welcome to secure-webserver CLIENT" << endl;
   key = "";
   cout << "-> Enter your confidential AES shared key" << endl;
   do{
    cout << "->" << endl;
    cin >> key;
   }while(key == "");

   while(true){
    cout << "Enter the hostname you want to visit (without the page indicator eg. google.com) : " << endl;
    string hostname;
    cin >> hostname;
    cout << "Enter the page indicator (eg. /search):" << endl;
    string pindicator;
    cin >> pindicator;
    cout << "Enter the port: " << endl;
    int port;
    cin >> port;
    
    httplib::Client cli(hostname, port);
    if (auto res = cli.Get(pindicator.c_str())) {
      if (res->status == 200) {
        std::cout << "GOT (still encrypted): " << res->body << endl;
        cout << "----------  END OF BODY ---------" << endl << endl;
      }
      else{cout << "ERROR HTTP IS NOT 200 !" << endl << endl;}
    }   
   }
}

private:
  string key;
};
