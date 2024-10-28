#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Okcular;

typedef struct {
    int sayi;
    int saldiri;    
    int savunma;
    int saglik;
    int kritik_sans;
} Piyadeler;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Suvariler;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Mizrakcilar;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Ork_Dovusculeri;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} kusatma_Makineleri;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Varg_Binicileri;

typedef struct {
    int sayi;
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
} Troller;


typedef struct {
    Okcular okcular;
    Piyadeler piyadeler;
    Suvariler suvariler;
    Ork_Dovusculeri ork_dovusculeri;
    Mizrakcilar mizrakcilar;
    kusatma_Makineleri kusatma_makineleri;
    Varg_Binicileri varg_binicileri;
    Troller troller;
} Birimler;

typedef struct {
char baslik[50];
int seviye;
int deger;
char aciklama[50];
char hedef[50];
} ArastirmaSeviyesi;

typedef struct 
{
    int etki_degeri;
    char etki_turu[50];
    char aciklama[50];
} CEtkiler;

typedef struct 
{
    int etki_degeri;
    char etki_turu[50];
    char aciklama[50];
} KEtkiler;


typedef struct {
    char kahramanlar[50];
    char canavarlar[50];
    CEtkiler cetkiler;
    KEtkiler ketkiler;
} KahramanlarVeCanavarlar;

typedef struct {
    Birimler birimler;
    ArastirmaSeviyesi arastirma_seviyesi;
    KahramanlarVeCanavarlar kahramanlar_ve_canavarlar;
} Fraksiyon;

typedef struct {
    Fraksiyon insan_imparatorlugu;
    Fraksiyon ork_legi;
} Oyuncular;
int extract_number(const char* json, const char* key) {
    char* found = strstr(json, key);
    if (found) {
        found = strchr(found, ':') + 1;
        return atoi(found);
    }
    return 0;
}

int extract_number2(char path_to_file[], char key[], char key2[]) {

    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        printf("%s bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ", path_to_file);
        return 1;
    }

    char buffer2[5000];
    char data[5000];
    int i = 0;

    while (i < sizeof(buffer2) - 1 && fscanf(fp, "%c", &buffer2[i]) != EOF) {
        data[i] = buffer2[i];
        i++;
    }

    data[i] = '\0';

    fclose(fp);
    char* found = strstr(data, key);
    char* found2 = strstr(found, key2);
    char output[5000];

    if (found2) {
        int i = 0;
        int j = 0;
        for (; found2[i-2] != ':'; i++)
            continue;

        for (; found2[i] != '\n'; i++) {
            if(found2[i] != ',') {
                output[j] = found2[i];
                j++;
            }
        }


        return atoi(output);
    }
}

int extract_string(char race[], char search[], char path[]) {
    char buffer[5000];
    char data[5000];
    int i = 0;
    
    FILE *fp = fopen("Files/file.json", "r");

    if(fp == NULL) {
        perror("Files/file.json bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ");
        return 1;
    }
    while (i < sizeof(buffer) - 1 && fscanf(fp, "%c", &buffer[i]) != EOF) {
        data[i] = buffer[i];
        i++;
    }

    data[i] = '\0'; 
    fclose(fp);

    char output[5000];


    char *result = strstr(data, race);
    if (result == NULL) {
        return 1;
    }

    char *start = strstr(result, search);
    if (start != NULL) {
        int j = 0;
        i = 0;

        for (; start[i-2] != '['; i++)
            continue;

        for (; start[i+1] != ']'; i++) {
            if (start[i] != ']') {
                output[j] = start[i];
                j++;
            }
        }

        output[j] = '\0';  

    } 
    strcpy(path, output);


    return 0;

}

int extract_effect(char path_to_file[], char Hero_Creature[], char search[], char path[]) {

    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        printf("%s bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ", path_to_file);
        return 1;
    }

    char buffer2[5000];
    char data[5000];
    int i = 0;

    while (i < sizeof(buffer2) - 1 && fscanf(fp, "%c", &buffer2[i]) != EOF) {
        data[i] = buffer2[i];
        i++;
    }

    data[i] = '\0';  

    fclose(fp);  

    char output[5000];

    char *result = strstr(data, Hero_Creature);
    if (result == NULL) {
        return 1;
    }

    char *start = strstr(result, search);
    if (start != NULL) {
        int j = 0;
        i = 0;

        for (; start[i-3] != ':'; i++)
            continue;

        for (; start[i] != '\"'; i++) {
            if (start[i] != '\"') {
                output[j] = start[i];
                j++;
            }
        }

        output[j] = '\0';  
    }

    strcpy(path, output);

    return 0;
}
int extract_effect2(char path_to_file[], char Hero_Creature[], int level, char path[]) {

    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        printf("%s bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ", path_to_file);
        return 1;
    }

    char buffer2[5000];
    char data[5000];
    int i = 0;

    while (i < sizeof(buffer2) - 1 && fscanf(fp, "%c", &buffer2[i]) != EOF) {
        data[i] = buffer2[i];
        i++;
    }

    data[i] = '\0';

    fclose(fp);  

    char output[5000];

    char *result = strstr(data, Hero_Creature);
    if (result == NULL) {
        return 1;
    }

    char *search;

    if(level == 1) {
        search = "seviye_1";
    } else if(level == 2) {
        search = "seviye_2";
    } else if(level == 3) {
        search = "seviye_3";
    }
    char *start2 = strstr(result, search);
    char *start = strstr(start2, "aciklama");

    if (start != NULL) {
        int j = 0;
        i = 0;

        for (; start[i-3] != ':'; i++)
            continue;

        for (; start[i] != '\"'; i++) {
            if (start[i] != '\"') {
                output[j] = start[i];
                j++;
            }
        }

        output[j] = '\0';  

    } 
    strcpy(path, output);

    return 0;
}

int extract_explaination(char path_to_file[], char Hero_Creature[], char path[]){


    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        printf("%s bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ", path_to_file);
        return 1;
    }

    char buffer[5000];
    char data[5000];
    int i = 0;
    KahramanlarVeCanavarlar oyuncular = { 0 };

    while (i < sizeof(buffer) - 1 && fscanf(fp, "%c", &buffer[i]) != EOF) {
        data[i] = buffer[i];
        i++;
    }

    data[i] = '\0';  
    fclose(fp);  

    char pos[5000];

    
    char *result = strstr(data, Hero_Creature);
    if (result == NULL) {
        return 1;
    }

       char *start = strstr(result, "aciklama");
    if (start != NULL) {
        int j = 0;
        i = 0;


    char *pos2;

    for(; start[i] != '}'; i++) {
        pos[i] = start[i];
    }

    pos[i] = '\0';

    if (strstr(pos, "piyadeler") != NULL) {
        pos2 = strstr(pos, "piyadeler");
        strcpy(path, "piyadeler");

    }
    else if (strstr(pos, "okcular") != NULL) {
        pos2 = strstr(pos, "okcular");
        strcpy(path, "okcular");

    }
    else if (strstr(pos, "suvariler") != NULL) {
        pos2 = strstr(pos, "suvariler");
        strcpy(path, "suvariler");

    }
    else if (strstr(pos, "kusatma_makineleri") != NULL) {
    pos2 = strstr(pos, "kusatma_makineleri");
    strcpy(path, "kusatma_makineleri");
}
    else if (strstr(pos, "ork_dovusculeri") != NULL) {
    pos2 = strstr(pos, "ork_dovusculeri");
    strcpy(path, "ork_dovusculeri");
}
    else if (strstr(pos, "mizrakcilar") != NULL) {
    pos2 = strstr(pos, "mizrakcilar");
    strcpy(path, "mizrakcilar");
}
    else if (strstr(pos, "varg_binicileri") != NULL) {
    pos2 = strstr(pos, "varg_binicileri");
    strcpy(path, "varg_binicileri");
}
    else if (strstr(pos, "troller") != NULL) {
    pos2 = strstr(pos, "troller");
    strcpy(path, "troller");
}
    else if(strstr(pos, "tum_birimler") != NULL) {
    pos2 = strstr(pos, "tum_birimler");
    strcpy(path, "tum_birimler");
}
    else {
    return 1;
}
    }
    return 0;
}

int extract_value(char path_to_file[], char Hero_Creature[], char search[]) {

    FILE *fp = fopen(path_to_file, "r");
    if (fp == NULL) {
        printf("%s bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ", path_to_file);
        return 1;
    }

    char buffer2[5000];
    char data[5000];
    int i = 0;

    while (i < sizeof(buffer2) - 1 && fscanf(fp, "%c", &buffer2[i]) != EOF) {
        data[i] = buffer2[i];
        i++;
    }


    data[i] = '\0';  

    fclose(fp);

    char output[5000];

     "ork_legi";
    char *result = strstr(data, Hero_Creature);
    if (result == NULL) {
        printf("Aranan dize bulunamadı.\n");
        return 1;
    }

     "kahramanlar";
    char *start = strstr(result, search);
    if (start != NULL) {
        int j = 0;
        i = 0;

         '[';
        for (; start[i-3] != ':'; i++)
            continue;

        for (; start[i] != '\"'; i++) {
            if (start[i] != '\"') {
                output[j] = start[i];
                j++;
            }
        }

    } 

    return atoi(output);
}

int extract_reseach(char race[], char search[], char path[], int path2) {
    char buffer[5000];
    char buffer2[5000];

    char data[5000];
    int i = 0;
    
    FILE *fp = fopen("Files/file.json", "r");
    while (i < sizeof(buffer) - 1 && fscanf(fp, "%c", &buffer[i]) != EOF) {
        data[i] = buffer[i];
        i++;
    }

        if (fp == NULL) {
        printf("Files/file.json bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ");
        return 1;
    }

    data[i] = '\0';  

    fclose(fp);

    char output[5000];

    char *result = strstr(data, race);
    if (result == NULL) {
        return 1;
    }

    char *start = strstr(result, search);
    if (start != NULL) {
        int j = 0;
        i = 0;

        for (; start[i-2] != '{'; i++)
            continue;
        for (; start[i-1] != '\"'; i++)
            continue;


        for (; start[i] != '\"'; i++) {

                output[j] = start[i];
                j++;


        output[j] = '\0';  
    } 
    }
    strcpy(path, output);

        return atoi(&start[i+3]);

}

int extract_reseach_value(char race[], int level) {
    char buffer[5000];
    char buffer2[5000];

    char data[5000];
    int i = 0;
    
    FILE *fp = fopen("Files/research.json", "r");
    while (i < sizeof(buffer) - 1 && fscanf(fp, "%c", &buffer[i]) != EOF) {
        data[i] = buffer[i];
        i++;
    }
        if (fp == NULL) {
        printf("Files/research.json bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun. ");
        return 1;
    }

    data[i] = '\0';  

    fclose(fp);

    char output[5000];

    char *result = strstr(data, race);
    if (result == NULL) {
        return 1;
    }

    if (level == 1) {

        char *start = strstr(result, "seviye_1");
        if (start != NULL) {
            int j = 0;
            i = 0;

            for (; start[i-2] != '{'; i++)
            continue;
            for (; start[i-3] != ':'; i++)
            continue;

            for (; start[i] != '\"'; i++) {

                output[j] = start[i];
                j++;
            }
            output[j] = '\0';
        } 
    }
    else if(level == 2) {
        char *start = strstr(result, "seviye_2");
        if (start != NULL) {
            int j = 0;
            i = 0;

            for (; start[i-2] != '{'; i++)
            continue;
            for (; start[i-3] != ':'; i++)
            continue;

            for (; start[i] != '\"'; i++) {

                output[j] = start[i];
                j++;
            }
            output[j] = '\0';
        }
    }
    else if(level == 3) {
        char *start = strstr(result, "seviye_3");
        if (start != NULL) {
            int j = 0;
            i = 0;

            for (; start[i-2] != '{'; i++)
            continue;
            for (; start[i-3] != ':'; i++)
            continue;

            for (; start[i] != '\"'; i++) {

                output[j] = start[i];
                j++;
            }
            output[j] = '\0';
        }
    }

    return atoi(output);

}

