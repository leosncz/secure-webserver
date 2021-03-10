#include "httplib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "plusaes.hpp"
using namespace std;
using namespace httplib;
class server
{
public:

 bool start(){
  svr.Get(R"(/(.*))", [&](const Request& req, Response& res) {
    auto fileToLook = req.matches[1];
    std::ifstream t(fileToLook);
    std::string fileContent((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
    //encode the result
    std::vector<unsigned char> key = {chosenKey[0],chosenKey[1],chosenKey[2],chosenKey[3],chosenKey[4],chosenKey[5],chosenKey[6],chosenKey[7],chosenKey[8],chosenKey[9],chosenKey[10],chosenKey[11],chosenKey[12],chosenKey[13],chosenKey[14],chosenKey[15]};
    const unsigned char iv[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    };
    const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(fileContent.size());
    std::vector<unsigned char> encrypted(encrypted_size);
    plusaes::encrypt_cbc((unsigned char*)fileContent.data(), fileContent.size(), &key[0], key.size(), &iv, &encrypted[0], encrypted.size(), true);
    fileContent = string(encrypted.begin(), encrypted.end());
    res.set_content(fileContent, "text/html");    
  });
  port = svr.bind_to_any_port("0.0.0.0");
  cout << "-> Listening started on port " << port << " !" << endl;
  svr.listen_after_bind();
  return true;
 }

 void startConfig(){
  cout << "------------Welcome to secure-webserver !" << endl;
  cout << "-> Every request must match the filename, for example : /hi -> hi.swsrv" << endl;
  cout << "-> All files must lie within the application path" << endl;
  cout << "-> The secret AES key can be passed automatically by parameter (first)" << endl;
  cout << "-> secure-webserver will automatically open your default web-browser when detects a request" << endl;
  cout << "-> Never share your key !" << endl;
  cout << "" << endl;
  cout << "-> What is your AES key ? (16 character)" << endl;
  cin >> chosenKey;
  
  return;
 }

private:
 httplib::Server svr;
 unsigned char chosenKey[16];
 int port;
};
