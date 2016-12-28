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
$ docker run -it --ipc=host -v /usr/local/lib:/usr/local/lib -v /user/local/include:/usr/local/include -v ./DooR-API-Client:. centos /bin/bash
```

2. Create Client image and Run Client container
```console
$ docker build -f Dockerfile .
$ docker run --ipc=host -it -v /tmp:/tmp --volumes-from libcontainer [Image ID] /bin/bash
```

3. Run program
```console
$ ./DooR-API-Client
```
