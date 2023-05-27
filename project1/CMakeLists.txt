cmake_minimum_required(VERSION 3.23)
project(horario)

set(CMAKE_CXX_STANDARD 14)

add_executable(horario main.cpp Student.cpp Student.h TurmaH.cpp TurmaH.h Bloco.cpp Bloco.h GestaoHorario.cpp GestaoHorario.h UcTurma.cpp UcTurma.h Pedido.cpp Pedido.h)
