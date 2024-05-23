#pragma once
#include <string>
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include "Persona.h"

using namespace std;

class Estudiante : Persona {

private:
    int id_tipo_sangre, id_estudiante;

public:
    Estudiante() {}

    Estudiante(int estudiante, int cod, string nom, string ape, string dir, int tel, string fn, int sangre)
        : Persona(cod, nom, ape, dir, tel, fn) {
        id_tipo_sangre = sangre;
        id_estudiante = estudiante;
    }

    void setcodigo(int cod) { codigo = cod; }
    void setnombres(string nom) { nombres = nom; }
    void setapellidos(string ape) { apellidos = ape; }
    void setdireccion(string dir) { direccion = dir; }
    void settelefono(int tel) { telefono = tel; }
    void setfechanacimiento(string fn) { fecha_nacimiento = fn; }
    void setidtiposangre(int sangre) { id_tipo_sangre = sangre; }
    void setid_estudiante(int estudiante) { id_estudiante = estudiante; }

    int getcodigo() { return codigo; }
    string getnombres() { return nombres; }
    string getapellidos() { return apellidos; }
    string getdireccion() { return direccion; }
    int gettelefono() { return telefono; }
    string getfechanacimiento() { return fecha_nacimiento; }
    int getidtiposangre() { return id_tipo_sangre; }
    int getidestudiante() { return id_estudiante; }

    void crear() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string c = to_string(codigo);
            string t = to_string(telefono);
            string s = to_string(id_tipo_sangre);
            string insert = "INSERT INTO estudiantes (codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre)VALUES('" + c + "','" + nombres + "','" + apellidos + "','" + direccion + "','" + t + "','" + fecha_nacimiento + "','" + s + "');";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            } else {
                cout << "Error al ingresar..." << endl;
            }
        } else {
            cout << "---- Error de Conexion ----" << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultados;
        cn.abrir_conexion();
        if (cn.getConectar()) {
            string consulta = "select t.id_estudiante, t.codigo, t.nombres, apellidos, t.direccion, t.telefono, t.fecha_nacimiento, c.tipo_sangre from estudiantes t inner join tipos_sangre c on c.id_tipo_sangre = t.id_tipo_sangre;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), c);
            if (!q_estado) {
                resultados = mysql_store_result(cn.getConectar());
                cout << " -------------Estudiantes--------------" << endl;
                cout << "ID_ESTUDIANTE " << "|" << "CODIGO" << " | " << "NOMBRES" << "    | " << "APELLIDOS" << "   | " << "DIRECCION" << "   | " << "TELEFONO" << "  | " << "FECHA DE NACIMIENTO" << " | " << "TIPO DE SANGRE" << endl;
                while (fila = mysql_fetch_row(resultados)) {
                    cout << fila[0] << "             | " << fila[1] << "     | " << fila[2] << "      | " << fila[3] << "       | " << fila[4] << "      | " << fila[5] << "      | " << fila[6] << "   |       " << fila[7] << endl;
                }
            } else {
                cout << "Error al mostrar los datos" << endl;
            }
        } else {
            cout << "---- Error de Conexion ----" << endl;
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        string t = to_string(telefono);
        string c = to_string(codigo);
        string s = to_string(id_tipo_sangre);
        string ii = to_string(id_estudiante);
        if (cn.getConectar()) {
            string actualizar = "update estudiantes set codigo =" + c + ", nombres='" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion + "', telefono =" + t + ", fecha_nacimiento='" + fecha_nacimiento + "', id_tipo_sangre= '" + s + "' where id_estudiante = " + ii + "";
            const char* i = actualizar.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Actualizacion Exitosa ..." << endl;
            } else {
                cout << " xxx Error al Ingresar  xxx" << endl;
            }
        } else {
            cout << " xxx Error en la Conexion xxxx" << endl;
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        string p = to_string(id_estudiante);
        if (cn.getConectar()) {
            string borrar = "delete from estudiantes where id_estudiante= " + p + "";
            const char* i = borrar.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Eliminacion Exitosa ..." << endl;
            } else {
                cout << " xxx Error al Ingresar  xxx" << endl;
            }
        } else {
            cout << " xxx Error en la Conexion xxxx" << endl;
        }
        cn.cerrar_conexion();
    }
};
