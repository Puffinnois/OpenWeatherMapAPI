#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<json-c/json.h> //  sudo apt-get install -y libjson-c-dev
#include <libpq-fe.h>

void do_exit(PGconn *conn, PGresult *res) {

    fprintf(stderr, "%s\n", PQerrorMessage(conn));

    PQclear(res);
    PQfinish(conn);

    exit(1);
}


int main() {


    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *main_obj;
    struct json_object *temp_obj;
    struct json_object *weather_obj;
    struct json_object *description_obj;
    struct json_object *humidity_obj;
    struct json_object *wind_obj;
    struct json_object *speed_obj;
    struct json_object *id_obj;

    double temp;
    int humidity;
    double wind_speed;
    int id;
    char weather_desc[10];
    char query[666];




    fp = fopen("weather.json","r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json,"main",&main_obj);
    json_object_object_get_ex(main_obj,"temp",&temp_obj);
    temp = json_object_get_double(temp_obj);
    temp = temp - 273;
    printf("temperature : %f\n", temp);

   /* json_object_object_get_ex(parsed_json,"weather",&weather_obj);
    json_object_object_get_ex(weather_obj,"description",&description_obj);
    strcpy(weather_desc[10], json_object_get_string(description_obj));
    printf("%s\n", weather_desc);*/

    json_object_object_get_ex(parsed_json,"main",&main_obj);
    json_object_object_get_ex(main_obj,"humidity",&humidity_obj);
    humidity = json_object_get_int(humidity_obj);
    printf("Humidity : %d\n", humidity);

    json_object_object_get_ex(parsed_json,"wind",&wind_obj);
    json_object_object_get_ex(wind_obj,"speed",&speed_obj);
    wind_speed = json_object_get_double(speed_obj);
    printf("Wind speed : %f\n", wind_speed);

    json_object_object_get_ex(parsed_json,"id",&id_obj);
    id = json_object_get_int(id_obj);
    printf("ID : %d\n", id);

    //to run mysql connection gcc -o output $(mysql_config --cflags) Connect.c $(mysql_config --libs)

    /*MYSQL* conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("MySQL initialization failed");
        return 1;
    }

    if (mysql_real_connect(conn, server, username, password, database, 0, NULL, 0) == NULL) {
        printf("Unable to connect with MySQL server\n");
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "CREATE TABLE Weather(temp DOUBLE, humidity INT, wind_speed DOUBLE)")) {
        printf("Unable to create database table in MyDb database\n");
        mysql_close(conn);
        return 1;
    }

    sprintf(query, "insert into Weather values(%f, %d, %f)", temp, humidity, wind_speed);
    if (mysql_query(conn, query)) {
        printf("Unable to insert data into Employee table\n");
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    printf("Data inserted successfully\n");

    return 0;*/

    PGconn *conn = PQconnectdb("host=practicephoenixazure.postgres.database.azure.com port=5432 user=practiceadmin@practicephoenixazure password=Respons11 dbname=easy_scooter sslmode=require");

    if (PQstatus(conn) == CONNECTION_BAD) {

        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));

        PQfinish(conn);
        exit(1);
    }

    sprintf(query, "INSERT INTO daily_weather (temperature, humidity, api_id) VALUES(%f, %d, %d)", temp, humidity, id);
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
        do_exit(conn, res);

    PQclear(res);

    PQfinish(conn);

    return 0;
}