void json_parse(const char* json, Oyuncular* oyuncular) {
    // İnsana ait birimleri ve araştırma seviyesini ayrıştır
    oyuncular->insan_imparatorlugu.birimler.piyadeler.sayi = extract_number(json, "piyadeler");
    oyuncular->insan_imparatorlugu.birimler.suvariler.sayi = extract_number(json, "suvariler");
    oyuncular->insan_imparatorlugu.birimler.okcular.sayi = extract_number(json, "okcular");
    oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.sayi = extract_number(json, "kusatma_makineleri");


    // Orklara ait birimleri ve araştırma seviyesini ayrıştır
    oyuncular->ork_legi.birimler.ork_dovusculeri.sayi = extract_number(json, "ork_dovusculeri");
    oyuncular->ork_legi.birimler.varg_binicileri.sayi = extract_number(json, "varg_binicileri");
    oyuncular->ork_legi.birimler.mizrakcilar.sayi = extract_number(json, "mizrakcilar");
    oyuncular->ork_legi.birimler.troller.sayi = extract_number(json, "troller");


    extract_string("insan_imparatorlugu", "kahramanlar", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar);
    extract_string("insan_imparatorlugu", "canavarlar", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar);

    // Ork kahramanları ve canavarları ayrıştır
    extract_string("ork_legi", "kahramanlar", oyuncular->ork_legi.kahramanlar_ve_canavarlar.kahramanlar);
    extract_string("ork_legi", "canavarlar", oyuncular->ork_legi.kahramanlar_ve_canavarlar.canavarlar);




    //kahraman ve canavarların etki türlerini ayrıştır
    extract_effect("Files/creatures.json", oyuncular->ork_legi.kahramanlar_ve_canavarlar.canavarlar, "etki_turu", oyuncular->ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu);
    extract_effect("Files/creatures.json", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, "etki_turu", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu);

    extract_effect("Files/heroes.json", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, "bonus_turu", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu);
    extract_effect("Files/heroes.json", oyuncular->ork_legi.kahramanlar_ve_canavarlar.kahramanlar, "bonus_turu", oyuncular->ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu);

    extract_explaination("Files/creatures.json" ,oyuncular->ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular->ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama);
    extract_explaination("Files/creatures.json" ,oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama);
    extract_explaination("Files/heroes.json" ,oyuncular->ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular->ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama);
    extract_explaination("Files/heroes.json" ,oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama);


    //kahraman ve canavarların etki degerlerini ayrıştır
    oyuncular->ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri = extract_value("Files/creatures.json", oyuncular->ork_legi.kahramanlar_ve_canavarlar.canavarlar, "etki_degeri");
    oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri = extract_value("Files/creatures.json", oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, "etki_degeri");
    oyuncular->ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri = extract_value("Files/heroes.json", oyuncular->ork_legi.kahramanlar_ve_canavarlar.kahramanlar, "bonus_degeri");
    oyuncular->insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri = extract_value("Files/heroes.json", oyuncular->ork_legi.kahramanlar_ve_canavarlar.kahramanlar, "bonus_degeri");

    
    //arastirma seviyesini ayrıştır
    oyuncular->ork_legi.arastirma_seviyesi.seviye = extract_reseach("ork_legi", "arastirma_seviyesi", oyuncular->ork_legi.arastirma_seviyesi.baslik, oyuncular->ork_legi.arastirma_seviyesi.seviye);
    oyuncular->insan_imparatorlugu.arastirma_seviyesi.seviye = extract_reseach("insan_imparatorlugu", "arastirma_seviyesi", oyuncular->insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular->insan_imparatorlugu.arastirma_seviyesi.seviye);

    //arastirma degerini ayrıstir
    oyuncular->ork_legi.arastirma_seviyesi.deger = extract_reseach_value(oyuncular->ork_legi.arastirma_seviyesi.baslik, oyuncular->ork_legi.arastirma_seviyesi.seviye);
    oyuncular->insan_imparatorlugu.arastirma_seviyesi.deger = extract_reseach_value(oyuncular->insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular->insan_imparatorlugu.arastirma_seviyesi.seviye);


    //arastirmanın aciklamasini ayristirir
    extract_explaination("Files/research.json", oyuncular->ork_legi.arastirma_seviyesi.baslik, oyuncular->ork_legi.arastirma_seviyesi.hedef);
    extract_explaination("Files/research.json", oyuncular->insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular->insan_imparatorlugu.arastirma_seviyesi.hedef);



    //birliklerin degerlerini ayristirir
    if(oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.sayi != 0) {
        oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.kritik_sans = extract_number2("Files/unit_types.json", "kusatma_makineleri", "kritik_sans");
        oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.saldiri = extract_number2("Files/unit_types.json", "kusatma_makineleri", "saldiri");
        oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.savunma = extract_number2("Files/unit_types.json", "kusatma_makineleri", "savunma");
        oyuncular->insan_imparatorlugu.birimler.kusatma_makineleri.saglik = extract_number2("Files/unit_types.json", "kusatma_makineleri", "saglik");
    }
    if (oyuncular->insan_imparatorlugu.birimler.okcular.sayi != 0) {
        oyuncular->insan_imparatorlugu.birimler.okcular.kritik_sans = extract_number2("Files/unit_types.json", "okcular", "kritik_sans");
        oyuncular->insan_imparatorlugu.birimler.okcular.saldiri = extract_number2("Files/unit_types.json", "okcular", "saldiri");
        oyuncular->insan_imparatorlugu.birimler.okcular.savunma = extract_number2("Files/unit_types.json", "okcular", "savunma");
        oyuncular->insan_imparatorlugu.birimler.okcular.saglik = extract_number2("Files/unit_types.json", "okcular", "saglik");
    }
    if(oyuncular->insan_imparatorlugu.birimler.piyadeler.sayi != 0) {
        oyuncular->insan_imparatorlugu.birimler.piyadeler.kritik_sans = extract_number2("Files/unit_types.json", "piyadeler", "kritik_sans");
        oyuncular->insan_imparatorlugu.birimler.piyadeler.saldiri = extract_number2("Files/unit_types.json", "piyadeler", "saldiri");
        oyuncular->insan_imparatorlugu.birimler.piyadeler.savunma = extract_number2("Files/unit_types.json", "piyadeler", "savunma");
        oyuncular->insan_imparatorlugu.birimler.piyadeler.saglik = extract_number2("Files/unit_types.json", "piyadeler", "saglik");
    }
    if(oyuncular->insan_imparatorlugu.birimler.suvariler.sayi != 0) {
        oyuncular->insan_imparatorlugu.birimler.suvariler.kritik_sans = extract_number2("Files/unit_types.json", "suvariler", "kritik_sans");
        oyuncular->insan_imparatorlugu.birimler.suvariler.saldiri = extract_number2("Files/unit_types.json", "suvariler", "saldiri");
        oyuncular->insan_imparatorlugu.birimler.suvariler.savunma = extract_number2("Files/unit_types.json", "suvariler", "savunma");
        oyuncular->insan_imparatorlugu.birimler.suvariler.saglik = extract_number2("Files/unit_types.json", "suvariler", "saglik");
    }
    if(oyuncular->ork_legi.birimler.ork_dovusculeri.sayi != 0) {
        oyuncular->ork_legi.birimler.ork_dovusculeri.kritik_sans = extract_number2("Files/unit_types.json", "ork_dovusculeri", "kritik_sans");
        oyuncular->ork_legi.birimler.ork_dovusculeri.saldiri = extract_number2("Files/unit_types.json", "ork_dovusculeri", "saldiri");
        oyuncular->ork_legi.birimler.ork_dovusculeri.savunma = extract_number2("Files/unit_types.json", "ork_dovusculeri", "savunma");
        oyuncular->ork_legi.birimler.ork_dovusculeri.saglik = extract_number2("Files/unit_types.json", "ork_dovusculeri", "saglik");
    }
    if(oyuncular->ork_legi.birimler.mizrakcilar.sayi != 0) {
        
        oyuncular->ork_legi.birimler.mizrakcilar.kritik_sans = extract_number2("Files/unit_types.json", "mizrakcilar", "kritik_sans");
        oyuncular->ork_legi.birimler.mizrakcilar.saldiri = extract_number2("Files/unit_types.json", "mizrakcilar", "saldiri");
        oyuncular->ork_legi.birimler.mizrakcilar.savunma = extract_number2("Files/unit_types.json", "mizrakcilar", "savunma");
        oyuncular->ork_legi.birimler.mizrakcilar.saglik = extract_number2("Files/unit_types.json", "mizrakcilar", "saglik");
    }
    if(oyuncular->ork_legi.birimler.varg_binicileri.sayi != 0) {
        oyuncular->ork_legi.birimler.varg_binicileri.kritik_sans = extract_number2("Files/unit_types.json", "varg_binicileri", "kritik_sans");
        oyuncular->ork_legi.birimler.varg_binicileri.saldiri = extract_number2("Files/unit_types.json", "varg_binicileri", "saldiri");
        oyuncular->ork_legi.birimler.varg_binicileri.savunma = extract_number2("Files/unit_types.json", "varg_binicileri", "savunma");
        oyuncular->ork_legi.birimler.varg_binicileri.saglik = extract_number2("Files/unit_types.json", "varg_binicileri", "saglik");
    }
    if(oyuncular->ork_legi.birimler.troller.sayi != 0) {
        oyuncular->ork_legi.birimler.troller.kritik_sans = extract_number2("Files/unit_types.json", "troller", "kritik_sans");
        oyuncular->ork_legi.birimler.troller.saldiri = extract_number2("Files/unit_types.json", "troller", "saldiri");
        oyuncular->ork_legi.birimler.troller.savunma = extract_number2("Files/unit_types.json", "troller", "savunma");
        oyuncular->ork_legi.birimler.troller.saglik = extract_number2("Files/unit_types.json", "troller", "saglik");
    }

    extract_effect2( "Files/research.json",  oyuncular->insan_imparatorlugu.arastirma_seviyesi.baslik,  oyuncular->insan_imparatorlugu.arastirma_seviyesi.seviye,  oyuncular->insan_imparatorlugu.arastirma_seviyesi.aciklama);

    extract_effect2( "Files/research.json",  oyuncular->ork_legi.arastirma_seviyesi.baslik,  oyuncular->ork_legi.arastirma_seviyesi.seviye,  oyuncular->ork_legi.arastirma_seviyesi.aciklama);

}

int write_data(const char* url, const char* file_name) {
        CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "init failed\n");
        return 1;
    }
    FILE *fp = fopen(file_name, "w");  
    if (!fp) {
        perror("Dosya açılamadı");
        return 1;
    }  
    

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);   


    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        return 1;
    }
    curl_easy_cleanup(curl);
    fclose(fp);

    return 0;
}








#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define HEX_SIZE 50
#define HEALTH_BAR_WIDTH 25 
#define HEALTH_BAR_HEIGHT 5 

typedef struct {
    int x, y;
    float health;
    int units;
    SDL_Texture *texture; 
} Hex;

void drawHexagon(SDL_Renderer *renderer, int x, int y, int size) {
    const double angle_step = M_PI / 3.0; 
    SDL_Point points[7]; 

    for (int i = 0; i < 6; i++) {
        double angle = i * angle_step;
        points[i].x = x + size * cos(angle);
        points[i].y = y + size * sin(angle);
    }
    points[6] = points[0]; 

    SDL_RenderDrawLines(renderer, points, 7);
}

