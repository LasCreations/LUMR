cd ..
sudo docker build . -t server

cd services/auth
sudo docker build . -t authentication

cd ../web/
sudo docker build . -t web