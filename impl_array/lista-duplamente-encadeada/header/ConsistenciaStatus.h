#ifndef CONSISTENCIA_STATUS_H
#define CONSISTENCIA_STATUS_H

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

#endif