void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int size) {
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

    int new_width = size * 1.5; 
    int new_height = (texture_height * new_width) / texture_width; 

    SDL_Rect renderQuad = {
        x - new_width / 2,
        y - new_height / 2,
        new_width,
        new_height
    };

    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

void drawHealthBar(SDL_Renderer *renderer, Hex hex);


void drawHealthBar(SDL_Renderer *renderer, Hex hex) {
    float healthPercentage = (float)hex.health;
    
    float barWidth = HEALTH_BAR_WIDTH * healthPercentage;
    
    float barX = hex.x - (HEALTH_BAR_WIDTH / 2);
    float barY = hex.y - HEX_SIZE - HEALTH_BAR_HEIGHT + 10;
    

    if(hex.health < 0.2) {

    }
    else if(hex.health < 0.5) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // sarı renk
    }
    else
    {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // yeşil renk
        
    }
    SDL_Rect healthBarRect = { barX, barY, barWidth, HEALTH_BAR_HEIGHT };
    SDL_RenderFillRect(renderer, &healthBarRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // Beyaz renk
}



void drawText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, const char *text) {
    SDL_Color color = {255, 255, 255, 255}; // Beyaz renk
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_Rect renderQuad = {x - text_width / 2, y - text_height / 2, text_width, text_height};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
int main(void) {
    
    int scene;
    scanf("%d", &scene);

   switch (scene)
   {
   case 1:
        write_data("https://yapbenzet.org.tr/1.json", "Files/file.json");
    break;
    case 2:
        write_data("https://yapbenzet.org.tr/2.json", "Files/file.json");
    break;
    case 3:
        write_data("https://yapbenzet.org.tr/3.json", "Files/file.json");
    break;
    case 4:
        write_data("https://yapbenzet.org.tr/4.json", "Files/file.json");
    break;
    case 5:
        write_data("https://yapbenzet.org.tr/5.json", "Files/file.json");
    break;
    case 6:
        write_data("https://yapbenzet.org.tr/6.json", "Files/file.json");
    break;
    case 7:
        write_data("https://yapbenzet.org.tr/7.json", "Files/file.json");
    break;
    case 8:
        write_data("https://yapbenzet.org.tr/8.json", "Files/file.json");
    break;
    case 9:
        write_data("https://yapbenzet.org.tr/9.json", "Files/file.json");
    break;
    case 10:
        write_data("https://yapbenzet.org.tr/10.json", "Files/file.json");
    break;

   
   default:
    printf("Hatalı sayı girdiniz\n");
    break;
   }



   FILE* file = fopen("Files/file.json", "r");
    if (file == NULL) {
        printf("Files/file.json bulunamadı dosyanın doğru isimde ve doğru dizinde olduğundan emin olun.\n");
        return 1;
    }

    char buffer[1024];
    char json_data[1024] = { 0 };

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        strcat(json_data, buffer);
    }
    fclose(file);

    Oyuncular oyuncular = { 0 };



    json_parse(json_data, &oyuncular);


   
    FILE *savas = fopen("savas_sim.txt", "w");



        //insanalr
        fprintf(savas, "İnsan İmparatorluğu:\n\n");
        if (oyuncular.insan_imparatorlugu.birimler.piyadeler.sayi > 0) {
            fprintf(savas, "    Piyadeler: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.insan_imparatorlugu.birimler.piyadeler.sayi, oyuncular.insan_imparatorlugu.birimler.piyadeler.saldiri, oyuncular.insan_imparatorlugu.birimler.piyadeler.savunma, oyuncular.insan_imparatorlugu.birimler.piyadeler.saglik, oyuncular.insan_imparatorlugu.birimler.piyadeler.kritik_sans);
            
        }
        if (oyuncular.insan_imparatorlugu.birimler.okcular.sayi > 0) {
            fprintf(savas, "    Okçular: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.insan_imparatorlugu.birimler.okcular.sayi, oyuncular.insan_imparatorlugu.birimler.okcular.saldiri, oyuncular.insan_imparatorlugu.birimler.okcular.savunma, oyuncular.insan_imparatorlugu.birimler.okcular.saglik, oyuncular.insan_imparatorlugu.birimler.okcular.kritik_sans);
            
        }
        if (oyuncular.insan_imparatorlugu.birimler.suvariler.sayi > 0) {
            fprintf(savas, "    Süvariler: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.insan_imparatorlugu.birimler.suvariler.sayi, oyuncular.insan_imparatorlugu.birimler.suvariler.saldiri, oyuncular.insan_imparatorlugu.birimler.suvariler.savunma, oyuncular.insan_imparatorlugu.birimler.suvariler.saglik, oyuncular.insan_imparatorlugu.birimler.suvariler.kritik_sans);
        }
        if (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.sayi > 0) {
            fprintf(savas, "    Kuşatma_Makineleri: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.sayi, oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.saldiri, oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.savunma, oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.saglik, oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.kritik_sans);
            
        }
        //kahraman ve canavar
        fprintf(savas, "\n");
        
        fprintf(savas, "Kahramanlar ve Canavarlar:\n\n");
        fprintf(savas, "    Kahraman %s (%s %%%d %s gücü bonusu)\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu);
        fprintf(savas, "    Canavar %s (%s %%%d %s gücü bonusu)\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu);


        fprintf(savas, "\n");
        //orklar
        fprintf(savas, "Orklar:\n\n");
        
        if (oyuncular.ork_legi.birimler.ork_dovusculeri.sayi > 0) {
            fprintf(savas, "    Ork_dovusculeri: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.ork_legi.birimler.ork_dovusculeri.sayi, oyuncular.ork_legi.birimler.ork_dovusculeri.saldiri, oyuncular.ork_legi.birimler.ork_dovusculeri.savunma, oyuncular.ork_legi.birimler.ork_dovusculeri.saglik, oyuncular.ork_legi.birimler.ork_dovusculeri.kritik_sans);
        }
        if (oyuncular.ork_legi.birimler.mizrakcilar.sayi > 0) {
            fprintf(savas, "    Mızrakçılar: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.ork_legi.birimler.mizrakcilar.sayi, oyuncular.ork_legi.birimler.mizrakcilar.saldiri, oyuncular.ork_legi.birimler.mizrakcilar.savunma, oyuncular.ork_legi.birimler.mizrakcilar.saglik, oyuncular.ork_legi.birimler.mizrakcilar.kritik_sans);
        }
        if (oyuncular.ork_legi.birimler.varg_binicileri.sayi > 0) {
            fprintf(savas, "    varg_binicileri: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.ork_legi.birimler.varg_binicileri.sayi, oyuncular.ork_legi.birimler.varg_binicileri.saldiri, oyuncular.ork_legi.birimler.varg_binicileri.savunma, oyuncular.ork_legi.birimler.varg_binicileri.saglik, oyuncular.ork_legi.birimler.varg_binicileri.kritik_sans);
        }
        if (oyuncular.ork_legi.birimler.troller.sayi > 0) {
            fprintf(savas, "    Troller: %d birim(saldırı gücü: %d, savunma gücü: %d, sağlık: %d, kritik vuruş şansı: %d)\n",oyuncular.ork_legi.birimler.troller.sayi, oyuncular.ork_legi.birimler.troller.saldiri, oyuncular.ork_legi.birimler.troller.savunma, oyuncular.ork_legi.birimler.troller.saglik, oyuncular.ork_legi.birimler.troller.kritik_sans);
        }
        fprintf(savas, "\n");
        fprintf(savas, "Kahramanlar ve Canavarlar:\n\n");
        
        fprintf(savas, "    Kahraman %s (%s %%%d %s gücü bonusu)\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu);
        fprintf(savas, "    Canavar %s (%s %%%d %s gücü bonusu)\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu);

        //arastırmalar
        fprintf(savas, "\n");
        fprintf(savas, "Araştırmalar: \n\n");
        fprintf(savas, "    İnsan İmparatorluğu: \n");
        fprintf(savas, "     %s (seviye %d): %s ", oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular.insan_imparatorlugu.arastirma_seviyesi.seviye, oyuncular.insan_imparatorlugu.arastirma_seviyesi.aciklama);
        fprintf(savas, "\n");
        fprintf(savas, "    Orklar: \n");
        fprintf(savas, "     %s (seviye %d): %s ", oyuncular.ork_legi.arastirma_seviyesi.baslik, oyuncular.ork_legi.arastirma_seviyesi.seviye, oyuncular.ork_legi.arastirma_seviyesi.aciklama);
        fprintf(savas, "\n\n");

        
        float insanlar_saldiri ;
        float orklar_saldiri ;
        float insanlar_savunma ;
        float orklar_savunma ;

        float net_hasar;

        float piyadeler_saldiri = (oyuncular.insan_imparatorlugu.birimler.piyadeler.saldiri);
        float piyadeler_savunma = (oyuncular.insan_imparatorlugu.birimler.piyadeler.savunma);
        float piyadeler_saglik = (oyuncular.insan_imparatorlugu.birimler.piyadeler.saglik);
        int piyadeler_sayi = (oyuncular.insan_imparatorlugu.birimler.piyadeler.sayi);
        int piyadeler_kritik_sans = (oyuncular.insan_imparatorlugu.birimler.piyadeler.kritik_sans);
        int piyadeler_kayip = 0;
        int piyadeler_sayig = (oyuncular.insan_imparatorlugu.birimler.piyadeler.sayi);



        float okcular_saldiri = (oyuncular.insan_imparatorlugu.birimler.okcular.saldiri);
        float okcular_savunma = (oyuncular.insan_imparatorlugu.birimler.okcular.savunma);
        int okcular_sayi = (oyuncular.insan_imparatorlugu.birimler.okcular.sayi);
        float okcular_saglik = (oyuncular.insan_imparatorlugu.birimler.okcular.saglik);
        int okcular_kritik_sans = (oyuncular.insan_imparatorlugu.birimler.okcular.kritik_sans);
        int okcular_kayip = 0;
        int okcular_sayig = (oyuncular.insan_imparatorlugu.birimler.okcular.sayi);




        float suvariler_saldiri = (oyuncular.insan_imparatorlugu.birimler.suvariler.saldiri);
        float suvariler_savunma = (oyuncular.insan_imparatorlugu.birimler.suvariler.savunma);
        int suvariler_sayi = (oyuncular.insan_imparatorlugu.birimler.suvariler.sayi);
        float suvariler_saglik = (oyuncular.insan_imparatorlugu.birimler.suvariler.saglik);
        int suvariler_kritik_sans = (oyuncular.insan_imparatorlugu.birimler.suvariler.kritik_sans);
        int suvariler_kayip = 0;
        int suvariler_sayig = (oyuncular.insan_imparatorlugu.birimler.suvariler.sayi);




        float kusatma_makineleri_saldiri = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.saldiri);
        float kusatma_makineleri_savunma = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.savunma);
        int kusatma_makineleri_sayi = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.sayi);
        float kusatma_makineleri_saglik = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.saglik);
        int kusatma_makineleri_kritik_sans = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.kritik_sans);
        int kusatma_makineleri_kayip = 0;
        int kusatma_makineleri_sayig = (oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.sayi);



        //orklar
        float mizrakcilar_saldiri = (oyuncular.ork_legi.birimler.mizrakcilar.saldiri);
        float mizrakcilar_savunma = (oyuncular.ork_legi.birimler.mizrakcilar.savunma);
        int mizrakcilar_sayi = (oyuncular.ork_legi.birimler.mizrakcilar.sayi);
        float mizrakcilar_saglik = (oyuncular.ork_legi.birimler.mizrakcilar.saglik);
        int mizrakcilar_kritik_sans = (oyuncular.ork_legi.birimler.mizrakcilar.kritik_sans);
        int mizrakcilar_kayip = 0;
        int mizrakcilar_sayig = (oyuncular.ork_legi.birimler.mizrakcilar.sayi);



        float ork_dovusculeri_saldiri = (oyuncular.ork_legi.birimler.ork_dovusculeri.saldiri);
        float ork_dovusculeri_savunma = (oyuncular.ork_legi.birimler.ork_dovusculeri.savunma);
        int ork_dovusculeri_sayi = (oyuncular.ork_legi.birimler.ork_dovusculeri.sayi);
        float ork_dovusculeri_saglik = (oyuncular.ork_legi.birimler.ork_dovusculeri.saglik);
        int ork_dovusculeri_kritik_sans = (oyuncular.ork_legi.birimler.ork_dovusculeri.kritik_sans);
        int ork_dovusculeri_kayip = 0;
        int ork_dovusculeri_sayig = (oyuncular.ork_legi.birimler.ork_dovusculeri.sayi);



        float varg_binicileri_saldiri = (oyuncular.ork_legi.birimler.varg_binicileri.saldiri);
        float varg_binicileri_savunma = (oyuncular.ork_legi.birimler.varg_binicileri.savunma);
        int varg_binicileri_sayi = (oyuncular.ork_legi.birimler.varg_binicileri.sayi);
        float varg_binicileri_saglik = (oyuncular.ork_legi.birimler.varg_binicileri.saglik);
        int varg_binicileri_kritik_sans = (oyuncular.ork_legi.birimler.varg_binicileri.kritik_sans);
        int varg_binicileri_kayip = 0;
        int varg_binicileri_sayig = (oyuncular.ork_legi.birimler.varg_binicileri.sayi);



        float troller_saldiri = (oyuncular.ork_legi.birimler.troller.saldiri);
        float troller_savunma = (oyuncular.ork_legi.birimler.troller.savunma);
        int troller_sayi = (oyuncular.ork_legi.birimler.troller.sayi);
        float troller_saglik = (oyuncular.ork_legi.birimler.troller.saglik);
        int troller_kritik_sans = (oyuncular.ork_legi.birimler.troller.kritik_sans);
        int troller_kayip = 0;
        int troller_sayig = (oyuncular.ork_legi.birimler.troller.sayi);


    for (int adim = 1; adim != 1000; adim++) {

        fprintf(savas, "\nAdım %d: İnsan imparatorluğu'nun Saldırısı \n\n", adim); 
        fprintf(savas, "1. Saldırı gücü hesaplaması(Araştırma ve Canavar Etkileri Dahil): \n\n");
        
        if(piyadeler_sayi > 0) { 


                fprintf(savas, "Piyadeler: %d birim x %.f saldırı gücü = %.f\n", piyadeler_sayi, piyadeler_saldiri, (piyadeler_sayi * piyadeler_saldiri));
                
                    piyadeler_saldiri = piyadeler_saldiri * piyadeler_sayi;
                
                if(adim == 1){
                    fprintf(savas, "(");
                }
            if ((adim == 1) && 
                (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "piyadeler") == 0) || 
                 (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0))) {
                
                piyadeler_saldiri *= (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", 
                        oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, 
                        oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, 
                        piyadeler_saldiri);
                //printf("%s\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu);
            }

            if ((adim == 1) && 
                (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "piyadeler") == 0) || 
                 (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0))) {
                
                piyadeler_saldiri *= (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", 
                        oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, 
                        oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, 
                        piyadeler_saldiri);
            }

            if ((adim == 1) && 
                (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "piyadeler") == 0) || 
                 (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0))) {
                
                piyadeler_saldiri *= (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %f", 
                        oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, 
                        piyadeler_saldiri);
            }

            if (adim == 1) {
                fprintf(savas, ")\n");
            }

            if ((adim != 1) && ((adim - 1) % 10) == 0) {
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı Piyadelerin yeni saldırı gücü: %f\n", piyadeler_saldiri * 0.9);
                piyadeler_saldiri *= 0.9;
            }

            if (adim == 1) {
                if ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "elit_egitim") == 0) && ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "piyadeler") == 0) || (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "Elit_egitim araştırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            piyadeler_kritik_sans, 
                            oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, 
                            piyadeler_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);

                    piyadeler_kritik_sans += oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger;
                }
                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "piyadeler") == 0) || (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, 
                            piyadeler_kritik_sans, 
                            oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, 
                            piyadeler_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);

                    piyadeler_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }
                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "piyadeler") == 0) || (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, 
                            piyadeler_kritik_sans, 
                            oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, 
                            piyadeler_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);

                    piyadeler_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "piyadeler kritik şans: %d\n", piyadeler_kritik_sans);
                //printf("ilk adım: %d\n", adim);

                
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((piyadeler_kritik_sans / 100.0), -1)) == 0)) {
                    piyadeler_saldiri *= 1.5;
                    fprintf(savas, "piyadelerin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", piyadeler_saldiri);
                    //printf("333\n");
                }

        

            //kritik şansı  vuruşu eklemeyi unutma;
        }

        //okcular
        if(okcular_sayi > 0) { 


            fprintf(savas, "okçular: %d birim x %.f saldırı gücü = %.f\n", okcular_sayi, okcular_saldiri, (okcular_sayi * okcular_saldiri));
            
                
                okcular_saldiri = okcular_sayi * okcular_saldiri;
            

            if(adim == 1){
                fprintf(savas, "(");
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "okcular") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                
                okcular_saldiri = okcular_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, okcular_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "okcular") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                
                okcular_saldiri = okcular_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, okcular_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "okcular") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                
                okcular_saldiri = okcular_saldiri * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %f", oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, okcular_saldiri);
            }

            if (adim == 1) {
                fprintf(savas, ")\n");
            }

            if ((adim != 1) && ((adim - 1) % 10) == 0) {
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı Okçuların yeni saldırı gücü: %f\n", okcular_saldiri * 0.9);
                okcular_saldiri = okcular_saldiri * 0.9;
            }

            if (adim == 1) {
                if ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "elit_egitim") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "okcular") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "Elit_egitim arastırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", okcular_kritik_sans, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, okcular_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);
                    okcular_kritik_sans += oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "okcular") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, okcular_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, okcular_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri);
                    okcular_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "okcular") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, okcular_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, okcular_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri);
                    okcular_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "okcular kritik şans: %d\n", okcular_kritik_sans);

                
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((okcular_kritik_sans / 100.0), -1)) == 0)) {
                    okcular_saldiri *= 1.5;
                    fprintf(savas, "okçuların saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", okcular_saldiri);
                }

        }
        //süvariler
        if(suvariler_sayi > 0) { 


            fprintf(savas, "Süvariler: %d birim x %.f saldırı gücü = %.f\n", suvariler_sayi, suvariler_saldiri, (suvariler_sayi * suvariler_saldiri));
            
            
                suvariler_saldiri = suvariler_sayi * suvariler_saldiri;
            
            if(adim == 1){
                fprintf(savas, "(");
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "suvariler") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                
                suvariler_saldiri = suvariler_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, suvariler_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "suvariler") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                
                suvariler_saldiri = suvariler_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, suvariler_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "suvariler") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                
                suvariler_saldiri = suvariler_saldiri * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %f", oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, suvariler_saldiri);
            }

            if (adim == 1) {
                fprintf(savas, ")\n");
            }

            if ((adim != 1) && ((adim - 1) % 10) == 0) {
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı Süvarilerin yeni saldırı gücü: %f\n", suvariler_saldiri * 0.9);
                suvariler_saldiri = suvariler_saldiri * 0.9;
            }

            if (adim == 1) {
                if ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "elit_egitim") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "suvariler") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "Elit_egitim arastırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", suvariler_kritik_sans, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, suvariler_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);
                    suvariler_kritik_sans += oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "suvariler") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, suvariler_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, suvariler_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri);
                    suvariler_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "suvariler") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, suvariler_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, suvariler_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri);
                    suvariler_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "süvariler kritik şans: %d\n", suvariler_kritik_sans);

                
            }
            if (adim != 1 && ((adim-1) % (int)ceil(pow((suvariler_kritik_sans / 100.0), -1)) == 0)) {
                    suvariler_saldiri *= 1.5;
                    fprintf(savas, "süvarilerin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", suvariler_saldiri);
                }

        }
        //kusatma_makineleri
        if(kusatma_makineleri_sayi > 0) { 


            fprintf(savas, "kusatma_makineleri: %d birim x %.f saldırı gücü = %.f\n", kusatma_makineleri_sayi, kusatma_makineleri_saldiri, (kusatma_makineleri_sayi * kusatma_makineleri_saldiri));
                
                
            kusatma_makineleri_saldiri = kusatma_makineleri_sayi * kusatma_makineleri_saldiri;
                
            if(adim == 1) {
                fprintf(savas, "(");
            }
            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "kusatma_makineleri") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                
                kusatma_makineleri_saldiri = kusatma_makineleri_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, kusatma_makineleri_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "kusatma_makineleri") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                
                kusatma_makineleri_saldiri = kusatma_makineleri_saldiri * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, kusatma_makineleri_saldiri);
            }

            if ((adim == 1) && (strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && 
                ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "kusatma_makineleri") == 0) || 
                 strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                
                kusatma_makineleri_saldiri = kusatma_makineleri_saldiri * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %f", oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, kusatma_makineleri_saldiri);
            }

            if (adim == 1) {
                fprintf(savas, ")\n");
            }

            if ((adim != 1) && ((adim - 1) % 10) == 0) {
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı Kuşatma makinelerinin yeni saldırı gücü: %f\n", kusatma_makineleri_saldiri * 0.9);
                kusatma_makineleri_saldiri = kusatma_makineleri_saldiri * 0.9;
            }

            if (adim == 1) {
                if ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "elit_egitim") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "kusatma_makineleri") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "Elit_egitim araştırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", kusatma_makineleri_kritik_sans, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, kusatma_makineleri_kritik_sans + oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger);
                    kusatma_makineleri_kritik_sans += oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "kusatma_makineleri") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, kusatma_makineleri_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, kusatma_makineleri_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri);
                    kusatma_makineleri_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }

                if ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && 
                    ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "kusatma_makineleri") == 0) || 
                     strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0)) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, kusatma_makineleri_kritik_sans, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, kusatma_makineleri_kritik_sans + oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri);
                    kusatma_makineleri_kritik_sans += oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "kuşatma makineleri kritik şans: %d\n", kusatma_makineleri_kritik_sans);

                
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((kusatma_makineleri_kritik_sans / 100.0), -1)) == 0)) {
                    kusatma_makineleri_saldiri *= 1.5;
                    fprintf(savas, "kuşatma makinelerinin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", kusatma_makineleri_saldiri);
                }
            
            

            //fprintf(savas, ")\n");

        }
        
