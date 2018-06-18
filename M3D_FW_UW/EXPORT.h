#pragma once

#define EXPORT __declspec(dllexport) __cdecl
#define PTR_EXPORT(P) __declspec(dllexport) P __cdecl