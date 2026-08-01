#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> // PostgreSQL connection library

int main() {
    // HTTP Header for Web Response
    printf("Content-Type: application/json\n\n");

    // External Cloud Database Connection String (Supabase/Neon Pooler URL)
    const char *conninfo = "postgresql://postgres.xyzproject:password@aws-0-ap-south-1.pooler.supabase.com:6543/postgres";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        printf("{\"status\": \"error\", \"message\": \"%s\"}", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    // Query to fetch doctors and timings
    PGresult *res = PQexec(conn, "SELECT d.name, dep.dept_name, d.available_from, d.available_to FROM Doctors d JOIN Departments dep ON d.dept_id = dep.dept_id");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("{\"status\": \"error\", \"message\": \"Query failed\"}");
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    int rows = PQntuples(res);
    printf("{\"status\": \"success\", \"total_doctors\": %d, \"data\": [", rows);

    for (int i = 0; i < rows; i++) {
        printf("{\"doctor\": \"%s\", \"department\": \"%s\", \"from\": \"%s\", \"to\": \"%s\"}%s",
            PQgetvalue(res, i, 0),
            PQgetvalue(res, i, 1),
            PQgetvalue(res, i, 2),
            PQgetvalue(res, i, 3),
            (i < rows - 1) ? "," : ""
        );
    }
    printf("]}");

    PQclear(res);
    PQfinish(conn);
    return 0;
}
