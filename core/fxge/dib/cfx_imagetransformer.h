// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXGE_DIB_CFX_IMAGETRANSFORMER_H_
#define CORE_FXGE_DIB_CFX_IMAGETRANSFORMER_H_

#include <memory>

#include "core/fxcrt/fx_coordinates.h"
#include "core/fxcrt/retain_ptr.h"
#include "core/fxcrt/unowned_ptr.h"
#include "core/fxge/dib/cfx_bitmapstorer.h"
#include "core/fxge/dib/cfx_dibitmap.h"
#include "core/fxge/dib/cfx_dibsource.h"

class CFX_ImageStretcher;

class CFX_ImageTransformer {
 public:
  CFX_ImageTransformer(const RetainPtr<CFX_DIBSource>& pSrc,
                       const CFX_Matrix* pMatrix,
                       int flags,
                       const FX_RECT* pClip);
  ~CFX_ImageTransformer();

  bool Continue(IFX_PauseIndicator* pPause);

  const FX_RECT& result() const { return m_result; }
  RetainPtr<CFX_DIBitmap> DetachBitmap();

 private:
  struct CalcData {
    const CFX_DIBitmap* bitmap;
    const CFX_Matrix& matrix;
    const uint8_t* buf;
    int pitch;
  };

  void CalcMask(const CalcData& cdata);
  void CalcAlpha(const CalcData& cdata);
  void CalcMono(const CalcData& cdata, FXDIB_Format format);

  bool IsBilinear() const {
    return !(m_Flags & FXDIB_DOWNSAMPLE) && !IsBiCubic();
  }
  bool IsBiCubic() const { return !!(m_Flags & FXDIB_BICUBIC_INTERPOL); }

  int stretch_width() const { return m_StretchClip.Width(); }
  int stretch_height() const { return m_StretchClip.Height(); }

  bool InStretchBounds(int col, int row) const {
    return col >= 0 && col <= stretch_width() && row >= 0 &&
           row <= stretch_height();
  }

  void AdjustCoords(int* col, int* row) const;

  const RetainPtr<CFX_DIBSource> m_pSrc;
  UnownedPtr<const CFX_Matrix> const m_pMatrix;
  const FX_RECT* const m_pClip;
  FX_RECT m_StretchClip;
  FX_RECT m_result;
  CFX_Matrix m_dest2stretch;
  std::unique_ptr<CFX_ImageStretcher> m_Stretcher;
  CFX_BitmapStorer m_Storer;
  const uint32_t m_Flags;
  int m_Status;
};

#endif  // CORE_FXGE_DIB_CFX_IMAGETRANSFORMER_H_
