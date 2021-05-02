# List
docker ps -l
docker ps -a


### [run](./run.md)
docker [run](./run.md)

#### Background
docker run --name my_ubuntu -d ubuntu
	-p 127.0.0.1:80:8080/tcp
docker run --name my_ubuntu -p 127.0.0.1:10022:22/tcp -d ubuntu
docker run --name my_ubuntu -p 127.0.0.1:10022:22/tcp -d -i -t ubuntu

#### Foreground
docker run -it nginx:latest /bin/bash

docker rm my_ubuntu


# Exec
docker exec -i -t  my_ubuntu /bin/bash

# Commit
docker commit -a "dramalife" -m "update ..." my_ubuntu  my_ubuntu:tag_add_xx

# Images
docker images
