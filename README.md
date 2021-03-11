# secure-webserver
**secure-webserver** is composed of two elements : a server and a client.
Both must share the same AES 16-character key (126 bits), the client will ask for a page : eg. /coolstuff.html -> the server will send an encrypted version of the coolstuff.html file.</br>
Then, the client will decrypt the received file and open it.

# Licences
- plusaes (for aes encryption-decryption) - MIT
- cpp-httplib (for http request handling) - MIT
- secure-webserver - MIT
