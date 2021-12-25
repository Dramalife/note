##### Debian
```bash
# ref: https://www.runoob.com/docker/debian-docker-install.html
curl -fsSL https://get.docker.com | bash -s docker --mirror Aliyun
```

#### Config
```
root@omvhpgen8:~/disk_rw/data # cat /etc/docker/daemon.json 
{
  "data-root": "/root/disk_rw/data/docker"
}
```
