
sudo docker build . -t trivpalserver


Required libraries
sudo apt-get install -y libmysqlcppconn-dev
sudo apt install mysql-client-core-8.0 
sudo apt install mariadb-client-core-10.6 
sudo apt-get install mysql-server
sudo apt install apache2
sudo apt install nginx
sudo apt-get install phpmyadmin
sudo apt install net-tools
sudo apt install libapache2-mod-php8.1
sudo apt install make 
sudo apt  install cmake 
sudo apt-get install -y build-essential
sudo snap install ngrok
sudo apt-get install libjsoncpp-dev
sudo apt-get install php-cgi

 




REMEMBER TO DISABLE UFW PORTS THAT ARE NOT BEING USED



local server might change sometimes
--- mysql command line ----
sudo service mysql start
sudo mysql -u root
sudo service mysql stop
CREATE USER 'lascelle'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON *.* TO 'lascelle'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;
--- apache2 command line ---
sudo service apache2 start
sudo service apache2 stop
Set up the server on a raspberry pi but had to redirect the IP address of the raspberry pi
- sudo ufw enable
- sudo ufw allow 8080/tcp
url: http://192.168.0.5:8080
Set up the apache connection on the raspberry pi for laptop
 - sudo ufw allow 80
 - http://192.168.0.5:80
 - http://192.168.0.5/phpmyadmin/index.php?route=/
Allow ssh on ubuntu
 - sudo ufw allow 22/tcp
Configure apache2 to run phpmyadmin
sudo vim /etc/apache2/apache2.conf
add this line somewhere
Include /etc/phpmyadmin/apache.conf
sudo apt install libapache2-mod-php8.1
and finally restart apache.
sudo service apache2 restart
In a separate terminal start ngrok
ngrok http 8080
GET: Requests data from a specified resource. The data is included in the URL as parameters.
POST: Submits data to be processed to a specified resource. The data is included in the body of the request.
PUT: Updates a specified resource or creates a new resource if it does not exist. The entire resource is sent in the request body.
DELETE: Requests that a specified resource be removed.
PATCH: Applies partial modifications to a resource. The data to be modified is included in the request body.
HEAD: Requests the headers of a specified resource, similar to GET but without the response body.
OPTIONS: Describes the communication options for the target resource.
TRACE: Echoes the received request, allowing the client to see what (if any) changes or additions have been made by intermediate servers.

CONNECT: Converts the request connection to a transparent TCP/IP tunnel, usually to facilitate secure SSL/TLS connections (HTTPS).


HTTP status codes
1xx (Informational):

100 Continue
101 Switching Protocols
102 Processing (WebDAV; RFC 2518)

2xx (Successful):

200 OK
201 Created
202 Accepted
203 Non-Authoritative Information
204 No Content
205 Reset Content
206 Partial Content
207 Multi-Status (WebDAV; RFC 4918)
208 Already Reported (WebDAV; RFC 5842)
226 IM Used (RFC 3229)
3xx (Redirection):

300 Multiple Choices
301 Moved Permanently
302 Found
303 See Other
304 Not Modified
305 Use Proxy
307 Temporary Redirect
308 Permanent Redirect (RFC 7538)
4xx (Client Error):

400 Bad Request
401 Unauthorized
402 Payment Required
403 Forbidden
404 Not Found
405 Method Not Allowed
406 Not Acceptable
407 Proxy Authentication Required
408 Request Timeout
409 Conflict
410 Gone
411 Length Required
412 Precondition Failed
413 Payload Too Large
414 URI Too Long
415 Unsupported Media Type
416 Range Not Satisfiable
417 Expectation Failed
418 I'm a teapot (RFC 2324)
421 Misdirected Request (RFC 7540)
422 Unprocessable Entity (WebDAV; RFC 4918)
423 Locked (WebDAV; RFC 4918)
424 Failed Dependency (WebDAV; RFC 4918)
425 Too Early (RFC 8470)
426 Upgrade Required
428 Precondition Required (RFC 6585)
429 Too Many Requests (RFC 6585)
431 Request Header Fields Too Large (RFC 6585)
451 Unavailable For Legal Reasons
5xx (Server Error):

500 Internal Server Error
501 Not Implemented
502 Bad Gateway
503 Service Unavailable
504 Gateway Timeout
505 HTTP Version Not Supported
506 Variant Also Negotiates (RFC 2295)
507 Insufficient Storage (WebDAV; RFC 4918)
508 Loop Detected (WebDAV; RFC 5842)
510 Not Extended (RFC 2774)
511 Network Authentication Required (RFC 6585)


Application	
application/EDI-X12
application/EDIFACT
application/javascript
application/octet-stream
application/ogg
application/pdf
application/xhtml+xml
application/x-shockwave-flash
application/json
application/ld+json
application/xml
application/zip
application/x-www-form-urlencoded

Audio	
audio/mpeg
audio/x-ms-wma
audio/vnd.rn-realaudio
audio/x-wav

Image	
image/gif
image/jpeg
image/png
image/tiff
image/vnd.microsoft.icon
image/x-icon
image/vnd.djvu
image/svg+xml

Multipart	
multipart/mixed
multipart/alternative
multipart/related (using by MHTML (HTML mail).)
multipart/form-data

Text	
text/css
text/csv
text/html
text/javascript (obsolete)
text/plain
text/xml

Video	
video/mpeg
video/mp4
video/quicktime
video/x-ms-wmv
video/x-msvideo
video/x-flv
video/webm

VND	
application/vnd.oasis.opendocument.text
application/vnd.oasis.opendocument.spreadsheet
application/vnd.oasis.opendocument.presentation
application/vnd.oasis.opendocument.graphics
application/vnd.ms-excel
application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
application/vnd.ms-powerpoint
application/vnd.openxmlformats-officedocument.presentationml.presentation
application/msword
application/vnd.openxmlformats-officedocument.wordprocessingml.document
application/vnd.mozilla.xul+xml