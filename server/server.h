#include "httplib.h"
#include <iostream>
#include <string>
#include "plusaes.hpp"
using namespace std;
using namespace httplib;
class server
{
public:

 bool start(){
  svr.Get(R"(/(.*))", [&](const Request& req, Response& res) {
    auto request = req.matches[1];
    res.set_content("OK !", "text/plain");
    }
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
  cout << "-> What is your AES key ?" << endl;
  key = "";
   
  do
  {
    cout << endl << "->";
    cin >> key;
  } while(key == "");
  
  return;
 }

private:
 httplib::Server svr;
 string key;
 int port;
};
