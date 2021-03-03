

## Scope 

Mini HTTP server that support YAML files to define APIs (Open API 3.0.0), and capable of refreshing the API list on runtime (through YAML file modification)
This dev was based on open source libs C++11 compatible and under MIT Licence.
The glue component was made withe spirit of wrapping and abstracting the frameworks/libs used to run the webserver and manage its configuration.

## known limitations

- Support only one yaml configuration file

## Future ameliorations

- Add the support of other webserver frameworks (other than cpp-httplib) like boost beast
- Add the support of other yaml parser (from boost)
- Add the possibility to use std::filesystem (C++17) to minitor configuration changes
- Support multiple configuration files
- Be able to select which frameworks/libs to use freely at buildtime (or maybe at runtime)

## How to Build

Tested on
---------------
Windows Linux subsystem + g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0 + cmake version 3.20.0-rc2

#### Commands
``` shell
   git clone --recurse-submodules https://github.com/hhaouala/exercice.git ; cd exercice
   mkdir build install
   cd build
   cmake -DJSON_MultipleHeaders=y  -DJSON_BuildTests=n -DJSON_Install=y  -DCMAKE_BUILD_TYPE=Debug -DYAML_CPP_INSTALL=ON -DYAML_BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=../install ..
   make
   make install
```

## Dependencies (to be installed on host computer)

- Doxygen

## Dependencies (submodules)

### cpp-httplib (https://github.com/yhirose/cpp-httplib.git)

### filewatch (https://github.com/ThomasMonkman/filewatch.git)

### yaml-cpp (https://github.com/jbeder/yaml-cpp.git)

### toJson (https://github.com/mircodezorzi/tojson.git)

### nlohmann json (https://github.com/nlohmann/json.git)

### Rapid XML (https://freefr.dl.sourceforge.net/project/rapidxml/rapidxml/rapidxml%201.13/rapidxml-1.13.zip)


