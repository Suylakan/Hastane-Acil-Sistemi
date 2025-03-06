#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Doktor ve Hasta Struct Tanımları
typedef struct {
    char TC[12];
    char name[50];
    int patientID;
    char complaint[255];
    char diagnosis[255];
} Patient;

typedef struct {
    char name[50];
    char username[20];
    char password[20];
} Doctor;

Patient patients[100];
Doctor doctors[100];
int patientCount = 0;
int doctorCount = 0;

// İlaç Struct Tanımı
typedef struct {
    char name[50];
} Medicine;

Medicine allMedicines[100];
Medicine prescribedMedicines[100];
int allMedicineCount = 0;
int prescribedMedicineCount = 0;

// Fonksiyon Prototipleri
void mainMenu();
void adminMenu();
void doctorMenu(const char* doctorName);
void registerDoctor();
void registerPatient();
void diagnosePatient();
void listPatients();
void addMedicine();
void prescribeMedicine();
void createHL7Message(Patient p, char *message);
void getCurrentTime(char *buffer);
int generatePrescriptionNumber();
void listAllMedicines();

int main() {
    mainMenu();
    return 0;
}

// Ana Menü Fonksiyonu
void mainMenu() {
    char username[20];
    char password[20];

    while (1) {
        printf("Kullanici adi: ");
        scanf("%s", username);
        printf("Sifre: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            adminMenu();
        } else {
            int found = 0;
            for (int i = 0; i < doctorCount; i++) {
                if (strcmp(doctors[i].username, username) == 0 && strcmp(doctors[i].password, password) == 0) {
                    doctorMenu(doctors[i].name);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Gecersiz giris!\n");
            }
        }
    }
}

// Fonksiyon Tanımları
void adminMenu() {
    int choice;

    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Doktor Kaydet\n");
        printf("2. Hasta Kaydet\n");
        printf("3. Ilac Ekle\n");
        printf("4. Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerDoctor();
                break;
            case 2:
                registerPatient();
                break;
            case 3:
                addMedicine();
                break;
            case 4:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while (choice != 4);
}

void doctorMenu(const char* doctorName) {
    int choice;

    printf("Hos geldiniz, Dr. %s\n", doctorName);

    do {
        printf("\n--- Doktor Menu ---\n");
        printf("1. Mevcut Hastalari Listele\n");
        printf("2. Hasta Kaydet\n");
        printf("3. Hasta Teshis\n");
        printf("4. Recete Yaz\n");
        printf("5. Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listPatients();
                break;
            case 2:
                registerPatient();
                break;
            case 3:
                diagnosePatient();
                break;
            case 4:
                prescribeMedicine();
                break;
            case 5:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while (choice != 5);
}

void registerDoctor() {
    Doctor d;

    printf("Doktor adi: ");
    scanf("%s", d.name);
    printf("Doktor kullanici adi: ");
    scanf("%s", d.username);
    printf("Doktor sifre: ");
    scanf("%s", d.password);

    doctors[doctorCount] = d;
    doctorCount++;

    printf("Doktor %s basariyla kaydedildi.\n", d.name);
}

void registerPatient() {
    Patient p;
    printf("TC Kimlik Numarasi: ");
    scanf("%s", p.TC);
    printf("Hasta adi: ");
    scanf("%s", p.name);
    p.patientID = patientCount + 1;
    patients[patientCount] = p;
    patientCount++;

    char hl7Message[1024];
    createHL7Message(p, hl7Message);
    printf("Hasta %s basariyla kaydedildi. Hasta numarasi: %d\n", p.name, p.patientID);
    printf("HL7 Mesaji:\n%s", hl7Message);
}

void diagnosePatient() {
    int patientID;
    printf("Teshis edilecek hastanin ID numarasi: ");
    scanf("%d", &patientID);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == patientID) {
            printf("Hasta adi: %s\n", patients[i].name);
            printf("Hasta sikayeti: ");
            scanf(" %[^\n]", patients[i].complaint);
            printf("Doktor gorusu: ");
            scanf(" %[^\n]", patients[i].diagnosis);
            printf("Sikayet ve gorus basariyla kaydedildi.\n");
            return;
        }
    }
    printf("Hasta bulunamadi!\n");
}

void listPatients() {
    printf("\n--- Mevcut Hastalar ---\n");
    for (int i = 0; i < patientCount; i++) {
        printf("Hasta ID: %d, Ad: %s, TC: %s\n", patients[i].patientID, patients[i].name, patients[i].TC);
    }
    printf("\n");
}

void addMedicine() {
    printf("Tum ilaclar listesine eklenecek ilacin adi: ");
    scanf("%s", allMedicines[allMedicineCount].name);
    allMedicineCount++;
    printf("Ilac basariyla eklendi.\n");
}

void listAllMedicines() {
    printf("\n--- Tum Ilaclar ---\n");
    for (int i = 0; i < allMedicineCount; i++) {
        printf("%d. Ilac: %s\n", i + 1, allMedicines[i].name);
    }
    printf("\n");
}

void prescribeMedicine() {
    int patientID;
    printf("Recete yazilacak hastanin ID numarasi: ");
    scanf("%d", &patientID);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == patientID) {
            printf("Hasta adi: %s\n", patients[i].name);
            printf("Hasta sikayeti: %s\n", patients[i].complaint);
            printf("Doktor gorusu: %s\n", patients[i].diagnosis);

            int prescriptionNumber = generatePrescriptionNumber();
            printf("Recete Numarasi: %d\n", prescriptionNumber);

            listAllMedicines();

            char medicineName[50];
            printf("Hastaya verilecek ilac adi: ");
            scanf("%s", medicineName);

            for (int j = 0; j < allMedicineCount; j++) {
                if (strcmp(allMedicines[j].name, medicineName) == 0) {
                    prescribedMedicines[prescribedMedicineCount] = allMedicines[j];
                    prescribedMedicineCount++;
                    printf("Ilac basariyla receteye eklendi.\n");
                    return;
                }
            }
            printf("Ilac bulunamadi!\n");
            return;
        }
    }
    printf("Hasta bulunamadi!\n");
}

int generatePrescriptionNumber() {
    return rand() % 1000000; // 0 ile 999999 arasında rastgele bir sayı
}

void getCurrentTime(char *buffer) {
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 20, "%Y%m%d%H%M%S", timeinfo);
}

void createHL7Message(Patient p, char *message) {
    char currentTime[20];
    getCurrentTime(currentTime);

    sprintf(message,
        "MSH|^~\\&|HastaneSistemi|Hastane|MerkeziSistem|SaglikBakanligi|%s||ADT^A01|%d|P|2.3\n"
        "EVN|A01|%s\n"
        "PID|||%d^^^TC^MR||%s||19700101|M|||123 Sokak^Istanbul^^^12345||(555)555-5555|||M||%d^^^TC^MR\n"
        "PV1||I|Acil^Oda1^1|\n",
        currentTime, p.patientID, currentTime, p.patientID, p.name, p.patientID
    );
}