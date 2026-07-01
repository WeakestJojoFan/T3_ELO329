# Tarea 3: Simulador Gráfico en C++ y Qt de EloTelTags y Aplicación Find My

**Ramo:** ELO329 – Diseño y Programación Orientados a Objetos  
**Semestre:** 1er semestre 2026


## Integrantes

| Nombre | Rol |
|--------|-----|
| Carlos Ramírez | Desarrollador |
| Nicolás King | Desarrollador |
| Yasin Morales | Desarrollador |
| Martin Pérez| Desarrollador |

## Descripción

Simulador gráfico en C++ y Qt de dispositivos de rastreo tipo AirTag (EloTelTag), celulares y tablets. Los dispositivos se mueven por el mapa (imagen especificada en config.txt), rebotan en los bordes, y se comunican con la nube (ETNube). La opción **FindMy** permite ver la última información disponible en la nuve para los dispositivos de un usuario en tiempo real. La opción **GFindMy** muestra los dispositivos en su última posición conocida en la nube.

---

## Estructura del repositiorio

```
Tarea2_elo/
├── Stage1/	Stage1: Abre una ventana de dialogo para elegir el archivo de configuración, muestra posición inicial de los celulares.
├── Stage2/	Stage2: Agrega Tablets y EloTelTag, los dispositivos se mueven por el mapa.
├── Stage3/	Stage3: Agrega ETNube y ventana FindMy. Tablets y tags muestran señal de radar. Se reporta posiciones a la nube. FindMy muestra los datos de la nube para un usuario (posición de sus dispositivos).
├── Stage4/	Stage4: Incorpora opción GFindMy del menú contextual, muestra una vista del territorio con los dispositivos en su última posición reportada. FindMy se actualiza con los últimos datos disponibles, y permite hacer seguimiento del camino recorrido por sus dispositivos.
└── resources/	Recursos de la simulación (archivo config.txt, imágen de fondo).
```
Cada etapa contiene:
- `CMakeLists.txt` - archivo de proyecto CMake/Qt.
- `*.cpp y *.h` - código fuente C++

---
# Requisitos

* **Qt Framework:** version 6.11.1
* **Build System:** CMake

---

# Compilación y ejecución

Cargar el proyecto Qt, cuando se pregunte por los kits seleccionar "Configurar proyecto", usar la opción **BUILD** y **RUN**.

Al ejecutar se abrirá un FileChooser para seleccionar el archivo `config.txt`.

---


## Archivo de configuración

Formato de `config.txt`:
```
<archivo_imagen>
<delta_tiempo>
<número_de_personas>
<nombre> <nTags> <tieneTablet(0|1)>
<x> <y> <rapidez> <angulo> <delta_angulo>
(<nombreTag> <x> <y> <rapidez> <angulo> <delta_angulo>)*
[<x> <y> <rapidez> <angulo> <delta_angulo>]   ← tablet (si tieneTablet=1)
```

Ejemplo incluido: `config.txt` con 3 personas (Pedro, Juan, Diego) sobre el mapa `Placeres.jpg`.

---

## Documentación

Ver [documentacion.html](documentacion.html) para el diagrama de clases completo y descripción de la arquitectura.