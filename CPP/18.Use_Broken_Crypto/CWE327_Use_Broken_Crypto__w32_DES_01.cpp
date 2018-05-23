/* 



*/
/*
 * 
 * 
 * 
 * 
 * 
 * 
 *
 * */

#include "std_testcase.h"

#include <windows.h>
#include <wincrypt.h>

/*  */
#pragma comment (lib, "Advapi32")

#ifndef OMITBAD

void CWE327_Use_Broken_Crypto__w32_DES_01_bad()
{
    {
        FILE *pFile;
        HCRYPTPROV hCryptProv;
        HCRYPTKEY hKey;
        HCRYPTHASH hHash;
        char password[100];
        size_t passwordLen;
        char toBeDecrypted[100];
        DWORD toBeDecryptedLen = sizeof(toBeDecrypted)-1;
        /*  */
        printLine("Enter the password: ");
        if (fgets(password, 100, stdin) == NULL)
        {
            printLine("fgets() failed");
            /*  */
            password[0] = '\0';
        }
        /* 
          */
        passwordLen = strlen(password);
        if (passwordLen > 0)
        {
            password[passwordLen-1] = '\0';
        }
        /*  */
        pFile = fopen("encrypted.txt", "rb");
        if (pFile == NULL)
        {
            exit(1);
        }
        if (fread(toBeDecrypted, sizeof(char), 100, pFile) != 100)
        {
            fclose(pFile);
            exit(1);
        }
        toBeDecrypted[99] = '\0';
        /*  */
        if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
        {
            if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
            {
                printLine("Error in acquiring cryptographic context");
                exit(1);
            }
        }
        /*  */
        if(!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
        {
            printLine("Error in creating hash");
            exit(1);
        }
        /*  */
        if(!CryptHashData(hHash, (BYTE *) password, passwordLen, 0))
        {
            printLine("Error in hashing password");
            exit(1);
        }
        /*  */
        if(!CryptDeriveKey(hCryptProv, CALG_DES, hHash, 0, &hKey))
        {
            printLine("Error in CryptDeriveKey");
            exit(1);
        }
        /*  */
        if(!CryptDecrypt(hKey, 0, 1, 0, (BYTE *)toBeDecrypted, &toBeDecryptedLen))
        {
            printLine("Error in decryption");
            exit(1);
        }
        /*  */
        toBeDecrypted[toBeDecryptedLen] = '\0';
        printLine(toBeDecrypted);
        /*  */
        if (hKey)
        {
            CryptDestroyKey(hKey);
        }
        if (hHash)
        {
            CryptDestroyHash(hHash);
        }
        if (hCryptProv)
        {
            CryptReleaseContext(hCryptProv, 0);
        }
        if (pFile)
        {
            fclose(pFile);
        }
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

static void good1()
{
    {
        FILE *pFile;
        HCRYPTPROV hCryptProv;
        HCRYPTKEY hKey;
        HCRYPTHASH hHash;
        char password[100];
        size_t passwordLen;
        char toBeDecrypted[100];
        DWORD toBeDecryptedLen = sizeof(toBeDecrypted)-1;
        /*  */
        printLine("Enter the password: ");
        if (fgets(password, 100, stdin) == NULL)
        {
            printLine("fgets() failed");
            /*  */
            password[0] = '\0';
        }
        /* 
          */
        passwordLen = strlen(password);
        if (passwordLen > 0)
        {
            password[passwordLen-1] = '\0';
        }
        /*  */
        pFile = fopen("encrypted.txt", "rb");
        if (pFile == NULL)
        {
            exit(1);
        }
        if (fread(toBeDecrypted, sizeof(char), 100, pFile) != 100)
        {
            fclose(pFile);
            exit(1);
        }
        toBeDecrypted[99] = '\0';
        /*  */
        if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
        {
            if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
            {
                printLine("Error in acquiring cryptographic context");
                exit(1);
            }
        }
        /*  */
        if(!CryptCreateHash(hCryptProv, CALG_SHA_256, 0, 0, &hHash))
        {
            printLine("Error in creating hash");
            exit(1);
        }
        /*  */
        if(!CryptHashData(hHash, (BYTE *) password, passwordLen, 0))
        {
            printLine("Error in hashing password");
            exit(1);
        }
        /*  */
        if(!CryptDeriveKey(hCryptProv, CALG_AES_256, hHash, 0, &hKey))
        {
            printLine("Error in CryptDeriveKey");
            exit(1);
        }
        /*  */
        if(!CryptDecrypt(hKey, 0, 1, 0, (BYTE *)toBeDecrypted, &toBeDecryptedLen))
        {
            printLine("Error in decryption");
            exit(1);
        }
        /*  */
        toBeDecrypted[toBeDecryptedLen] = '\0';
        printLine(toBeDecrypted);
        /*  */
        if (hKey)
        {
            CryptDestroyKey(hKey);
        }
        if (hHash)
        {
            CryptDestroyHash(hHash);
        }
        if (hCryptProv)
        {
            CryptReleaseContext(hCryptProv, 0);
        }
        if (pFile)
        {
            fclose(pFile);
        }
    }
}

void CWE327_Use_Broken_Crypto__w32_DES_01_good()
{
    good1();
}

#endif /* OMITGOOD */

/* 
   
   
    */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /*  */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE327_Use_Broken_Crypto__w32_DES_01_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE327_Use_Broken_Crypto__w32_DES_01_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif