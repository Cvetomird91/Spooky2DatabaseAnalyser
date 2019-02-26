FROM gcc:4.8
COPY . /src

RUN apt-get -y update

RUN apt-get install -y build-essential libboost-iostreams-dev libboost-regex-dev libboost-system-dev libboost-filesystem-dev libboost-date-time-dev cmake vim
