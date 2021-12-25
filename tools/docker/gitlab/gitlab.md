##### Install
```bash
docker search gitlab
docker pull gitlab/gitlab-ce:latest
```

##### Run
```
PATH_TO_HOST=./
NAME_OF_CONTAINER=gitlab-test
docker run \
	       -itd  \
	       -p 1443:443 \
	       -p 1880:80 \
	       -p 1822:22 \
	       -v ${PATH_TO_HOST}/etc:/etc/gitlab  \
	       -v ${PATH_TO_HOST}/log:/var/log/gitlab \
	       -v ${PATH_TO_HOST}/opt:/var/opt/gitlab \
	       --restart always \
	       --privileged=true \
	       --name ${NAME_OF_CONTAINER} \
	       gitlab/gitlab-ce
```

##### Config
```
# vi /etc/gitlab/gitlab.rb
# external_url: hostIP, not containerIP
external_url 'http://192.168.0.200'
gitlab_rails['gitlab_ssh_host'] = '192.168.0.200'
# gitlab_shell_ssh_port hostIP (a container's port published to)
gitlab_rails['gitlab_shell_ssh_port'] = 1822
# avatar
gitlab_rails['gravatar_plain_url'] = 'http://cdn.libravatar.org/avatar/%{hash}?s=%{size}&d=identicon'
```

##### Login
```
# password
cat /etc/gitlab/initial_root_password
```

##### Debug
```
# inside docker
gitlab-ctl tail
```
