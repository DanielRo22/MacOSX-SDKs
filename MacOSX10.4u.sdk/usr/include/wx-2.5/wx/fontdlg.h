///////////////////////////////////////////////////////////////////////////////
// Name:        wx/fontdlg.h
// Purpose:     common interface for different wxFontDialog classes
// Author:      Vadim Zeitlin
// Modified by:
// Created:     12.05.02
// RCS-ID:      $Id: fontdlg.h,v 1.27 2004/09/28 14:28:22 JS Exp $
// Copyright:   (c) 1997-2002 wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_FONTDLG_H_BASE_
#define _WX_FONTDLG_H_BASE_

#include "wx/defs.h"            // for wxUSE_FONTDLG

#if wxUSE_FONTDLG

#include "wx/dialog.h"          // the base class
#include "wx/cmndata.h"         // wxFontData

// ----------------------------------------------------------------------------
// wxFontDialog interface
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxFontDialogBase : public wxDialog
{
public:
    // create the font dialog
    wxFontDialogBase() { }
    wxFontDialogBase(wxWindow *parent) { m_parent = parent; }
    wxFontDialogBase(wxWindow *parent, const wxFontData& data)
        { m_parent = parent; InitFontData(&data); }

    bool Create(wxWindow *parent)
        { return DoCreate(parent); }
    bool Create(wxWindow *parent, const wxFontData& data)
        { InitFontData(&data); return Create(parent); }

    virtual ~wxFontDialogBase();

    // retrieve the font data
    const wxFontData& GetFontData() const { return m_fontData; }
    wxFontData& GetFontData() { return m_fontData; }

    // deprecated interface, for compatibility only, don't use
    wxFontDialogBase(wxWindow *parent, const wxFontData *data)
        { m_parent = parent; InitFontData(data); }

    bool Create(wxWindow *parent, const wxFontData *data)
        { InitFontData(data); return Create(parent); }

protected:
    virtual bool DoCreate(wxWindow *parent) { m_parent = parent; return true; }

    void InitFontData(const wxFontData *data = NULL)
        { if ( data ) m_fontData = *data; }

    wxFontData m_fontData;

    DECLARE_NO_COPY_CLASS(wxFontDialogBase)
};

// ----------------------------------------------------------------------------
// platform-specific wxFontDialog implementation
// ----------------------------------------------------------------------------

#define USE_NATIVE_FONT_DIALOG_FOR_MACOSX 0

#if defined(__WXUNIVERSAL__) || \
    defined(__WXMOTIF__)     || \
    (defined(__WXMAC__) && !defined(__WXMAC_OSX__))  || \
    (defined(__WXMAC__) && !USE_NATIVE_FONT_DIALOG_FOR_MACOSX)  || \
    (defined(__WXMAC_OSX__) && ( MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_2 ) ) || \
    defined(__WXCOCOA__)     || \
    defined(__WXWINCE__)     || \
    defined(__WXGPE__)

    #include "wx/generic/fontdlgg.h"
    #define wxFontDialog wxGenericFontDialog
#elif defined(__WXMSW__)
    #include "wx/msw/fontdlg.h"
#elif defined(__WXGTK__)
    #include "wx/gtk/fontdlg.h"
#elif defined(__WXPM__)
    #include "wx/os2/fontdlg.h"
#elif defined(__WXMAC__)
    #include "wx/mac/fontdlg.h"
#endif

// ----------------------------------------------------------------------------
// global public functions
// ----------------------------------------------------------------------------

// get the font from user and return it, returns wxNullFont if the dialog was
// cancelled
wxFont WXDLLEXPORT
wxGetFontFromUser(wxWindow *parent = (wxWindow *)NULL,
                  const wxFont& fontInit = wxNullFont);

#endif // wxUSE_FONTDLG

#endif
    // _WX_FONTDLG_H_BASE_
