#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// Og�lne informacje o zestawie s� kontrolowane poprzez nast�puj�cy 
// zestaw atrybut�w. Zmie� warto�ci tych atrybut�w, aby zmodyfikowa� informacje
// powi�zane z zestawem.
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
// Informacje o wersji zestawu zawieraj� nast�puj�ce cztery warto�ci:
//
//      Wersja g��wna
//      Wersja pomocnicza
//      Numer kompilacji
//      Rewizja
//
// Mo�na okre�li� wszystkie warto�ci lub przyj�� warto�ci domy�lne dla numeru wydania i numeru kompilacji
// przy u�yciu symbolu �*�, tak jak pokazano poni�ej:

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];