Ref : https://www.runoob.com/docker/docker-run-command.html

docker run ：创建一个新的容器并运行一个命令

docker run [OPTIONS] IMAGE [COMMAND] [ARG...]

-d: 后台运行容器，并返回容器ID；

-i: 以交互模式运行容器，通常与 -t 同时使用；
-t: 为容器重新分配一个伪输入终端，通常与 -i 同时使用；

-p: 指定端口映射，格式为：主机(宿主)端口:容器端口

--name="nginx-lb": 为容器指定一个名称；

-h "mars": 指定容器的hostname；
-e username="ritchie": 设置环境变量；
--env-file=[]: 从指定文件读入环境变量；

--cpuset="0-2" or --cpuset="0,1,2": 绑定容器到指定CPU运行；
-m :设置容器使用内存最大值；
--net="bridge": 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；
--volume , -v: 绑定一个卷


