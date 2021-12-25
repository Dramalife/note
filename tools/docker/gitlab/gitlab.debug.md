##### Error - 502: 502 Whoops, GitLab is taking too much time to respond.
```
gitlab-ctl tail
tail -f /var/log/gitlab/nginx/gitlab_error.log
chmod 777 /var/opt/gitlab/gitlab-workhorse/sockets/socket
```
##### Error - ssh: Connection refused
root@1a6c776dee43:/# service ssh restart
/run/sshd must be owned by root and not group or world-writable.
chmod 744 /run/sshd/

##### Error - avatar
ref: https://docs.gitlab.com/13.9/ee/administration/libravatar.html
```
vi /etc/gitlab/gitlab.rb
# uncomment and update:
gitlab_rails['gravatar_plain_url'] = 'http://cdn.libravatar.org/avatar/%{hash}?s=%{size}&d=identicon'
```
##### Reconfig
gitlab-ctl reconfigure
gitlab-ctl restart
