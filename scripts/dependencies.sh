

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

sudo docker build . -t trivpalserver


Required libraries


 




REMEMBER TO DISABLE UFW PORTS THAT ARE NOT BEING USED


Start up docker compose
- sudo docker-compose up -d

Stop docker compose
- sudo docker-compose down


Building an image
- sudo docker build . -t {name you want to call the image}

Remove an image
- sudo docker rmi -f {image name}

Run an image 
- sudo docker run -p {External Port}:{Container Port} -it {image name}

Check Container status
- sudo docker ps