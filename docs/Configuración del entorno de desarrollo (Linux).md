# Configuración del entorno de desarrollo (GNU/Linux)

Utilizaremos Ubuntu en los ejemplos de cómo instalar las herramientas necesarias en nuestro sistema para poder compilar el firmware y grabarlo en la EDU-CIAA.

## Instalación del compilador

Primero necesitaremos un compilador para ARM (v4.8) el cual descargaremos del [siguiente link](https://launchpad.net/gcc-arm-embedded/4.8/4.8-2014-q2-update/+download/gcc-arm-none-eabi-4_8-2014q2-20140609-linux.tar.bz2|arm-none-eabi-gcc para Linux) o [accediendo al sitio](https://launchpad.net/gcc-arm-embedded|https://launchpad.net/gcc-arm-embedded).

Una vez obtenido el archivo `tar.bz2`, lo descomprimimos y agregamos al `PATH` del sistema la ruta donde se encuentran los binarios del compilador:

```bash
sudo su
wget https://launchpad.net/gcc-arm-embedded/4.8/4.8-2014-q2-update/+download/gcc-arm-none-eabi-4_8-2014q2-20140609-linux.tar.bz2
mv gcc-arm-none-eabi-4_8-2014q2-20140609-linux.tar.bz2 /opt/
cd /opt
tar jxf gcc-arm-none-eabi-4_8-2014q2-20140609-linux.tar.bz2
rm gcc-arm-none-eabi-4_8-2014q2-20140609-linux.tar.bz2
```

Para agregar el compilador al `PATH`, editamos el archivo `.bashrc` (o `.zshrc`) el cual contiene un script que se ejecutará cuando ingresemos a la terminal con el usuario *root*.

```bash
nano /root/.bashrc
```

Al final del archivo agregamos:

```bash
export PATH=$PATH:/opt/gcc-arm-none-eabi-4_8-2014q2/bin/
````

Abrimos otra consola y nos logueamos como root y verificamos que el compilador se encuentra en el PATH escribiendo:

```bash
arm-none-eabi-gcc --version

arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 4.8.4 20140526 (release) [ARM/embedded-4_8-branch revision 211358]
Copyright (C) 2013 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.''
```

### Instalación de openOCD

Comenzaremos instalando el driver para el chip FTDI que posee la placa:

```bash
sudo apt install libftdi-dev
sudo apt install libusb-1.0-0-dev
```

Bajamos e instalamos los paquetes necesarios para compilar:

```bash
sudo apt install pkg-config
sudo apt install build-essential
```

Bajamos [OpenOCD](https://openocd.org/) (v0.9.0), lo compilamos e instalamos:

```bash
cd ~
wget https://sourceforge.net/projects/openocd/files/openocd/0.9.0/openocd-0.9.0.tar.bz2
tar -xvjf openocd-0.9.0.tar.bz2
cd openocd-0.9.0
./configure --enable-ftdi
make
make install
```

Para comprobar que la herramienta este instalada, ejecutamos:

```bash
openocd --version
```
