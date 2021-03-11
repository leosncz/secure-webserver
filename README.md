# secure-webserver
## what is secure-webserver
**secure-webserver** is composed of two elements : a server and a client.</br>
Both must share the same AES 16-character key (126 bits), the client will ask for a page : eg. /coolstuff.html -> the server will send an encrypted version of the coolstuff.html file.</br>
Then, the client will decrypt the received file and open it.
## Purpose
**secure-werbserver** is usefull to setup an easy encrypted web-server without all the pain to manage any kind of certificate.</br>
With this software, the only mandatory thing to do is to share a 16 character long key between the client and the server.</br> 
## Example
Server configuration :
<br/><br/>
![Server conf](screenshot_server.png)
<br/><br/>
What you see when you navigate with your default browser :
<br/><br/>
![Server conf](screenshot_encrypted.png)
<br/><br/>
Client configuration :
<br/><br/>
![Server conf](screenshot_client.png)
<br/><br/>
The final result when you access the website from the client :
<br/><br/>
![Server conf](screenshot_result.png)
## Licences
- plusaes (for aes encryption-decryption) - MIT
- cpp-httplib (for http request handling) - MIT
- secure-webserver - MIT
