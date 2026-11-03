#ifndef CONSISTENCIA_STATUS_H
#define CONSISTENCIA_STATUS_H

#include <ostream>

// Códigos comuns às duas representações de lista.
enum class ConsistenciaStatus
{
    OK,
    CICLO_DETECTADO,
    QUANTIDADE_INCORRETA,
    EXTREMIDADE_INCORRETA,
    SENTINELA_INCORRETA,
    ENCADEAMENTO_INCORRETO
};

inline std::ostream& operator<<(std::ostream& saida, ConsistenciaStatus status)
{
    switch (status)
    {
    case ConsistenciaStatus::OK: return saida << "OK";
    case ConsistenciaStatus::CICLO_DETECTADO: return saida << "CICLO_DETECTADO";
    case ConsistenciaStatus::QUANTIDADE_INCORRETA: return saida << "QUANTIDADE_INCORRETA";
    case ConsistenciaStatus::EXTREMIDADE_INCORRETA: return saida << "EXTREMIDADE_INCORRETA";
    case ConsistenciaStatus::SENTINELA_INCORRETA: return saida << "SENTINELA_INCORRETA";
    case ConsistenciaStatus::ENCADEAMENTO_INCORRETO: return saida << "ENCADEAMENTO_INCORRETO";
    }
    return saida << "ConsistenciaStatus desconhecido";
}

#endif
