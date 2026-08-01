FROM gcc:latest

WORKDIR /usr/src/hospital_app

# 1. Install PostgreSQL development libraries
RUN apt-get update && apt-get install -y libpq-dev

# 2. Copy source code
COPY . /usr/src/hospital_app

# 3. Compile with explicit include path for PostgreSQL headers
RUN gcc -o hospital.cgi hospital.c -I/usr/include/postgresql -lpq

EXPOSE 8080

CMD ["./hospital.cgi"]
