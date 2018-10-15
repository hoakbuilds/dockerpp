#include "shell.h"

void aviso (char *msg, int tempo){
    while (tempo > 0) {
    sleep (1);
        tempo--;
    }
    fprintf (stderr, "\n%sAviso:%s %s\n\n",KRYELLOW, KRYESET, msg );
}

void avisot (char *msg, int tempo, char *prompt){
    while (tempo > 0) {
    sleep (1);
        tempo--;
    }
    fprintf (stderr, "\n\n%sAviso:%s %s\n\n%s%s %s",KRYELLOW,KRYESET, msg,KRYED,prompt,KRYESET);
    
}

void * avisowrapper(void *args) {
    Aviso_t *avs = (Aviso_t *) args;
    avisot( avs->msg, avs->tempo, avs->prompt);
    free(avs);
    return NULL;
}