//orklar savunma
            
        fprintf(savas, "\n2. Savunma gücü hesaplanması(Ork Lejyonu):\n\n");
        if(ork_dovusculeri_sayi > 0) {

            fprintf(savas, "Ork_dovusculeri: %d birim x %.f savunma gücü = %.f\n", ork_dovusculeri_sayi, ork_dovusculeri_savunma, (ork_dovusculeri_sayi * ork_dovusculeri_savunma));


                ork_dovusculeri_savunma = ork_dovusculeri_sayi * ork_dovusculeri_savunma;


            if(adim == 1){
                fprintf(savas, "(");
            }

            if((adim == 1) && ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "ork_dovusculeri")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                ork_dovusculeri_savunma = ork_dovusculeri_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, ork_dovusculeri_savunma);
            }

            if((adim == 1) && ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "ork_dovusculeri")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                ork_dovusculeri_savunma = ork_dovusculeri_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, ork_dovusculeri_savunma);
            }

            if((adim == 1) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "ork_dovusculeri")) == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                ork_dovusculeri_savunma = ork_dovusculeri_savunma * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.arastirma_seviyesi.baslik, oyuncular.ork_legi.arastirma_seviyesi.deger, ork_dovusculeri_savunma);

            }
            if (adim == 1) {
                fprintf(savas, ")\n");
            }
            if((adim != 1) && ((adim - 1) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı ork_dovusculerinin yeni savunma gücü: %f\n", ork_dovusculeri_savunma * 0.9);
                    ork_dovusculeri_savunma = ork_dovusculeri_savunma * 0.9;

            }




        }
        //mizrakcilar
        if(mizrakcilar_sayi > 0) {
            fprintf(savas, "Mızrakçılar: %d birim x %.f savunma gücü = %.f\n", mizrakcilar_sayi, mizrakcilar_savunma, (mizrakcilar_sayi * mizrakcilar_savunma));


                mizrakcilar_savunma = mizrakcilar_sayi * mizrakcilar_savunma;


            if(adim == 1){
                fprintf(savas, "(");
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                mizrakcilar_savunma = mizrakcilar_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, mizrakcilar_savunma);
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                mizrakcilar_savunma = mizrakcilar_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, mizrakcilar_savunma);
            }

            if((adim == 1) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                mizrakcilar_savunma = mizrakcilar_savunma * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.arastirma_seviyesi.baslik, oyuncular.ork_legi.arastirma_seviyesi.deger, mizrakcilar_savunma);

            }
            if (adim == 1) {
                fprintf(savas, ")\n");
            }
            if((adim != 1) && ((adim - 1) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı mızrakçıların yeni savunma gücü: %f\n", mizrakcilar_savunma * 0.9);
                    mizrakcilar_savunma = mizrakcilar_savunma * 0.9;

            }




        }
        if(varg_binicileri_sayi > 0) {
            fprintf(savas, "varg_binicileri: %d birim x %.f savunma gücü = %.f\n", varg_binicileri_sayi, varg_binicileri_savunma, (varg_binicileri_sayi * varg_binicileri_savunma));


            varg_binicileri_savunma = varg_binicileri_sayi * varg_binicileri_savunma;


            if(adim == 1){
                fprintf(savas, "(");
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                varg_binicileri_savunma = varg_binicileri_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, varg_binicileri_savunma);
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                varg_binicileri_savunma = varg_binicileri_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, varg_binicileri_savunma);
            }

            if((adim == 1) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                varg_binicileri_savunma = varg_binicileri_savunma * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.arastirma_seviyesi.baslik, oyuncular.ork_legi.arastirma_seviyesi.deger, varg_binicileri_savunma);

            }
            if (adim == 1) {
                fprintf(savas, ")\n");
            }
            if((adim != 1) && ((adim - 1) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı varg_binicilerinin yeni savunma gücü: %f\n", varg_binicileri_savunma * 0.9);
                    varg_binicileri_savunma = varg_binicileri_savunma * 0.9;

            }




        }
        if(troller_sayi > 0) {
            fprintf(savas, "troller: %d birim x %.f savunma gücü = %.f\n", troller_sayi, troller_savunma, (troller_sayi * troller_savunma));


                troller_savunma = troller_sayi * troller_savunma;


            if(adim == 1){
                fprintf(savas, "(");
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "troller") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                troller_savunma = troller_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, troller_savunma);
            }

            if((adim == 1) && ( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "troller") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                troller_savunma = troller_savunma * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, troller_savunma);
            }

            if((adim == 1) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "troller") == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                troller_savunma = troller_savunma * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.ork_legi.arastirma_seviyesi.baslik, oyuncular.ork_legi.arastirma_seviyesi.deger, troller_savunma);

            }
            if (adim == 1) {
                fprintf(savas, ")\n");
            }
            if((adim != 1) && ((adim - 1) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı trollernin yeni savunma gücü: %f\n", troller_savunma * 0.9);
                    troller_savunma = troller_savunma * 0.9;

            }
        }

        //printf("%f\n", piyadeler_saldiri);
        //printf("%f\n", suvariler_saldiri);

            insanlar_saldiri = piyadeler_saldiri + suvariler_saldiri + okcular_saldiri + kusatma_makineleri_saldiri;
            orklar_savunma = ork_dovusculeri_savunma + mizrakcilar_savunma + varg_binicileri_savunma + troller_savunma;

            //printf("%f\n", piyadeler_saldiri + suvariler_saldiri + okcular_saldiri + kusatma_makineleri_saldiri);

            //net hasar
            fprintf(savas, "\n3. Net Hasar Hesaplanması:\n");

            fprintf(savas, "\nNet Hasar = %f x (1 - (%f / %f))\n", insanlar_saldiri, orklar_savunma, insanlar_saldiri);

            net_hasar = insanlar_saldiri * (1 - (orklar_savunma / insanlar_saldiri));

            //printf("%f\n", insanlar_saldiri);

            fprintf(savas, "Net Hasar = %f\n", (float)net_hasar);


            if(net_hasar < 0) {

            fprintf(savas,"Bu adımda saldırı olmaz. \n");

            }
            else {


                fprintf(savas, "\n4. Orantılı Hasar Dağılımı: Ork Lejyonuna %f hasar orantılı olarak dağıtılır:\n", net_hasar);


                if(ork_dovusculeri_sayi > 0) {
                    fprintf(savas, "Ork Dövüşçüleri : %f / %f = %f -> %f x %f = %f\n", ork_dovusculeri_savunma, orklar_savunma, ork_dovusculeri_savunma / orklar_savunma, ork_dovusculeri_savunma / orklar_savunma, net_hasar, ork_dovusculeri_savunma / orklar_savunma * net_hasar);    
                    ork_dovusculeri_kayip = (int)((ork_dovusculeri_savunma / orklar_savunma * net_hasar) / ork_dovusculeri_sayi);
                    fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(ork_dovusculeri_savunma / orklar_savunma * net_hasar), ork_dovusculeri_sayi, ork_dovusculeri_kayip);

                }
                if(varg_binicileri_sayi > 0) {
                    fprintf(savas, "varg_binicileri : %f / %f = %f -> %f x %f = %f\n", varg_binicileri_savunma, orklar_savunma, varg_binicileri_savunma / orklar_savunma, varg_binicileri_savunma / orklar_savunma, net_hasar, varg_binicileri_savunma / orklar_savunma * net_hasar);    
                    varg_binicileri_kayip = (int)((varg_binicileri_savunma / orklar_savunma * net_hasar) / varg_binicileri_sayi);
                    fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(varg_binicileri_savunma / orklar_savunma * net_hasar), varg_binicileri_sayi, varg_binicileri_kayip);

                }
                if(mizrakcilar_sayi > 0) {
                    fprintf(savas, "mizrakcilar : %f / %f = %f -> %f x %f = %f\n", mizrakcilar_savunma, orklar_savunma, mizrakcilar_savunma / orklar_savunma, mizrakcilar_savunma / orklar_savunma, net_hasar, mizrakcilar_savunma / orklar_savunma * net_hasar);    
                    mizrakcilar_kayip = (int)((mizrakcilar_savunma / orklar_savunma * net_hasar) / mizrakcilar_sayi);
                    fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(mizrakcilar_savunma / orklar_savunma * net_hasar), mizrakcilar_kayip, mizrakcilar_kayip);

                }
                if(troller_sayi > 0) {
                    fprintf(savas, "troller : %f / %f = %f -> %f x %f = %f\n", troller_savunma, orklar_savunma, troller_savunma / orklar_savunma, troller_savunma / orklar_savunma, net_hasar, troller_savunma / orklar_savunma * net_hasar);    
                    troller_kayip = (int)((troller_savunma / orklar_savunma * net_hasar) / troller_sayi);
                    fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(troller_savunma / orklar_savunma * net_hasar), troller_sayi, troller_kayip);

                }
            }








            if (adim != 1 && ((adim - 1) % (int)ceil(pow((piyadeler_kritik_sans / 100.0), -1)) == 0)) {
                piyadeler_saldiri = piyadeler_saldiri / 1.5;
                //printf("kritik piyadelr\n");
                //printf("%d\n", adim);
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((okcular_kritik_sans / 100.0), -1)) == 0)) {
                okcular_saldiri = okcular_saldiri / 1.5;
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((suvariler_kritik_sans / 100.0), -1)) == 0)) {
                suvariler_saldiri = suvariler_saldiri / 1.5;
            }
            if (adim != 1 && ((adim - 1) % (int)ceil(pow((kusatma_makineleri_kritik_sans / 100.0), -1)) == 0)) {
                kusatma_makineleri_saldiri = kusatma_makineleri_saldiri / 1.5;
            }


        if (piyadeler_sayi > 0) {

            piyadeler_saldiri = piyadeler_saldiri / piyadeler_sayi;
        }
        if (suvariler_sayi > 0) {
            suvariler_saldiri = suvariler_saldiri / suvariler_sayi;
        }
        if (okcular_sayi > 0) {
            okcular_saldiri = okcular_saldiri / okcular_sayi;
        }
        if (kusatma_makineleri_sayi > 0) {
            kusatma_makineleri_saldiri = kusatma_makineleri_saldiri / kusatma_makineleri_sayi;
        }
        if (ork_dovusculeri_sayi > 0) {

            ork_dovusculeri_savunma = ork_dovusculeri_savunma / ork_dovusculeri_sayi;
        }
        if (mizrakcilar_sayi > 0) {
            mizrakcilar_savunma = mizrakcilar_savunma / mizrakcilar_sayi;
        }
        if (varg_binicileri_sayi > 0) {
            varg_binicileri_savunma = varg_binicileri_savunma / varg_binicileri_sayi;
        }
        if (troller_sayi > 0) {
            troller_savunma = troller_savunma / troller_sayi;
        }


        if(ork_dovusculeri_kayip < 0) {
            ork_dovusculeri_sayi = 0;
        }
        else {
            
            ork_dovusculeri_sayi = ork_dovusculeri_sayi - ork_dovusculeri_kayip;
        }

            mizrakcilar_sayi = mizrakcilar_sayi - mizrakcilar_kayip;

            varg_binicileri_sayi = varg_binicileri_sayi - varg_binicileri_kayip;

            troller_sayi = troller_sayi - troller_kayip;


            if((troller_sayi <= 0) && (ork_dovusculeri_sayi <= 0) && (varg_binicileri_sayi <= 0) && (mizrakcilar_sayi <= 0)) {
                fprintf(savas, "\n\nTÜM ORK BİRLİKLERİ ÖLDÜ İNSANLAR KAZANDI\n");
                break;
            }

            adim++;

            //orkların saldırısı

        fprintf(savas, "\nAdım %d: Orkların Saldırısı \n\n", adim); 
        fprintf(savas, "1. Saldırı gücü hesaplaması(Araştırma ve Canavar Etkileri Dahil): \n\n");
        
        if(ork_dovusculeri_sayi > 0) { 


                fprintf(savas, "ork_dovusculeri: %d birim x %.f saldırı gücü = %.f\n", ork_dovusculeri_sayi, ork_dovusculeri_saldiri, (ork_dovusculeri_sayi * ork_dovusculeri_saldiri));
                
                    ork_dovusculeri_saldiri = ork_dovusculeri_saldiri * ork_dovusculeri_sayi;
                
                if(adim == 2){
                    fprintf(savas, "(");
                }
            if ((adim == 2) && 
                (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "ork_dovusculeri") == 0) || 
                 (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0))) {
                
                ork_dovusculeri_saldiri = ork_dovusculeri_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", 
                        oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, 
                        oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, 
                        ork_dovusculeri_saldiri);
            }
            
            if ((adim == 2) && 
                (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && 
                ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "ork_dovusculeri") == 0) || 
                 (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0))) {
                
                ork_dovusculeri_saldiri = ork_dovusculeri_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %f ", 
                        oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, 
                        oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, 
                        ork_dovusculeri_saldiri);
            }
            
            //printf("%s\n",oyuncular.ork_legi.arastirma_seviyesi.aciklama);
            if ((adim == 2) && 
                (strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && 
                ((strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "ork_dovusculeri") == 0) || 
                 (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler") == 0))) {
                    //printf("%s\n",oyuncular.ork_legi.arastirma_seviyesi.baslik);
                
                ork_dovusculeri_saldiri = ork_dovusculeri_saldiri * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "Araştırmanın %%%d etkisi ile: %f", 
                        oyuncular.ork_legi.arastirma_seviyesi.deger, 
                        ork_dovusculeri_saldiri);
            }
            
            if (adim == 2) {
                fprintf(savas, ")\n");
            }
            
            if ((adim != 2) && ((adim - 2) % 10) == 0) {
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı. Ork dövüşçülerinin yeni saldırı gücü: %f\n", 
                        ork_dovusculeri_saldiri * 0.9);
                ork_dovusculeri_saldiri = ork_dovusculeri_saldiri * 0.9;
            }
            
            if (adim == 2) {
                if ((strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "elit_egitim") == 0) && ((strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "ork_dovusculeri") == 0) || (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "Elit eğitim araştırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            ork_dovusculeri_kritik_sans, 
                            oyuncular.ork_legi.arastirma_seviyesi.deger, 
                            ork_dovusculeri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    ork_dovusculeri_kritik_sans += oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
            
                if ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "ork_dovusculeri") == 0) || (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, 
                            ork_dovusculeri_kritik_sans, 
                            oyuncular.ork_legi.arastirma_seviyesi.deger, 
                            ork_dovusculeri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    ork_dovusculeri_kritik_sans += oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
            
                if ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "ork_dovusculeri") == 0) || (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler") == 0))) {
                    
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", 
                            oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, 
                            ork_dovusculeri_kritik_sans, 
                            oyuncular.ork_legi.arastirma_seviyesi.deger, 
                            ork_dovusculeri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    ork_dovusculeri_kritik_sans += oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
            
                fprintf(savas, "Ork dövüşçüleri kritik şans: %d\n", ork_dovusculeri_kritik_sans);
            
                
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((ork_dovusculeri_kritik_sans / 100.0), -1)) == 0)) {
                    ork_dovusculeri_saldiri *= 1.5;
                    fprintf(savas, "Ork dövüşçülerinin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", 
                            ork_dovusculeri_saldiri);
                }

        

            //kritik şansı  vuruşu eklemeyi unutma;
        }

        //mizrakcilar
        if(mizrakcilar_sayi > 0) { 


            fprintf(savas, "mizrakcilar: %d birim x %.f saldırı gücü = %.f\n", mizrakcilar_sayi, mizrakcilar_saldiri, (mizrakcilar_sayi * mizrakcilar_saldiri));
            
                
                mizrakcilar_saldiri = mizrakcilar_sayi * mizrakcilar_saldiri;
            

            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && (((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama , "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
            
                mizrakcilar_saldiri = mizrakcilar_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, mizrakcilar_saldiri);

            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler")) == 0)) {
            
                mizrakcilar_saldiri = mizrakcilar_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, mizrakcilar_saldiri);
            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && (( (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
            
                mizrakcilar_saldiri = mizrakcilar_saldiri * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %.f", oyuncular.ork_legi.arastirma_seviyesi.deger, mizrakcilar_saldiri);
            }

            if(adim == 2){
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 2) % 10 )== 0){
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı mizrakciların yeni saldırı gücü: %f\n", mizrakcilar_saldiri * 0.9);
                mizrakcilar_saldiri = mizrakcilar_saldiri * 0.9;

            }
            if ( adim == 2) {
                if(( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "elit_egitim") == 0) && (( (strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                    fprintf(savas, "Elit_egitim arastırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", mizrakcilar_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, mizrakcilar_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    mizrakcilar_kritik_sans = mizrakcilar_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "mizrakcilar")) == 0) || (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama , "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, mizrakcilar_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, mizrakcilar_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    mizrakcilar_kritik_sans = mizrakcilar_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && (( (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "mizrakcilar")) == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, mizrakcilar_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, mizrakcilar_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    mizrakcilar_kritik_sans = mizrakcilar_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "mizrakcilar kritik şans: %d\n", mizrakcilar_kritik_sans);

                
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((mizrakcilar_kritik_sans / 100.0), -1)) == 0)) {
                    mizrakcilar_saldiri = mizrakcilar_saldiri * 1.5;
                    fprintf(savas, "mizrakcilarin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", mizrakcilar_saldiri);

                }

        }
        //varg_binicileri
        if(varg_binicileri_sayi > 0) { 


            fprintf(savas, "varg_binicileri: %d birim x %.f saldırı gücü = %.f\n", varg_binicileri_sayi, varg_binicileri_saldiri, (varg_binicileri_sayi * varg_binicileri_saldiri));
            
            
                varg_binicileri_saldiri = varg_binicileri_sayi * varg_binicileri_saldiri;
            
            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "varg_binicileri")) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
            
                varg_binicileri_saldiri = varg_binicileri_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, varg_binicileri_saldiri);

            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "varg_binicileri")) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler")) == 0)) {
            
                varg_binicileri_saldiri = varg_binicileri_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, okcular_saldiri);
            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "varg_binicileri")) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
            
                varg_binicileri_saldiri = varg_binicileri_saldiri * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %.f", oyuncular.ork_legi.arastirma_seviyesi.deger, varg_binicileri_saldiri);
            }


            if(adim == 2){
                fprintf(savas, ")\n");
            }

            if((adim != 2) && ((adim - 2) % 10 )== 0){
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı varg_binicileri yeni saldırı gücü: %f\n", varg_binicileri_saldiri * 0.9);
                varg_binicileri_saldiri = varg_binicileri_saldiri * 0.9;

            }
            if ( adim == 2) {
                if(( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "elit_egitim") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                    fprintf(savas, "Elit_egitim arastırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", varg_binicileri_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, varg_binicileri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    varg_binicileri_kritik_sans = varg_binicileri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, varg_binicileri_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, varg_binicileri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    varg_binicileri_kritik_sans = varg_binicileri_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "varg_binicileri") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, varg_binicileri_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, varg_binicileri_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    varg_binicileri_kritik_sans = varg_binicileri_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "varg_binicileri kritik şans: %d\n", varg_binicileri_kritik_sans);

                
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((varg_binicileri_kritik_sans / 100.0), -1)) == 0)) {
                    varg_binicileri_saldiri = varg_binicileri_saldiri * 1.5;
                    fprintf(savas, "varg_binicileriin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", varg_binicileri_saldiri);
                }

        }
        //troller
        if(troller_sayi > 0) { 


            fprintf(savas, "troller: %d birim x %.f saldırı gücü = %.f\n", troller_sayi, troller_saldiri, (troller_sayi * troller_saldiri));
                
                
            troller_saldiri = troller_sayi * troller_saldiri;
                
            if(adim == 2) {
                fprintf(savas, "(");
            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "saldiri") == 0) && ((strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "troller") == 0) || (strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
            
                troller_saldiri = troller_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, troller_saldiri);

            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "saldiri") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "troller") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler")) == 0)) {
            
                troller_saldiri = troller_saldiri * (1 + (oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0)); 
                fprintf(savas, "%s ile %%%d saldırı bonusu ile: %.f ", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, troller_saldiri);
            }
            if((adim == 2) && ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "saldiri_gelistirmesi") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "troller") == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
            
                troller_saldiri = troller_saldiri * (1 + (oyuncular.ork_legi.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "araştırmanın %%%d etkisi ile: %.f", oyuncular.ork_legi.arastirma_seviyesi.deger, troller_saldiri);
            }
            if(adim == 2) {
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 1) % 10 ) == 0){
                fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı trollerin yeni saldırı gücü: %f\n", troller_saldiri * 0.9);
                troller_saldiri = troller_saldiri * 0.9;

            }
            if ( adim == 2) {
                if(( strcmp(oyuncular.ork_legi.arastirma_seviyesi.baslik, "elit_egitim") == 0) && (( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "troller") == 0) || ( strcmp(oyuncular.ork_legi.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                    fprintf(savas, "Elit_egitim araştırmasının etkisi ile kritik şans: %%%d + %%%d = %%%d\n", troller_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, piyadeler_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    troller_kritik_sans = troller_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kritik_sans") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "troller") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.aciklama, "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.kahramanlar, troller_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, troller_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    troller_kritik_sans = troller_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.ketkiler.etki_degeri;
                }
                if(( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kritik_sans") == 0) && (( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "troller") == 0) || ( strcmp(oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.aciklama, "tum_birimler")) == 0)) {
                    fprintf(savas, "%s etkisi ile kritik şans: %%%d + %%%d = %%%d\n", oyuncular.ork_legi.kahramanlar_ve_canavarlar.canavarlar, troller_kritik_sans, oyuncular.ork_legi.arastirma_seviyesi.deger, troller_kritik_sans + oyuncular.ork_legi.arastirma_seviyesi.deger);
                    troller_kritik_sans = troller_kritik_sans + oyuncular.ork_legi.kahramanlar_ve_canavarlar.cetkiler.etki_degeri;
                }

                fprintf(savas, "troller kritik şans: %d\n", troller_kritik_sans);
                if(adim == 2) {
                    fprintf(savas, "(");
                }
                fprintf(savas, ")\n");

                
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((troller_kritik_sans / 100.0), -1)) == 0)) {
                    troller_saldiri = troller_saldiri * 1.5;
                    fprintf(savas, "trollernin saldırı gücü bu turda kritik hasar sayesinde %%50 arttı: %f\n", troller_saldiri);
                }
            

            //

        }
        
//insanlar savunma
            
        fprintf(savas, "\n2. Savunma gücü hesaplanması(İnsan İmparatorluğu):\n\n");
        if(piyadeler_sayi > 0) {

            fprintf(savas, "piyadeler: %d birim x %.f savunma gücü = %.f\n", piyadeler_sayi, piyadeler_savunma, (piyadeler_sayi * piyadeler_savunma));


                piyadeler_savunma = piyadeler_sayi * piyadeler_savunma;


            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "piyadeler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                piyadeler_savunma = piyadeler_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, piyadeler_savunma);
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "piyadeler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                piyadeler_savunma = piyadeler_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, piyadeler_savunma);
            }

            if((adim == 2) && ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "piyadeler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                piyadeler_savunma = piyadeler_savunma * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, piyadeler_savunma);

            }
            if (adim == 2) {
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 1) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı piyadelernin yeni savunma gücü: %f\n", piyadeler_savunma * 0.9);
                    piyadeler_savunma = piyadeler_savunma * 0.9;

            }




        }
        //okcular
        if(okcular_sayi > 0) {
            fprintf(savas, "okcular: %d birim x %.f savunma gücü = %.f\n", okcular_sayi, okcular_savunma, (okcular_sayi * okcular_savunma));


                okcular_savunma = okcular_sayi * okcular_savunma;


            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ((strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu , "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "okcular") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                okcular_savunma = okcular_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, okcular_savunma);
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "okcular") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                okcular_savunma = okcular_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, okcular_savunma);
            }

            if((adim == 2) && ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "okcular") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                okcular_savunma = okcular_savunma * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, okcular_savunma);

            }
            if (adim == 2) {
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 2) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı mızrakçıların yeni savunma gücü: %f\n", okcular_savunma * 0.9);
                    okcular_savunma = okcular_savunma * 0.9;

            }




        }
        if(suvariler_sayi > 0) {
            fprintf(savas, "suvariler: %d birim x %.f savunma gücü = %.f\n", suvariler_sayi, suvariler_savunma, (suvariler_sayi * suvariler_savunma));


            suvariler_savunma = suvariler_sayi * suvariler_savunma;


            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "suvariler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                suvariler_savunma = suvariler_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, suvariler_savunma);
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "suvariler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                suvariler_savunma = suvariler_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, suvariler_savunma);
            }

            if((adim == 2) && ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "suvariler") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                suvariler_savunma = suvariler_savunma * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, suvariler_savunma);

            }
            if (adim == 2) {
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 2) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı suvarilernin yeni savunma gücü: %f\n", suvariler_savunma * 0.9);
                    suvariler_savunma = suvariler_savunma * 0.9;

            }




        }
        if(kusatma_makineleri_sayi> 0) {
            fprintf(savas, "kusatma_makineleri: %d birim x %.f savunma gücü = %.f\n", kusatma_makineleri_sayi, kusatma_makineleri_savunma, (kusatma_makineleri_sayi * kusatma_makineleri_savunma));


                kusatma_makineleri_savunma = kusatma_makineleri_sayi * kusatma_makineleri_savunma;


            if(adim == 2){
                fprintf(savas, "(");
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "kusatma_makineleri") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_turu, "tum_birimler")) == 0)) {
                kusatma_makineleri_savunma = kusatma_makineleri_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.canavarlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.cetkiler.etki_degeri, kusatma_makineleri_savunma);
            }

            if((adim == 2) && ( (strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "savunma")) == 0) && (( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "kusatma_makineleri") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_turu, "tum_birimler")) == 0)) {
                kusatma_makineleri_savunma = kusatma_makineleri_savunma * (1 + (oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.kahramanlar, oyuncular.insan_imparatorlugu.kahramanlar_ve_canavarlar.ketkiler.etki_degeri, kusatma_makineleri_savunma);
            }

            if((adim == 2) && ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, "savunma_ustaligi") == 0) && (( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "kusatma_makineleri") == 0) || ( strcmp(oyuncular.insan_imparatorlugu.arastirma_seviyesi.hedef, "tum_birimler")) == 0)) {
                kusatma_makineleri_savunma = kusatma_makineleri_savunma * (1 + (oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger / 100.0));
                fprintf(savas, "%s ile %%%d savunma bonusu ile: %.f\n", oyuncular.insan_imparatorlugu.arastirma_seviyesi.baslik, oyuncular.insan_imparatorlugu.arastirma_seviyesi.deger, kusatma_makineleri_savunma);

            }
            if (adim == 2) {
                fprintf(savas, ")\n");
            }
            if((adim != 2) && ((adim - 2) % 10 ) == 0) {
                    fprintf(savas, "Yorgunluk nedeniyle tüm birimlerin saldırıları %%10 azaldı kusatma_makinelerinin yeni savunma gücü: %f\n", kusatma_makineleri_savunma * 0.9);
                    kusatma_makineleri_savunma = kusatma_makineleri_savunma * 0.9;

            }
        }

        //printf("%f\n", piyadeler_saldiri);
        //printf("%f\n", suvariler_saldiri);

            orklar_saldiri = ork_dovusculeri_saldiri + troller_saldiri + varg_binicileri_saldiri + mizrakcilar_saldiri;
            insanlar_savunma = piyadeler_savunma + suvariler_savunma + okcular_savunma + kusatma_makineleri_savunma;

            //printf("%f\n", piyadeler_saldiri + suvariler_saldiri + okcular_saldiri + kusatma_makineleri_saldiri);

            //net hasar
            fprintf(savas, "\n3. Net Hasar Hesaplanması:\n");

            fprintf(savas, "\nNet Hasar = %f x (1 - (%f / %f))\n", orklar_saldiri, insanlar_savunma, orklar_saldiri);

            net_hasar = orklar_saldiri * (1 - (insanlar_savunma / orklar_saldiri));

            //printf("%f\n", orklar_saldiri);

            fprintf(savas, "Net Hasar = %f\n", (float)net_hasar);


            if(net_hasar < 0) {

            fprintf(savas,"Bu adımda saldırı olmaz. \n");
            }
            else {


            fprintf(savas, "\n4. Orantılı Hasar Dağılımı: Ork Lejyonuna %f hasar orantılı olarak dağıtılır:\n", net_hasar);


            if(piyadeler_sayi > 0) {
                fprintf(savas, "piyadeler : %f / %f = %f -> %f x %f = %f\n", piyadeler_savunma, insanlar_savunma, piyadeler_savunma / insanlar_savunma, piyadeler_savunma / insanlar_savunma, net_hasar, piyadeler_savunma / insanlar_savunma * net_hasar);    
                piyadeler_kayip = (int)((piyadeler_savunma / insanlar_savunma * net_hasar) / piyadeler_sayi);
                fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(piyadeler_savunma / insanlar_savunma * net_hasar), piyadeler_sayi, piyadeler_kayip);

            }
            if(suvariler_sayi > 0) {
                fprintf(savas, "suvariler : %f / %f = %f -> %f x %f = %f\n", suvariler_savunma, insanlar_savunma, suvariler_savunma / insanlar_savunma, suvariler_savunma / insanlar_savunma, net_hasar, suvariler_savunma / insanlar_savunma * net_hasar);    
                suvariler_kayip = (int)((suvariler_savunma / insanlar_savunma * net_hasar) / suvariler_sayi);
                fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(suvariler_savunma / insanlar_savunma * net_hasar), suvariler_sayi, suvariler_kayip);

            }
            if(okcular_sayi > 0) {
                fprintf(savas, "okcular : %f / %f = %f -> %f x %f = %f\n", okcular_savunma, insanlar_savunma, okcular_savunma / insanlar_savunma, okcular_savunma / insanlar_savunma, net_hasar, okcular_savunma / insanlar_savunma * net_hasar);    
                okcular_kayip = (int)((okcular_savunma / insanlar_savunma * net_hasar) / okcular_sayi);
                fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(okcular_savunma / insanlar_savunma * net_hasar), okcular_kayip, okcular_kayip);

            }
            if(kusatma_makineleri_sayi > 0) {
                fprintf(savas, "kusatma_makineleri : %f / %f = %f -> %f x %f = %f\n", kusatma_makineleri_savunma, insanlar_savunma, kusatma_makineleri_savunma / insanlar_savunma, kusatma_makineleri_savunma / insanlar_savunma, net_hasar, kusatma_makineleri_savunma / insanlar_savunma * net_hasar);    
                kusatma_makineleri_kayip = (int)((kusatma_makineleri_savunma / insanlar_savunma * net_hasar) / kusatma_makineleri_sayi);
                fprintf(savas, "Kayıp: %f/%d = %d birim öldü\n",(kusatma_makineleri_savunma / insanlar_savunma * net_hasar), kusatma_makineleri_sayi, kusatma_makineleri_kayip);

            }
            }








            if (adim != 2 && ((adim - 2) % (int)ceil(pow((ork_dovusculeri_kritik_sans / 100.0), -1)) == 0)) {
                ork_dovusculeri_saldiri = ork_dovusculeri_saldiri / 1.5;
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((mizrakcilar_kritik_sans / 100.0), -1)) == 0)) {
                mizrakcilar_saldiri = mizrakcilar_saldiri / 1.5;
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((troller_kritik_sans / 100.0), -1)) == 0)) {
                troller_saldiri = troller_saldiri / 1.5;
            }
            if (adim != 2 && ((adim - 2) % (int)ceil(pow((varg_binicileri_kritik_sans / 100.0), -1)) == 0)) {
                varg_binicileri_saldiri = varg_binicileri_saldiri / 1.5;
            }


        if (ork_dovusculeri_sayi > 0) {

            ork_dovusculeri_saldiri = ork_dovusculeri_saldiri / ork_dovusculeri_sayi;
        }
        if (mizrakcilar_sayi > 0) {
            mizrakcilar_saldiri = mizrakcilar_saldiri / mizrakcilar_sayi;
        }
        if (varg_binicileri_sayi > 0) {
            varg_binicileri_saldiri = varg_binicileri_saldiri / varg_binicileri_sayi;
        }
        if (troller_sayi > 0) {
            troller_saldiri = troller_saldiri / troller_sayi;
        }
        if (piyadeler_sayi > 0) {

            piyadeler_savunma = piyadeler_savunma / piyadeler_sayi;
        }
        if (suvariler_sayi > 0) {
            suvariler_savunma = suvariler_savunma / suvariler_sayi;
        }
        if (okcular_sayi > 0) {
            okcular_savunma = okcular_savunma / okcular_sayi;
        }
        if (kusatma_makineleri_sayi > 0) {
            kusatma_makineleri_savunma = kusatma_makineleri_savunma / kusatma_makineleri_sayi;
        }



            piyadeler_sayi = piyadeler_sayi - piyadeler_kayip;

            okcular_sayi = okcular_sayi - okcular_kayip;

            suvariler_sayi = suvariler_sayi - suvariler_kayip;

            kusatma_makineleri_sayi = kusatma_makineleri_sayi - kusatma_makineleri_kayip;


            if((piyadeler_sayi <= 0) && (okcular_sayi <= 0) && (kusatma_makineleri_sayi <= 0) && (suvariler_sayi <= 0)) {
                fprintf(savas, "\n\nTÜM İNSAN BİRLİKLERİ ÖLDÜ ORKLAR KAZANDI\n");
                break;
            }
    }

    fclose(savas);




    float piyadeler_once = oyuncular.insan_imparatorlugu.birimler.piyadeler.sayi;
    float okcular_once = oyuncular.insan_imparatorlugu.birimler.okcular.sayi;
    float suvariler_once = oyuncular.insan_imparatorlugu.birimler.suvariler.sayi;
    float kusatma_makineleri_once = oyuncular.insan_imparatorlugu.birimler.kusatma_makineleri.sayi;

    float ork_dovusculeri_once = oyuncular.ork_legi.birimler.ork_dovusculeri.sayi;
    float mizrakcilar_once = oyuncular.ork_legi.birimler.mizrakcilar.sayi;
    float troller_once = oyuncular.ork_legi.birimler.troller.sayi;
    float varg_binicileri_once = oyuncular.ork_legi.birimler.varg_binicileri.sayi;
 
 
    float piyadeler_sonra = piyadeler_sayi;
    float okcular_sonra = okcular_sayi;
    float suvariler_sonra = suvariler_sayi;
    float kusatma_makineleri_sonra = kusatma_makineleri_sayi;

    float ork_dovusculeri_sonra = ork_dovusculeri_sayi;
    float mizrakcilar_sonra = mizrakcilar_sayi;
    float troller_sonra = troller_sayi;
    float varg_binicileri_sonra = varg_binicileri_sayi;


