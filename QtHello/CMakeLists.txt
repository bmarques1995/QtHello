# CMakeList.txt: projeto de CMake para QtSample, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
add_executable (QtSample "QtSample.cpp" "QtSample.h")

set_property(TARGET QtSample PROPERTY CXX_STANDARD 20)

# TODO: Adicione testes e instale destinos, se necessário.
