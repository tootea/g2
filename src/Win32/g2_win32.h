/*****************************************************************************
**  This is part of the g2 library
**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License (version 2) as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/
/* This is g2_win32.h */
#ifndef _G2_WIN32_H
#define _G2_WIN32_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdio.h>

// Common Library header for DLL and application
#ifdef WIN32
#ifdef G2DLL
#ifdef MAKEDLL
/* Create DLL */
#define LINKDLL __declspec( dllexport)
#else
/* Use DLL */
#define LINKDLL __declspec( dllimport)
#endif
#else 
/* Use static win32 */
#define LINKDLL
#endif
#else
/* Use non-win32 */
#define LINKDLL
#endif

LINKDLL int  g2_open_win32(int width, int height, const char *filename,int type);


#if defined(__cplusplus)
} /* end extern "C" */
#endif


#endif /* _G2_WIN32_H */