if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_JPG) == 0) {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Hexagonal Grid", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont("Fonts/arial.ttf", 16); 
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    double hex_width = 1.5 * HEX_SIZE;
    double hex_height = sqrt(3) * HEX_SIZE;
    double grid_width = hex_width * 10;
    double grid_height = hex_height * 10;

    int start_x = (SCREEN_WIDTH - grid_width) / 2;
    int start_y = (SCREEN_HEIGHT - grid_height) /2;

    Hex hexes[10][10];
    SDL_Texture *okcular_texture = IMG_LoadTexture(renderer, "pictures/okcular.png"); 
    if (!okcular_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *piyadeler_texture = IMG_LoadTexture(renderer, "pictures/piyadeler.png"); 
    if (!piyadeler_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *suvariler_texture = IMG_LoadTexture(renderer, "pictures/suvariler.png"); 
    if (!suvariler_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *kusatma_makineleri_texture = IMG_LoadTexture(renderer, "pictures/kusatma_makineleri.png"); 
    if (!kusatma_makineleri_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *ork_dovusculeri_texture = IMG_LoadTexture(renderer, "pictures/ork_dovusculeri.png"); 
    if (!ork_dovusculeri_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *mizrakcilar_texture = IMG_LoadTexture(renderer, "pictures/mizrakcilar.png"); 
    if (!mizrakcilar_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *varg_binicileri_texture = IMG_LoadTexture(renderer, "pictures/varg_binicileri.png"); 
    if (!varg_binicileri_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *troller_texture = IMG_LoadTexture(renderer, "pictures/troller.png"); 
    if (!troller_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *bos_texture = IMG_LoadTexture(renderer, "pictures/bos.png"); 
    if (!troller_texture) {
        printf("Failed to load texture! IMG_Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *background_texture = IMG_LoadTexture(renderer, "pictures/back_ground.png"); 
if (!background_texture) {
    printf("Failed to load background texture! IMG_Error: %s\n", IMG_GetError());
    return 1;
}
    SDL_Texture *insanlar_kahraman_texture = IMG_LoadTexture(renderer, "pictures/insanlar_kahraman.png"); 
if (!background_texture) {
    printf("Failed to load background texture! IMG_Error: %s\n", IMG_GetError());
    return 1;
}
    SDL_Texture *insanlar_canavar_texture = IMG_LoadTexture(renderer, "pictures/insanlar_canavar.png"); 
if (!background_texture) {
    printf("Failed to load background texture! IMG_Error: %s\n", IMG_GetError());
    return 1;
}
    SDL_Texture *orklar_kahraman_texture = IMG_LoadTexture(renderer, "pictures/orklar_kahraman.png"); 
if (!background_texture) {
    printf("Failed to load background texture! IMG_Error: %s\n", IMG_GetError());
    return 1;
}
    SDL_Texture *orklar_canavar_texture = IMG_LoadTexture(renderer, "pictures/orklar_canavar.png"); 
if (!background_texture) {
    printf("Failed to load background texture! IMG_Error: %s\n", IMG_GetError());
    return 1;
}





    for(int a = 0; a < 10; a++) {
        for(int b = 0; b < 10; b++) {
            hexes[a][b].x = start_x + b * 1.5 * HEX_SIZE;
            hexes[a][b].y = start_y + a * hex_height + (b % 2) * (HEX_SIZE * sqrt(3) / 2);
            hexes[a][b].health = 0;
            hexes[a][b].units = 0;
            hexes[a][b].texture = bos_texture; 
                    
        }
    }       


    for (int i = 0; i < 10; i++) {        
        for (int j = 0; j < 10; j++) {
            if(i == 0 && j == 0) {
                hexes[0][0].texture = insanlar_kahraman_texture;    
                continue;
            }
            else if(i == 1 && j == 0) {
                hexes[0][1].texture = insanlar_canavar_texture;
                continue;
            }
            else if((piyadeler_sayig > 0) && (piyadeler_sayig > 100)) {
                
                    hexes[j][i].health = piyadeler_saglik / piyadeler_saglik;
                    hexes[j][i].units = 100;
                    hexes[j][i].texture = piyadeler_texture; 

                    piyadeler_sayig -= 100;
                
            }
            else if((piyadeler_sayig > 0) && (piyadeler_sayig <= 100)) {
                    hexes[j][i].health = piyadeler_saglik / piyadeler_saglik;
                    hexes[j][i].units = piyadeler_sayig;
                    hexes[j][i].texture = piyadeler_texture; 

                    piyadeler_sayig -= piyadeler_sayig;
                    continue;
                    
            }
            else if((okcular_sayig > 0) && (okcular_sayig > 100)) {
                
                
                    hexes[j][i].health = okcular_saglik / okcular_saglik;
                    hexes[j][i].units = 100;
                    hexes[j][i].texture = okcular_texture; 

                    okcular_sayig -= 100;
                
            }
            else if((okcular_sayig > 0) && (okcular_sayig <= 100)) {
                
                    hexes[j][i].health = okcular_saglik / okcular_saglik;
                    hexes[j][i].units = okcular_sayig;
                    hexes[j][i].texture = okcular_texture; 

                    okcular_sayig -= okcular_sayig;
                    continue;

            }
            else if((suvariler_sayig > 0) && (suvariler_sayig > 100)) {
                    
                    
                    hexes[j][i].health = 1;
                    hexes[j][i].units = 100;
                    hexes[j][i].texture = suvariler_texture; 

                    suvariler_sayig -= 100;
                
            }
            else if((suvariler_sayig > 0) && (suvariler_sayig <= 100)) {
                
                    hexes[j][i].health = 1;
                    hexes[j][i].units = suvariler_sayig;
                    hexes[j][i].texture = suvariler_texture; 

                    suvariler_sayig -= suvariler_sayig;
                    continue;

            }
            else if((kusatma_makineleri_sayig > 0) && (kusatma_makineleri_sayig > 100)) {
                
                
                    hexes[j][i].health = kusatma_makineleri_saglik / kusatma_makineleri_saglik;
                    hexes[j][i].units = 100;
                    hexes[j][i].texture = kusatma_makineleri_texture; 

                    kusatma_makineleri_sayig -= 100;
                
            }
            else if((kusatma_makineleri_sayig > 0) && (kusatma_makineleri_sayig <= 100)) {
                
                    hexes[j][i].health = kusatma_makineleri_saglik / kusatma_makineleri_saglik;
                    hexes[j][i].units = kusatma_makineleri_sayig;
                    hexes[j][i].texture = kusatma_makineleri_texture; 

                    kusatma_makineleri_sayig -= kusatma_makineleri_sayig;
                    continue;

            }
            
                
            
        }
        
    }

    for(int m = 9; m >= 0; m--) {
        for(int n = 9; n >= 0; n--) {
            if(m == 9 && n == 9) {
                hexes[n][m].texture =  orklar_kahraman_texture;
                
            }
            else if(m == 9 && n == 8) {
                hexes[n][m].texture =  orklar_canavar_texture;
                
            }
            else if((ork_dovusculeri_sayig > 0) && (ork_dovusculeri_sayig > 100)) {

                
                    hexes[n][m].health = ork_dovusculeri_saglik / ork_dovusculeri_saglik;
                    hexes[n][m].units = 100;
                    hexes[n][m].texture = ork_dovusculeri_texture; 

                    ork_dovusculeri_sayig -= 100;
                
            }
            else if((ork_dovusculeri_sayig > 0) && (ork_dovusculeri_sayig <= 100)) {
                
                    hexes[n][m].health = ork_dovusculeri_saglik / ork_dovusculeri_saglik;
                    hexes[n][m].units = ork_dovusculeri_sayig;
                    hexes[n][m].texture = ork_dovusculeri_texture; 

                    ork_dovusculeri_sayig -= ork_dovusculeri_sayig;
                    

            }
            else if((mizrakcilar_sayig > 0) && (mizrakcilar_sayig > 100)) {
                
                
                    hexes[n][m].health = mizrakcilar_saglik / mizrakcilar_saglik;
                    hexes[n][m].units = 100;
                    hexes[n][m].texture = mizrakcilar_texture; 

                    mizrakcilar_sayig -= 100;
                
            }
            else if((mizrakcilar_sayig > 0) && (mizrakcilar_sayig <= 100)) {
                
                    hexes[n][m].health = mizrakcilar_saglik / mizrakcilar_saglik;
                    hexes[n][m].units = mizrakcilar_sayig;
                    hexes[n][m].texture = mizrakcilar_texture; 

                    mizrakcilar_sayig -= mizrakcilar_sayig;
                    

            }
            else if((varg_binicileri_sayig > 0) && (varg_binicileri_sayig > 100)) {
                
                
                    hexes[n][m].health = 1;
                    hexes[n][m].units = 100;
                    hexes[n][m].texture = varg_binicileri_texture; 

                    varg_binicileri_sayig -= 100;
                
            }
            else if((varg_binicileri_sayig > 0) && (varg_binicileri_sayig <= 100)) {
                
                    hexes[n][m].health = 1;
                    hexes[n][m].units = varg_binicileri_sayig;
                    hexes[n][m].texture = varg_binicileri_texture; 

                    varg_binicileri_sayig -= varg_binicileri_sayig;


            }
            else if((troller_sayig > 0) && (troller_sayig > 100)) {
                
                
                    hexes[n][m].health = troller_saglik / troller_saglik;
                    hexes[n][m].units = 100;
                    hexes[n][m].texture = troller_texture; 

                    troller_sayig -= 100;
                
            }
            else if((troller_sayig > 0) && (troller_sayig <= 100)) {
                
                    hexes[n][m].health = troller_saglik / troller_saglik;
                    hexes[n][m].units = troller_sayig;
                    hexes[n][m].texture = troller_texture; 

                    troller_sayig -= troller_sayig;


            }

            
        }
    }
    /*for(int a = 0; a < 20; a++) {
        for(int b = 0; b < 20; b++) {
            

                   if(hexes[a][b].health == NULL)
                   { 
                    hexes[a][b].health = 0;
                   }

                   if(hexes[a][b].units == NULL)
                   {
                       
                    hexes[a][b].units = 0;
                   }
                   if(hexes[a][b].texture == NULL){

                    hexes[a][b].texture == okcular_texture;
                   }
        }

    }*/

    int quit = 0;
    SDL_Event e;
    while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_r: //r
                    for(int a = 0; a < 10; a++) {
                        for(int b = 0; b < 10; b++) {
                            hexes[a][b].x = start_x + b * 1.5 * HEX_SIZE;
                            hexes[a][b].y = start_y + a * hex_height + (b % 2) * (HEX_SIZE * sqrt(3) / 2);
                            hexes[a][b].health = 0;
                            hexes[a][b].units = 0;
                            hexes[a][b].texture = bos_texture; 

                        }
                    }       

                    for (int i = 0; i < 10; i++) {        
                        for (int j = 0; j < 10; j++) {
                            if(i == 0 && j == 0) {
                                hexes[0][0].texture = insanlar_kahraman_texture;    
                                continue;
                            }
                            else if(i == 1 && j == 0) {
                                hexes[0][1].texture = insanlar_canavar_texture;
                                continue;
                            }
                            else if((piyadeler_sayi > 0) && (piyadeler_sayi > 100)) {

                                    hexes[j][i].health = piyadeler_sonra / piyadeler_once;
                                    hexes[j][i].units = 100;
                                    hexes[j][i].texture = piyadeler_texture; 

                                    piyadeler_sayi -= 100;

                            }
                            else if((piyadeler_sayi > 0) && (piyadeler_sayi <= 100)) { 
                                    hexes[j][i].health = piyadeler_sonra / piyadeler_once;
                                    hexes[j][i].units = piyadeler_sayi;
                                    hexes[j][i].texture = piyadeler_texture; 

                                    piyadeler_sayi -= piyadeler_sayi;
                                    continue;

                            }
                            else if((okcular_sayi > 0) && (okcular_sayi > 100)) {


                                    hexes[j][i].health = okcular_sonra / okcular_once;
                                    hexes[j][i].units = 100;
                                    hexes[j][i].texture = okcular_texture; 

                                    okcular_sayi -= 100;

                            }
                            else if((okcular_sayi > 0) && (okcular_sayi <= 100)) {

                                    hexes[j][i].health = okcular_sonra / okcular_once;
                                    hexes[j][i].units = okcular_sayi;
                                    hexes[j][i].texture = okcular_texture; 

                                    okcular_sayi -= okcular_sayi;
                                    continue;

                            }
                            else if((suvariler_sayi > 0) && (suvariler_sayi > 100)) {


                                    hexes[j][i].health = suvariler_sonra / suvariler_once;
                                    hexes[j][i].units = 100;
                                    hexes[j][i].texture = suvariler_texture; 

                                    suvariler_sayi -= 100;

                            }
                            else if((suvariler_sayi > 0) && (suvariler_sayi <= 100)) {

                                    hexes[j][i].health = suvariler_sonra / suvariler_once;
                                    hexes[j][i].units = suvariler_sayi;
                                    hexes[j][i].texture = suvariler_texture; 

                                    suvariler_sayi -= suvariler_sayi;
                                    continue;

                            }
                            else if((kusatma_makineleri_sayi > 0) && (kusatma_makineleri_sayi > 100)) {


                                    hexes[j][i].health = kusatma_makineleri_sonra / kusatma_makineleri_once;
                                    hexes[j][i].units = 100;
                                    hexes[j][i].texture = kusatma_makineleri_texture; 

                                    kusatma_makineleri_sayi -= 100;

                            }
                            else if((kusatma_makineleri_sayi > 0) && (kusatma_makineleri_sayi <= 100)) {

                                    hexes[j][i].health = kusatma_makineleri_sonra / kusatma_makineleri_once;
                                    hexes[j][i].units = kusatma_makineleri_sayi;
                                    hexes[j][i].texture = kusatma_makineleri_texture; 

                                    kusatma_makineleri_sayi -= kusatma_makineleri_sayi;
                                    continue;

                            }
                        }
                    }



                    for(int m = 9; m >= 0; m--) {
                        for(int n = 9; n >= 0; n--) {
                            if(m == 9 && n == 9) {
                                hexes[n][m].texture =  orklar_kahraman_texture;

                            }
                            else if(m == 9 && n == 8) {
                                hexes[n][m].texture =  orklar_canavar_texture;

                            }
                            else if((ork_dovusculeri_sayi > 0) && (ork_dovusculeri_sayi > 100)) {
                            

                                    hexes[n][m].health = ork_dovusculeri_sonra / ork_dovusculeri_once;
                                    hexes[n][m].units = 100;
                                    hexes[n][m].texture = ork_dovusculeri_texture; 

                                    ork_dovusculeri_sayi -= 100;

                            }
                            else if((ork_dovusculeri_sayi > 0) && (ork_dovusculeri_sayi <= 100)) {

                                    hexes[n][m].health = ork_dovusculeri_sonra / ork_dovusculeri_once;
                                    hexes[n][m].units = ork_dovusculeri_sayi;
                                    hexes[n][m].texture = ork_dovusculeri_texture; 

                                    ork_dovusculeri_sayi -= ork_dovusculeri_sayi;


                            }
                            else if((mizrakcilar_sayi > 0) && (mizrakcilar_sayi > 100)) {


                                    hexes[n][m].health = mizrakcilar_sonra / mizrakcilar_once;
                                    hexes[n][m].units = 100;
                                    hexes[n][m].texture = mizrakcilar_texture; 

                                    mizrakcilar_sayi -= 100;

                            }
                            else if((mizrakcilar_sayi > 0) && (mizrakcilar_sayi <= 100)) {

                                    hexes[n][m].health = mizrakcilar_sonra / mizrakcilar_once;
                                    hexes[n][m].units = mizrakcilar_sayi;
                                    hexes[n][m].texture = mizrakcilar_texture; 

                                    mizrakcilar_sayi -= mizrakcilar_sayi;


                            }
                            else if((varg_binicileri_sayi > 0) && (varg_binicileri_sayi > 100)) {


                                    hexes[n][m].health = varg_binicileri_sonra / varg_binicileri_once;
                                    hexes[n][m].units = 100;
                                    hexes[n][m].texture = varg_binicileri_texture; 

                                    varg_binicileri_sayi -= 100;

                            }
                            else if((varg_binicileri_sayi > 0) && (varg_binicileri_sayi <= 100)) {

                                    hexes[n][m].health = varg_binicileri_sonra / varg_binicileri_once;
                                    hexes[n][m].units = varg_binicileri_sayi;
                                    hexes[n][m].texture = varg_binicileri_texture; 

                                    varg_binicileri_sayi -= varg_binicileri_sayi;


                            }
                            else if((troller_sayi > 0) && (troller_sayi > 100)) {


                                    hexes[n][m].health = troller_sonra / troller_once;
                                    hexes[n][m].units = 100;
                                    hexes[n][m].texture = troller_texture; 

                                    troller_sayi -= 100;

                            }
                            else if((troller_sayi > 0) && (troller_sayi <= 100)) {

                                    hexes[n][m].health = troller_sonra / troller_once;
                                    hexes[n][m].units = troller_sayi;
                                    hexes[n][m].texture = troller_texture; 

                                    troller_sayi -= troller_sayi;


                            }


                        }
                    }

                    break;
            }
        }
    }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Beyaz çizim rengi

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background_texture, NULL, NULL);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                drawHexagon(renderer, hexes[i][j].x, hexes[i][j].y, HEX_SIZE);
                drawTexture(renderer, hexes[i][j].texture, hexes[i][j].x, hexes[i][j].y, HEX_SIZE); 

                drawHealthBar(renderer, hexes[i][j]);

                char buffer[10];

                if (hexes[i][j].units != 0) {
                    char buffer[10];
                    sprintf(buffer, "%d", hexes[i][j].units);
                    drawText(renderer, font, hexes[i][j].x, hexes[i][j].y + 10, buffer);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    // bellegi sil
    SDL_DestroyTexture(okcular_texture);
    SDL_DestroyTexture(piyadeler_texture);
    SDL_DestroyTexture(suvariler_texture);
    SDL_DestroyTexture(kusatma_makineleri_texture);
    SDL_DestroyTexture(ork_dovusculeri_texture);
    SDL_DestroyTexture(mizrakcilar_texture);
    SDL_DestroyTexture(varg_binicileri_texture);
    SDL_DestroyTexture(troller_texture);
    SDL_DestroyTexture(bos_texture);
    SDL_DestroyTexture(insanlar_kahraman_texture);
    SDL_DestroyTexture(insanlar_canavar_texture);
    SDL_DestroyTexture(orklar_kahraman_texture);
    SDL_DestroyTexture(orklar_canavar_texture);
    SDL_DestroyTexture(background_texture);



    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();






    return 0;

}