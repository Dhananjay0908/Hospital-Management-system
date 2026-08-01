FROM gcc:latest
COPY . /usr/src/hospital_app
WORKDIR /usr/src/hospital_app
RUN apt-get update && apt-get install -y libpq-dev
RUN gcc -o hospital.cgi hospital.c -lpq
EXPOSE 8080
CMD ["./hospital.cgi"]
