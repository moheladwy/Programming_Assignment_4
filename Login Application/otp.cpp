#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <charconv>
#include "EASendMailObj.tlh"
using namespace EASendMailObjLib;
using namespace std;

int otp;
string password;
const int ConnectNormal = 0;
const int ConnectSSLAuto = 1;
const int ConnectSTARTTLS = 2;
const int ConnectDirectSSL = 3;
const int ConnectTryTLS = 4;

int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitialize(NULL);

    IMailPtr oSmtp = NULL;
    oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));
    oSmtp->LicenseCode = _T("TryIt");

    // Set your sender email address
    oSmtp->FromAddr = _T("amrkhaled96023@gmail.com");
    // Add recipient email address
    oSmtp->AddRecipientEx(_T("amrkhaled96023@gmail.com"), 0);//<----------------user account(this email for test)

    // Set email subject
    oSmtp->Subject = _T("Log in app forgetten password");
    srand(time(0));
    otp = rand() % 8;
    password = to_string(otp);
    // Set email body
    oSmtp->BodyText = _T(password.c_str());//<----------------- the error in this line

    // Your SMTP server address
    oSmtp->ServerAddr = _T("smtp.gmail.com");

    // User and password for ESMTP authentication, if your server doesn't
    // require User authentication, please remove the following codes.
    oSmtp->UserName = _T("amrkhaled96023@gmail.com");
    oSmtp->Password = _T("ujtrfwmmpthcclmx");

    // Most mordern SMTP servers require SSL/TLS connection now.
    // ConnectTryTLS means if server supports SSL/TLS, SSL/TLS will be used automatically.
    oSmtp->ConnectType = ConnectTryTLS;

    // If your SMTP server uses 587 port
    oSmtp->ServerPort = 587;

    // If your SMTP server requires SSL/TLS connection on 25/587/465 port
    // oSmtp->ServerPort = 25; // 25 or 587 or 465
    // oSmtp->ConnectType = ConnectSSLAuto;

    _tprintf(_T("Start to send email ...\r\n"));

    if (oSmtp->SendMail() == 0)
    {
        _tprintf(_T("email was sent successfully!\r\n"));
    }
    else
    {
        _tprintf(_T("failed to send email with the following error: %s\r\n"),
            (const TCHAR*)oSmtp->GetLastErrDescription());
    }

    return 0;
}