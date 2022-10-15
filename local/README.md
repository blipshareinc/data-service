# Data Storage - Local Mode
CRUD operations are performed on data hosted on-premise. The project includes a `sqlite3` database (`./db/local.db`) to hold the data.   

<p>
The project is developed in C++ leveraging [OATPP](https://github.com/oatpp/oatpp)
</p>

## Build Instructions
This project supports building for Arch64 and Arm32v7

### Arch64
Run the following command to build the image
```
docker build -f Dockerfile -t local-data-service:latest .
```

### Arch64
Run the following command to build the image. It has been tested on Raspberry Pi4 with Arch Linux.

```
docker build -f Dockerfile.edge -t local-data-service:latest .
```
