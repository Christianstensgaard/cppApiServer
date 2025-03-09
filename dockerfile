FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
RUN mkdir -p /app/swagger-ui

COPY ./build/test /app/


COPY ./build/swagger-ui /app/swagger-ui

EXPOSE 8080

CMD [ "/app/test" ]

