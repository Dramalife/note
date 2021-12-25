##### Debian
```bash
# ref: https://blog.kelu.org/tech/2021/01/04/debian-uninstall-docker.html
dpkg -l | grep docker
apt-get remove docker-ce-cli docker-ce
apt-get autoremove
```
```bash
# ref: https://www.runoob.com/docker/debian-docker-install.html
sudo apt-get purge docker-ce
sudo rm -rf /var/lib/docker
```
