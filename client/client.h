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
   cout << "-> Enter your confidential AES shared key" << endl << "->";
   cin >> chosenKey;
   while(true){
    cout << "-> Enter the hostname you want to visit (without the page indicator eg. google.com) : " << endl << "->";
    string hostname;
    cin >> hostname;
    cout << "-> Enter the page indicator (eg. /search):" << endl << "->";
    string pindicator;
    cin >> pindicator;
    cout << "-> Enter the port: " << endl << "->";
    int port;
    cin >> port;
    cout << endl;

    httplib::Client cli(hostname, port);

    if (auto res = cli.Get(pindicator.c_str())) {
      if (res->status == 200) {
        string encryptedAnswer = res->body;
        std::vector<unsigned char> key = {chosenKey[0],chosenKey[1],chosenKey[2],chosenKey[3],chosenKey[4],chosenKey[5],chosenKey[6],chosenKey[7],chosenKey[8],chosenKey[9],chosenKey[10],chosenKey[11],chosenKey[12],chosenKey[13],chosenKey[14], chosenKey[15]};
        const unsigned char iv[16] = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
          };
        const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(encryptedAnswer.size());
        unsigned long padded_size = 0;
        std::vector<unsigned char> decrypted(encrypted_size);
        plusaes::decrypt_cbc((unsigned char*)encryptedAnswer.data(), encryptedAnswer.size(), &key[0], key.size(), &iv, &decrypted[0], decrypted.size(), &padded_size);
        string decryptedStr = string(decrypted.begin(), decrypted.end());
        //shift by 1 to remove the first /
        for(int i = 0; i < pindicator.length(); i++)
        {
		pindicator[i] = pindicator[i+1];
        }
        
        std::ofstream out(pindicator);
        out << decryptedStr;
        out.close();
        cout << "File" << pindicator << " has been created !" << endl;
        string commandLine = "open ";
        commandLine.append(pindicator);
        system(commandLine.c_str());
       }
       else{cout << "ERROR HTTP IS NOT 200 (OK)!"  << endl;}
     }
    }
 }

private:
  unsigned char chosenKey[16];
};
