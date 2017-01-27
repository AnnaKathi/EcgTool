/*****************************************************************************
 * MS-Adam 7.x
 * -----------
 * Copyright (c) 1987-2017
 * Martin Stratmann, c/o MS-Software GmbH, Rankestr. 4-6, 45144 Essen
 * martin.stratmann@mslib.net
 * all rights reserved.
 *
 * Project:
 * mskasse.cbproj - PC-Kasse
 *
 * Module:
 * classCashBase.cpp - Basisklasse der Kassenarbeitsklasen mit Fehlerbehandlung
 *
 * Procs:
 * class cChashBase
 *
 * Info:
 * Programmers:
 * ms - Martin Stratmann
 * an - Anna Stratmann
 *
 * $History$
 * 23.01.2017 ms Erstellung
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cBase::cBase()
    : ferror(false), ferror_code(0)
    {
    }
//---------------------------------------------------------------------------
cBase::~cBase()
    {
    }
//---------------------------------------------------------------------------
bool cBase::ok()
    {
    ferror_code = 0;
    return true;
    }
//---------------------------------------------------------------------------
bool cBase::fail(const int code, const String& msg)
    {
    ferror_code = code;
    ferror_msg  = msg;
    return false;
    }
//---------------------------------------------------------------------------
bool cBase::fail(const cBase& cbase)
    {
    ferror_code = cbase.error_code;
    ferror_msg  = cbase.error_msg;
    return false;
    }
//---------------------------------------------------------------------------
bool cBase::get_success()
    {
    return !get_error();
    }
//---------------------------------------------------------------------------
bool cBase::get_error()
    {
    return ferror_code > CE_HARDERRORS;
    }
//---------------------------------------------------------------------------
void cBase::set_trigger(String value)
    {
    ftrigger = value;
    }
//---------------------------------------------------------------------------

