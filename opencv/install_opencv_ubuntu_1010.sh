#!/bin/bash

# Instala o G++

sudo apt-get --yes install g++

# Possivelmente adicionar um servidor de proxy, caso exista, em:
# System > Preferences > Proxy
# Instalar a biblioteca boost 

sudo apt-get --yes install libboost1.40-all-dev

# Para instalar a OpenCV com suporte a vídeo, temos de ter o ffmpeg-dev instalado juntamente com as bibliotecas de driver. Para isso então, instalaremos os seguintes pacotes:

sudo apt-get --yes install ffmpeg libavformat-dev libswscale-dev

# Agora instalaremos a parte que dara suporte ao gráfico

sudo apt-get --yes install libgtk2.0-dev pkg-config

# Para permitir a compilação do OpenCV precisamos do cmake 
sudo apt-get --yes install cmake

# Agora devemos efetuar o download do OpenCV

wget "http://downloads.sourceforge.net/project/opencvlibrary/opencv-unix/2.2/OpenCV-2.2.0.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fopencvlibrary%2Ffiles%2Fopencv-unix%2F2.2%2F&ts=1298402631&use_mirror=ufpr"

# Agora devemos que renomear e descompactar o OpenCV

mv "OpenCV-2.2.0.tar.bz2?r=http:%2F%2Fsourceforge.net%2Fprojects%2Fopencvlibrary%2Ffiles%2Fopencv-unix%2F2.2%2F&ts=1298402631&use_mirror=ufpr" OpenCV.tar.bz2

tar --extract -vf OpenCV.tar.bz2

# Entra no diretório para efetuar a compilação e instalação do código
cd OpenCV-2.2.0/
mkdir release
cd release
cmake ..
make && sudo make install


