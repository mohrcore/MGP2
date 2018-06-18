#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// Ogólne informacje o zestawie s¹ kontrolowane poprzez nastêpuj¹cy 
// zestaw atrybutów. Zmieñ wartoœci tych atrybutów, aby zmodyfikowaæ informacje
// powi¹zane z zestawem.
//
[assembly:AssemblyTitleAttribute(L"M3D_FW_CLR_WRAP")];
[assembly:AssemblyDescriptionAttribute(L"")];
[assembly:AssemblyConfigurationAttribute(L"")];
[assembly:AssemblyCompanyAttribute(L"")];
[assembly:AssemblyProductAttribute(L"M3D_FW_CLR_WRAP")];
[assembly:AssemblyCopyrightAttribute(L"Copyright (c)  2017")];
[assembly:AssemblyTrademarkAttribute(L"")];
[assembly:AssemblyCultureAttribute(L"")];

//
// Informacje o wersji zestawu zawieraj¹ nastêpuj¹ce cztery wartoœci:
//
//      Wersja g³ówna
//      Wersja pomocnicza
//      Numer kompilacji
//      Rewizja
//
// Mo¿na okreœliæ wszystkie wartoœci lub przyj¹æ wartoœci domyœlne dla numeru wydania i numeru kompilacji
// przy u¿yciu symbolu „*”, tak jak pokazano poni¿ej:

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];