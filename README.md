# DooR-API-Client
This program will work with docker container.


## compile

Compile door_bridge shared library 
```console
$ cd src/door_bridge
$ cmake .
$ make
$ sudo make install
```

Compile DooR-API-Client
```console
$ cmake .
$ make
```

## how to work
1. Create data container to share shared library
```console
$ docker run --name libcontainer --ipc=host -v /usr/local/lib:/usr/local/lib -v /user/local/include:/usr/local/include -v /tmp/unix-socket:/tmp/unix-socket -v /tmp/recorder:/tmp/recorder centos
```

2. Create Client image and Run Client container
```console
$ docker build -t door-app .
$ docker run --rm --ipc=host -it --volumes-from libcontainer door-app /bin/bash
```

3. Run program
```console
$ ./DooR-API-Client
```
