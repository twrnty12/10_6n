#include "Prim.h"
//Использование мьютекса(mutex) необходимо для обеспечения потокобезопасности при доступе к переменной num в многопоточной среде.//
void ExampleRace::DoWork(uint32_t* num, bool mutexOn, int numIterat)
{
    if(mutexOn){
        for(uint32_t i = 0; i < numIterat; i++){
            mut->lock();
            (*num)++;
            mut->unlock();
        }
    }
    else{
        for(uint32_t i = 0; i < numIterat; i++){
            (*num)++;
        }
    }

    emit sig_Finish();
}
